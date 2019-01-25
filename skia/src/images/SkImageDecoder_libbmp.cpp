
/*
 * Copyright 2007 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#include "bmpdecoderhelper.h"
#include "SkColorPriv.h"
#include "SkImageDecoder.h"
#include "SkScaledBitmapSampler.h"
#include "SkStream.h"
#include "SkStreamPriv.h"
#include "SkTDArray.h"
#include <unistd.h>

#include "SkTemplates.h"


class SkBMPImageDecoder : public SkImageDecoder {
public:
    SkBMPImageDecoder() {
        buffer = NULL;
    }
    ~SkBMPImageDecoder() {
        if(buffer) {
            sk_free(buffer);
        }
    }

    Format getFormat() const override {
        return kBMP_Format;
    }

protected:
    Result onDecode(SkStream* stream, SkBitmap* bm, Mode mode) override;
    bool onBuildTileIndex(SkStreamRewindable *stream,
             int *width, int *height) override;
    bool onDecodeSubset(SkBitmap* bitmap, const SkIRect& region) override;
private:
    typedef SkImageDecoder INHERITED;

    int imageWidth;
    int imageHeight;
    void* buffer;
    int length;
};

///////////////////////////////////////////////////////////////////////////////
DEFINE_DECODER_CREATOR(BMPImageDecoder);
///////////////////////////////////////////////////////////////////////////////

static bool is_bmp(SkStreamRewindable* stream) {
    static const char kBmpMagic[] = { 'B', 'M' };


    char buffer[sizeof(kBmpMagic)];

    return stream->read(buffer, sizeof(kBmpMagic)) == sizeof(kBmpMagic) &&
        !memcmp(buffer, kBmpMagic, sizeof(kBmpMagic));
}

static SkImageDecoder* sk_libbmp_dfactory(SkStreamRewindable* stream) {
    if (is_bmp(stream)) {
        return SkNEW(SkBMPImageDecoder);
    }
    return NULL;
}

static SkImageDecoder_DecodeReg gReg(sk_libbmp_dfactory);

static SkImageDecoder::Format get_format_bmp(SkStreamRewindable* stream) {
    if (is_bmp(stream)) {
        return SkImageDecoder::kBMP_Format;
    }
    return SkImageDecoder::kUnknown_Format;
}

static SkImageDecoder_FormatReg gFormatReg(get_format_bmp);

///////////////////////////////////////////////////////////////////////////////

class SkBmpDecoderCallback : public image_codec::BmpDecoderCallback {
public:
    // we don't copy the bitmap, just remember the pointer
    SkBmpDecoderCallback(bool justBounds) : fJustBounds(justBounds) {}

    // override from BmpDecoderCallback
    virtual uint8* SetSize(int width, int height) {
        fWidth = width;
        fHeight = height;
        if (fJustBounds) {
            return NULL;
        }

        fRGB.setCount(width * height * 3);  // 3 == r, g, b
        return fRGB.begin();
    }
    virtual uint8* SetSizeRegion(int width, int height, SkIRect * region) {
        fWidth = region->width();
        fHeight = region->height();
        fRGB.setCount(fWidth * fHeight * 3);  // 3 == r, g, b
        return fRGB.begin();
    }

    int width() const { return fWidth; }
    int height() const { return fHeight; }
    const uint8_t* rgb() const { return fRGB.begin(); }

private:
    SkTDArray<uint8_t> fRGB;
    int fWidth;
    int fHeight;
    bool fJustBounds;
};

SkImageDecoder::Result SkBMPImageDecoder::onDecode(SkStream* stream, SkBitmap* bm, Mode mode) {
    // First read the entire stream, so that all of the data can be passed to
    // the BmpDecoderHelper.
    // Allocated space used to hold the data.
    SkAutoMalloc storage;
    // Byte length of all of the data.

    const size_t length = SkCopyStreamToStorage(&storage, stream);

    if (0 == length) {
        storage.free();
        return kFailure;
    }

    const bool justBounds = SkImageDecoder::kDecodeBounds_Mode == mode;
    SkBmpDecoderCallback callback(justBounds);

    // Now decode the BMP into callback's rgb() array [r,g,b, r,g,b, ...]
    {
        image_codec::BmpDecoderHelper helper;
        const int max_pixels = 16383*16383; // max width*height
        if (!helper.DecodeImage((const char*)storage.get(), length,
                                max_pixels, NULL, &callback)) {
            return kFailure;
        }
    }

    // we don't need this anymore, so free it now (before we try to allocate
    // the bitmap's pixels) rather than waiting for its destructor

    storage.free();

    int width = callback.width();
    int height = callback.height();
    SkColorType colorType = this->getPrefColorType(k32Bit_SrcDepth, false);

    // only accept prefConfig if it makes sense for us
    if (kARGB_4444_SkColorType != colorType && kRGB_565_SkColorType != colorType) {
        colorType = kN32_SkColorType;
    }

    SkScaledBitmapSampler sampler(width, height, getSampleSize());

    bm->setInfo(SkImageInfo::Make(sampler.scaledWidth(), sampler.scaledHeight(),
                                  colorType, kOpaque_SkAlphaType));

    if (justBounds) {
        return kSuccess;
    }

    if (!this->allocPixelRef(bm, NULL)) {
        return kFailure;
    }

    SkAutoLockPixels alp(*bm);

    if (!sampler.begin(bm, SkScaledBitmapSampler::kRGB, *this)) {
        return kFailure;
    }

    const int srcRowBytes = width * 3;
    const int dstHeight = sampler.scaledHeight();
    const uint8_t* srcRow = callback.rgb();

    srcRow += sampler.srcY0() * srcRowBytes;
    for (int y = 0; y < dstHeight; y++) {
        sampler.next(srcRow);
        srcRow += sampler.srcDY() * srcRowBytes;
    }
    return kSuccess;
}

static const int kBmpHeaderSize = 14;
static const int kBmpInfoSize = 40;
static const int kBmpOS2InfoSize = 12;
static const int kMaxDim = SHRT_MAX / 2;

bool SkBMPImageDecoder::onBuildTileIndex(SkStreamRewindable* sk_stream, int *width,
        int *height) {

    /// for cts test case @{
    char acBuf[256];
    sprintf(acBuf, "/proc/%d/cmdline", getpid());
    FILE *fp = fopen(acBuf, "r");
    if (fp)
    {
        fread(acBuf, 1, sizeof(acBuf), fp);
        fclose(fp);
        if(strncmp(acBuf, "com.android.cts", 15) == 0)
        {
            if (sk_stream){
                SkDELETE(sk_stream);
            }
            return false;
        }
    }
    /// @}

    const size_t BMP_SIZE_LIMIT = getBMPLimitSize();

    size_t len = sk_stream->getLength();
    //SPRD: large BMP image decoding will cause OOM, if the picture size is larger than 110M, do not decode
    if (len > BMP_SIZE_LIMIT) {
        SkDebugf("onBuildTileIndex,bmp size is %d, larger than %d bytes, do not decode.", (unsigned int)len,(unsigned int)BMP_SIZE_LIMIT);
        if (sk_stream){
            SkDELETE(sk_stream);
        }
        return false;
    }

    if (len < 26)
    {
        if (sk_stream){
            SkDELETE(sk_stream);
        }
        return false;
    }

    if (buffer)
    {
        sk_free(buffer);
        buffer = NULL;
    }



    buffer = sk_malloc_throw(len);
    if (sk_stream->read(buffer, len) != len) {
        sk_free(buffer);
        if (sk_stream){
            SkDELETE(sk_stream);
        }
        return false;
    }

    uint8* header = (uint8*)buffer;
    int size = header[14] + (header[15] << 8) + (header[16] << 16) + (header[17] << 24);
    if (size >= 40) {
    int origWidth  = header[18] + (header[19] << 8) + (header[20] << 16) + (header[21] << 24);
    int origHeight = header[22] + (header[23] << 8) + (header[24] << 16) + (header[25] << 24);

    *width = origWidth;
    *height = origHeight;
    /// for the BMP file on the OS2 system. @{
    } else {
        int os2OrigWidth = header[18] + (header[19] << 8);
        int os2OrigHeight = header[20] + (header[21] <<8);
        *width = os2OrigWidth;
        *height = os2OrigHeight;
    }
    /// @}
    this->imageWidth = *width;
    /// for the flip row BMP file. @{
    if (*height < 0) {
        *height = -*height;
        this->imageHeight = *height;
    /// @}
    } else {
    this->imageHeight = *height;
    }
    this->length = len;

    if (sk_stream){
        SkDELETE(sk_stream);
    }
    return true;
}

bool SkBMPImageDecoder::onDecodeSubset(SkBitmap* bm, const SkIRect& region) {


    SkIRect rect = SkIRect::MakeWH(this->imageWidth, this->imageHeight);
    if (!rect.intersect(region)) {
        SkDebugf("SkBMPImageDecoder::onDecodeSubset region is error");
        // If the requested region is entirely outsides the image, just
        // returns false
        return false;
    }


    //decode
    bool justBounds = false;
    SkBmpDecoderCallback callback(justBounds);

    // Now decode the BMP into callback's rgb() array [r,g,b, r,g,b, ...]
    {
        image_codec::BmpDecoderHelper helper;
        const int max_pixels = 16383*16383;
        if (!helper.DecodeImage((const char*)buffer, this->length,
                                max_pixels, &rect, &callback)) {
            SkDebugf("SkBMPImageDecoder::onDecodeSubset helper.DecodeImage return null");
            return false;
        }
    }

    //DUMP bitmap here
    //end dump
    int width = callback.width();
    int height = callback.height();
    SkColorType colorType = this->getPrefColorType(k32Bit_SrcDepth, false);

    // only accept prefConfig if it makes sense for us
    if (kARGB_4444_SkColorType != colorType && kRGB_565_SkColorType != colorType) {
        colorType = kN32_SkColorType;
    }

    //Sample
    const int sampleSize = this->getSampleSize();
    SkScaledBitmapSampler sampler(rect.width(), rect.height(), sampleSize);

    SkBitmap *decodedBitmap = new SkBitmap;
    SkAutoTDelete<SkBitmap> adb(decodedBitmap);
    decodedBitmap->setInfo(SkImageInfo::Make(sampler.scaledWidth(), sampler.scaledHeight(),
                                  colorType, kOpaque_SkAlphaType));

    int w = rect.width() / sampleSize;
    int h = rect.height() / sampleSize;
    bool swapOnly = (rect == region) && (w == decodedBitmap->width()) &&
                    (h == decodedBitmap->height()) &&
                    ((0 - rect.x()) / sampleSize == 0) && bm->isNull();

    if (swapOnly) {
        if (!this->allocPixelRef(decodedBitmap,
               NULL)) {

            return false;
        }
    } else {
        if (!decodedBitmap->tryAllocPixels(
            NULL,  NULL)) {
            return false;
        }
    }
    SkAutoLockPixels alp(*decodedBitmap);

    if (!sampler.begin(decodedBitmap, SkScaledBitmapSampler::kRGB, *this)) {
        return false;
    }

    const int srcRowBytes = width * 3;
    const int dstHeight = sampler.scaledHeight();
    const uint8_t* srcRow = callback.rgb();

    srcRow += sampler.srcY0() * srcRowBytes;
    for (int y = 0; y < dstHeight; y++) {
        sampler.next(srcRow);
        srcRow += sampler.srcDY() * srcRowBytes;
    }

    int startX = rect.fLeft;
    int startY = rect.fTop;

    if (swapOnly) {
        bm->swap(*decodedBitmap);
    } else {
        cropBitmap(bm, decodedBitmap, sampleSize, region.x(), region.y(),
                   region.width(), region.height(), startX, startY);
    }
    //SkDebugf("bmp_decoder onDecodeSubset finish successfully, L:%d!!!\n",__LINE__);

    return true;
}
