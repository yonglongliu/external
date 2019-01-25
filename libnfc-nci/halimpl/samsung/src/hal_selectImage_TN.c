/*
 *    Copyright (C) 2016 SAMSUNG S.LSI
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *   Author: Woonki Lee <woonki84.lee@samsung.com>
 *
 */

#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <cutils/properties.h>

#include "osi.h"
#include "hal.h"
#include "util.h"

//#define TN
#ifdef TN
#include <SecNativeFeature.h>
#endif

#define DEFAULT_CODE                "DEF"
#define MPOS_CODE                   "MPS"

#define FIELD_NAME_UFU_DIR_PATH     "UFU_DIR_PATH"
#define FIELD_NAME_FW_DIR_PATH      "FW_DIR_PATH"
#define FIELD_NAME_RF_DIR_PATH      "RF_DIR_PATH"

#define FIELD_NAME_FW_FILE_NAME     "FW_FILE_NAME"
#define FIELD_NAME_MPOS_POST_FIX    "_mpos"
#define FIELD_NAME_RF_FILE_NAME     "RF_FILE_NAME"

#define FIELD_OLD_FW_FILE           "FW_IMAGE"
#define FIELD_OLD_RF_FILE           "RFREG_FILE"
#define FIELD_OLD_FW_FILE_UFU       "USER_FW_IMAGE"
#define FIELD_OLD_RF_FILE_UFU       "USER_REG_IMAGE"

#define FILE_NAME_UFU_FW            "NFC_FW.bin"
#define FILE_NAME_UFU_RFREG         "NFC_REG.bin"

#define IMAGE_CODE_SIZE             3

#define IMAGE_OPTION_UFU            0x01
#define IMAGE_OPTION_OLD_HW         0x02

typedef unsigned int tIMAGE_TYPE;

typedef struct {
    tIMAGE_TYPE type;
    char *code;
    uint8_t *binary;
    unsigned int binary_length;
    uint8_t option;
} tIMAGE;

#define VERSION_LEN_FW  3
#define VERSION_LEN_RF  5

#define VERSION_MAX     5
typedef struct {
    int length;
    uint8_t version[VERSION_MAX];
} tVERSION;

#define STORAGE_MAX     256
typedef struct {
    tIMAGE *image1;
    tIMAGE *image2;
    tIMAGE *selected;
    char* chip_code;
    char* target_code;
    bool mPOS_mode;
    tIMAGE_TYPE type;
} tUPDATE_INFO;

// Temporary for adapting
static void set_chip_version(uint8_t *data, int length, tVERSION *version)
{
    int i;
    for (i = 0; i < length && i < VERSION_MAX; i++)
        version->version[i] = *data++;
    version->length = i;
}

static tVERSION chip_fw_version;
static tVERSION chip_rf_version;
void select_image_set_fw_version(uint8_t *data, int length)
{
    set_chip_version(data, length, &chip_fw_version);
}

void select_image_set_rf_version(uint8_t *data, int length)
{
    set_chip_version(data, length, &chip_rf_version);
}

static char chip_code[IMAGE_CODE_SIZE + 1];
void select_image_set_chip_code(char *code)
{
    strncpy(chip_code, code, IMAGE_CODE_SIZE);
    chip_code[IMAGE_CODE_SIZE] = '\0';
    OSI_logd("Chip code is %s", chip_code);
}

// Operations for code
static char* get_chip_code(void);
static tVERSION get_chip_version(tIMAGE_TYPE type);
static char* get_sales_code(void);  /* get CSC code */

static bool get_mPOS_mode(void);
static char* get_mPOS_code(void);
static bool is_mPOS_image(tIMAGE *image);

static char* get_storage(int type, int option);
static char *get_image_file_name(tIMAGE *image);
static char *get_image_file(tIMAGE *image, char *from);
static char *get_image_compat_field(tIMAGE *image);
static tIMAGE* get_image(tUPDATE_INFO *info, char *from, unsigned int option);
static int load_fw_binary(tIMAGE *image, char *file_name);
static int load_rf_binary(tIMAGE *image, char *file_name, char *target_code);

static tIMAGE* decide_image(tUPDATE_INFO *info);
static bool check_update(tUPDATE_INFO *info);

static bool exception_version_index(tIMAGE_TYPE type, int index);
static tIMAGE* get_high_ver_image(tIMAGE *image1, tIMAGE *image2);
static int version_compare(tIMAGE_TYPE type, tVERSION *ver1, tVERSION *ver2);
static tVERSION get_image_version(tIMAGE *image);

static void free_image(tIMAGE *image);
static void free_not_selected_image(tUPDATE_INFO *info);

static void print_version(char *name, tVERSION *ver);
static bool check_old_hw_exception(int type);

static char* get_default_code(void);

/****************
 * Code
 ***************/
static char* get_storage(int type, int option)
{
    static char ufu_storage[STORAGE_MAX];     /* UFU */
    static char sys_storage[STORAGE_MAX];     /* SYS */

    OSI_logd("Selecting %s image", (type == IMAGE_TYPE_FW) ? "FW" : "RF");

    if (option & IMAGE_OPTION_UFU)
    {
        if (get_config_string(FIELD_NAME_UFU_DIR_PATH, ufu_storage, STORAGE_MAX) > 0)
            return ufu_storage;
    }

    if (type == IMAGE_TYPE_FW)
    {
        if (get_config_string(FIELD_NAME_FW_DIR_PATH, sys_storage, STORAGE_MAX) > 0)
            return sys_storage;
    }
    else
    {
        if (get_config_string(FIELD_NAME_RF_DIR_PATH, sys_storage, STORAGE_MAX) > 0)
            return sys_storage;
    }
    return NULL;
}

uint8_t *nfc_hal_get_update_image(int type, bool force)
{
    tUPDATE_INFO info;
    char *ufu_storage = NULL;
    char *sys_storage = NULL;
    uint8_t *retImage = NULL;

    OSI_logd("Enter");

    memset(&info, 0, sizeof(info));

    info.chip_code = get_chip_code();
    info.mPOS_mode = get_mPOS_mode();
    info.type = type;

    if (check_old_hw_exception(type) == true)
    {
        info.mPOS_mode = false;
        info.target_code = get_default_code();
        info.selected = get_image(&info, NULL, IMAGE_OPTION_OLD_HW);
        OSI_logd("Old HW image is selected");
    }
    else
    {

        OSI_logd("Inform, chip code: %s", info.chip_code);
        OSI_logd("mPOS: %d, type: %d", info.mPOS_mode, info.type);
        OSI_logd("Sales code: %s", get_sales_code());

        ufu_storage = get_storage(type, IMAGE_OPTION_UFU);
        sys_storage = get_storage(type, 0);

        if (info.mPOS_mode)
        {
            OSI_logd("mPOS support!");
            info.target_code = get_mPOS_code();
            info.image1 = get_image(&info, ufu_storage, IMAGE_OPTION_UFU);
            info.image2 = get_image(&info, sys_storage, 0);

            if (!is_mPOS_image(info.image1) && !is_mPOS_image(info.image2))
            {
                free_image(info.image1);
                free_image(info.image2);
                if (!force && !memcmp(info.chip_code, get_mPOS_code(), IMAGE_CODE_SIZE))
                {
                    OSI_logd("Only current FW(RF) is already in mPOS mode");
                    return NULL;
                }

                OSI_logd("Failed to get mPOS image");
                info.mPOS_mode = false;
            }
        }

        /*
            mPOS mode should be double checked! If there is not mPOS image even mpos mode,
            the normal image (CSC or default) should be selected.
        */
        if (!info.mPOS_mode)
        {
            info.target_code = get_sales_code();
            OSI_logd("Target code: %s", info.target_code);

            OSI_logd("Try to load ufu image from %s", ufu_storage);
            info.image1 = get_image(&info, ufu_storage, IMAGE_OPTION_UFU);

            OSI_logd("Try to load sys image from %s", sys_storage);
            info.image2 = get_image(&info, sys_storage, 0);
        }

        info.selected = decide_image(&info);
        free_not_selected_image(&info);

        if (info.selected == info.image1)
            OSI_logd("UFU image is selected");
        else if (info.selected == info.image2)
            OSI_logd("SYS image is selected");
        else
        {
            OSI_loge("Cannot decide any image");
            return NULL;
        }
    }

    if (!force && !check_update(&info))
    {
#ifdef UNIT_TEST_REPORT
        print_unit_test_report(false);
#endif
        free_image(info.selected);
        return NULL;
    }

    OSI_logd("Need to update image");
    retImage = info.selected->binary;
    free(info.selected);

    return retImage;
}

static char* get_chip_code(void)
{
    // Temporary data
    // TODO: add get fw version to fw module
    return chip_code;
}

static tVERSION get_chip_version(tIMAGE_TYPE type)
{
    tVERSION version;
    memset(&version, 0, sizeof(version));

    if (type == IMAGE_TYPE_FW)
    {
        // Temporary data
        // TODO: add get fw version to fw module
        return chip_fw_version;
    }
    else if (type == IMAGE_TYPE_RF_REG)
    {
        // TODO: add get fw version to rf module
        return chip_rf_version;
    }

    return version;
}

static char* get_default_code(void)
{
    return DEFAULT_CODE;
}

static char* get_sales_code(void)
{
    char *sales_code = NULL;

#ifndef SEC_PRODUCT_SHIP
    {
        static char override_code[PROPERTY_VALUE_MAX] = {0};
        property_get("nfc.fw.dfl_ovrd", override_code, "");

        if (strlen(override_code) != 0)
        {
            OSI_logd("dynamicfwloading_override : %s", override_code);
            return override_code;
        }
    }
#endif

#ifdef TN
    sales_code = SecNativeFeature_getString(TAG_CSCFEATURE_NFC_CONFIGDYNAMICFIRMWARELOADING);
#endif
    if (sales_code == NULL || strlen(sales_code) == 0)
        return get_default_code();

    return sales_code;
}

static bool get_mPOS_mode(void)
{
    char rfreg_mode[PROPERTY_VALUE_MAX] = {0, };
    property_get("nfc.fw.rfreg_mode", rfreg_mode, "normal");
    return (strncmp(rfreg_mode, "mpos", sizeof("mpos")) == 0);
}

static char* get_mPOS_code(void)
{
    return MPOS_CODE;
}

static bool is_mPOS_image(tIMAGE *image)
{
    if (image == NULL || image->code == NULL)
        return false;
    return (memcmp(image->code, MPOS_CODE, sizeof(MPOS_CODE)) == 0);
}

static char *get_image_file_name(tIMAGE *image)
{
    static char file_name[50] = {0, };
    if (image->type == IMAGE_TYPE_FW)
    {
        if (image->option & IMAGE_OPTION_UFU)
            strncpy(file_name, FILE_NAME_UFU_FW, sizeof(FILE_NAME_UFU_FW));
        else
        get_config_string(FIELD_NAME_FW_FILE_NAME, file_name, sizeof(file_name));
    }
    else if (image->type == IMAGE_TYPE_RF_REG)
    {
        if (image->option & IMAGE_OPTION_OLD_HW)
            get_config_string(cfg_name_table[CFG_RFREG_FILE_FOR_OLD_HW], file_name, sizeof(file_name));
        else if (image->option & IMAGE_OPTION_UFU)
            strncpy(file_name, FILE_NAME_UFU_RFREG, sizeof(FILE_NAME_UFU_RFREG));
        else
            get_config_string(FIELD_NAME_RF_FILE_NAME, file_name, sizeof(file_name));
    }

    return file_name;
}

static char *get_image_compat_field(tIMAGE *image)
{
    if (image->option & IMAGE_OPTION_OLD_HW)
        return cfg_name_table[CFG_RFREG_FILE_FOR_OLD_HW];
    else if (image->type == IMAGE_TYPE_FW)
        return (image->option & IMAGE_OPTION_UFU) ?  FIELD_OLD_FW_FILE_UFU : FIELD_OLD_FW_FILE;
    else if (image->type == IMAGE_TYPE_RF_REG)
        return (image->option & IMAGE_OPTION_UFU) ?  FIELD_OLD_RF_FILE_UFU : FIELD_OLD_RF_FILE;
    return NULL;
}

static char *get_image_file(tIMAGE *image, char *from)
{
    static char file_path[256] = { 0, };    // FILE path max
    char *file_name = NULL;
    char *compat_old_field = NULL;
    struct stat attrib;

    if (from != NULL)
    {
        file_name = get_image_file_name(image);

        // Looking at sub-directory (Single SKU)
        if (image->code != get_default_code())
        {
            strncpy(file_path, from, sizeof(file_path) - 1);
            strncat(file_path, "/", 1);
            strncat(file_path, image->code, IMAGE_CODE_SIZE);
            strncat(file_path, "/", 1);
            strncat(file_path, file_name, sizeof(file_path) - strlen(file_path));

            if (stat(file_path, &attrib) == 0)
                return file_path;

            // if the file in sub-directory is not exist then set the code to default
            image->code = get_default_code();
        }

        // Looking at default root directory of storage
        strncpy(file_path, from, sizeof(file_path) - 1);
        strncat(file_path, "/", 1);
        strncat(file_path, file_name, sizeof(file_path) - strlen(file_path));
        if (stat(file_path, &attrib) == 0)
            return file_path;

        OSI_logd("File is not exist: %s", file_path);
    }

    // support old version configuration (HAL 2.0 conf)
    compat_old_field = get_image_compat_field(image);
    OSI_logd("Try to open old verson field name [%s]", compat_old_field);
    if (compat_old_field != NULL && get_config_string(compat_old_field, file_path, sizeof(file_path)) > 0)
    {
        image->code = get_default_code();
        return file_path;
    }

    return NULL;
}

static int load_fw_binary(tIMAGE *image, char *file_name)
{
    FILE *file;
    int binary_length;

    OSI_logd("Open: %s(%s)", file_name, image->code);
    if ((file = fopen(file_name, "rb")) == NULL)
    {
        OSI_loge("Failed to open F/W file (file: %s)", file_name);
        return -1;
    }

    // Get image size
    fseek(file, 0, SEEK_END);

    binary_length = ftell(file);

    if (binary_length <= 0)
        goto err_alloc;

    fseek(file, 0, SEEK_SET);
    image->binary_length = (unsigned int) binary_length;
    image->binary = (uint8_t *)malloc(image->binary_length);

    if (image->binary == NULL)
        goto err_alloc;

    // Read binary
    if (fread(image->binary, image->binary_length, 1, file) <= 0)
        goto err_read;

    fclose(file);
    return image->binary_length;

err_read:
    free(image->binary);
    image->binary = NULL;
err_alloc:
    fclose(file);
    return -1;
}

static int load_rf_binary(tIMAGE *image, char *file_name, char *target_code)
{
    int prop_header_size;
    int binary_length;

    if (image == NULL || file_name == NULL)
        return 0;

    prop_header_size = sizeof(image->binary_length) + 1;

    nfc_hal_rf_set_reg_id_tmp((uint8_t*)target_code);
    nfc_hal_rf_set_file_tmp(file_name, image->option);

    // TODO: tIMAGE structure should be move to upper layer header
    image->binary = (uint8_t *)malloc((size_t)(4 * 1024 + prop_header_size));    // + length info
    if (image->binary != NULL)
    {
        binary_length = nfc_hal_rf_get_reg(image->binary + prop_header_size, 4 * 1024);

        if (binary_length < 0)
        {
            free(image->binary);
            return -1;
        }
        image->binary_length = binary_length;

        memcpy(image->binary + 1, &image->binary_length, sizeof(image->binary_length));
        image->binary[0] = sizeof(image->binary_length);


        // Reset the code. If the image is one binary then image_code may be default. 
        if (nfc_hal_rf_is_one_binary())
        {
            if (nfc_hal_rf_is_default())
                image->code = get_default_code();
            else
                image->code = target_code;
        }
        else
        {
            /* For compativity old enviroment of system. ( > N8x)
             * Overwrite the register id to image's code */
            nfc_hal_rf_set_id(image->binary + prop_header_size, image->binary_length, image->code);
        }
    }


    return image->binary_length;
}

static tIMAGE* get_image(tUPDATE_INFO *info, char *from, unsigned int option)
{
    char *image_file;
    tIMAGE *new_image = NULL;

    if (info == NULL)
        return NULL;

    new_image = (tIMAGE *)malloc(sizeof(tIMAGE));

    if (new_image != NULL)
    {
        memset(new_image, 0, sizeof(tIMAGE));

        new_image->type = info->type;
        new_image->code = info->target_code;
        new_image->option = option;
        image_file = get_image_file(new_image, from);
        if (image_file == NULL)
        {
            OSI_loge("Failed to find image file (%p)", new_image);
            free(new_image);
            return NULL;
        }
            
        if(info->type == IMAGE_TYPE_FW)
        {
            if (load_fw_binary(new_image, image_file) < 0)
            {
                OSI_loge("Failed to load FW image!");
                free(new_image);
                return NULL;
            }
        }
        else if (info->type == IMAGE_TYPE_RF_REG)
        {
            if (load_rf_binary(new_image, image_file, info->target_code) < 0)
            {
                OSI_loge("Failed to load RF image!");
                free(new_image);
                return NULL;
            }
        }
    }

    OSI_logd("Success get image: %p", new_image);

    return new_image;
}

static tIMAGE* decide_image(tUPDATE_INFO *info)
{
    tIMAGE *ret_image = NULL;
    
    if (info == NULL)
        return NULL;

    if (info->image1 == NULL)
        return info->image2;
    else if (info->image2 == NULL)
        return info->image1;

    if (info->target_code == NULL || info->image1->code == NULL || info->image2->code == NULL)
        return get_high_ver_image(info->image1, info->image2);

    OSI_logd("Target code      : %c%c%c", info->target_code[0], info->target_code[1], info->target_code[2]);
    OSI_logd("Image1 code      : %c%c%c", info->image1->code[0], info->image1->code[1], info->image1->code[2]);
    OSI_logd("Image2 code      : %c%c%c", info->image2->code[0], info->image2->code[1], info->image2->code[2]);
    OSI_logd("Current Chip code: %c%c%c", info->chip_code[0], info->chip_code[1], info->chip_code[2]);

    if (!memcmp(info->image1->code, info->image2->code, IMAGE_CODE_SIZE))
        return get_high_ver_image(info->image1, info->image2);
    else if (!memcmp(info->image1->code, info->target_code, IMAGE_CODE_SIZE))
        return info->image1;

    return info->image2;
}

static bool exception_version_index(tIMAGE_TYPE type, int index)
{
    if (type == IMAGE_TYPE_FW)
    {
        switch (index)
        {
            case 1: // Customer key index.
                return true;
        }
    }
    return false;
}

static tIMAGE* get_high_ver_image(tIMAGE *image1, tIMAGE *image2)
{
    tVERSION ver1, ver2;

    if (image1 == NULL || image2 == NULL)
        return NULL;

    if (image1->type != image2->type)
        return NULL;

    OSI_logd("Check high version!");

    memset(&ver1, 0, sizeof(tVERSION));
    memset(&ver2, 0, sizeof(tVERSION));

    ver1 = get_image_version(image1);
    ver2 = get_image_version(image2);
    if (ver1.length != ver2.length)
        return NULL;

    if (version_compare(image1->type, &ver1, &ver2) >= 0)
        return image1;
    else
        return image2;

    // Same version
    return NULL;
}

static int version_compare(tIMAGE_TYPE type, tVERSION *ver1, tVERSION *ver2)
{
    int index;
    int ret = 0;

    if (ver1 == NULL || ver2 == NULL)
        return 0;

    for (index = 0; index < ver1->length && ret == 0; index++)
    {
        if (exception_version_index(type, index))
            continue;

        ret = ver1->version[index] - ver2->version[index];
    }
    return ret;
}

static tVERSION get_image_version(tIMAGE *image)
{
    tVERSION ver;
    uint8_t *p = NULL;

    memset(&ver, 0, sizeof(tVERSION));

    if (image == NULL || image->binary == NULL)
        return ver;

    if (image->type == IMAGE_TYPE_FW)
    {
        ver.length = VERSION_LEN_FW;
        memcpy(ver.version, image->binary + 0x10, VERSION_LEN_FW);
        OSI_logd("FW version (%p): %x.%x.%x", image,
            ver.version[0], ver.version[1], ver.version[2]);
    }
    else if (image->type == IMAGE_TYPE_RF_REG)
    {
        ver.length = VERSION_LEN_RF;
        //p = image->binary + image->binary_length - 16; // Get meta data
        p = image->binary + 1 + sizeof(image->binary_length);
        p += image->binary_length - 16;
        p += 5; // Move to version

        memcpy(ver.version, p, VERSION_LEN_RF);
        OSI_logd("RF version: (%p)%d/%d/%d/%d.%d.%d", image,
            (ver.version[0] >> 4) + 14, ver.version[0] & 0xF, ver.version[1],
            ver.version[2], ver.version[3], ver.version[4]);

    }

    return ver;
}

static bool check_update(tUPDATE_INFO *info)
{
    tVERSION ver_chip, ver_image;
    int update_mode = 0;

    if (info == NULL || info->selected == NULL)
        return false;

    if (info->chip_code == NULL)
    {
        OSI_logd("Cannot find chip code");
        return (info->selected != NULL);
    }

    ver_chip = get_chip_version(info->type);
    ver_image = get_image_version(info->selected);
#ifdef UNIT_TEST_REPORT
    ver_chip.utr_flag = UTR_FLAG_CHIP;
    ver_image.utr_flag = (info->selected == info->image1) ? UTR_FLAG_UFU : UTR_FLAG_SYS;
#endif

    print_version("Chip version ", &ver_chip);
    print_version("Image version", &ver_image);
    OSI_logd("selectd code: %s", info->selected->code);

    // Get update mode option
    if (get_config_int(cfg_name_table[CFG_UPDATE_MODE], &update_mode))
    {
        OSI_logd("Update mode is %d", update_mode);
        if (update_mode >= 2) // force update
        {
            OSI_logd("Force update by config option!");
            return true;
        }
    }

    /*
     * (image == mPOS) && (chip != mPOS): Update image  (mPOS image is only selected in mPOS mode)
     * (image != chip) && (chip != CSC) : Update image  (It means image is CSC or default)
     * (image != chip) && (chip == CSC) : Do not update (It means image is not CSC)
     * in other case system need to check version
     */
    if (is_mPOS_image(info->selected) && memcmp(info->chip_code, get_mPOS_code(), IMAGE_CODE_SIZE))
        return true;
    else if (memcmp(info->chip_code, info->selected->code, IMAGE_CODE_SIZE))
        return (memcmp(info->chip_code, get_sales_code(), IMAGE_CODE_SIZE) != 0);

    // By version check option from configuration
    if (update_mode == 0)
        return (version_compare(info->type, &ver_chip, &ver_image) != 0);
    return (version_compare(info->type, &ver_chip, &ver_image) < 0);
}

static void free_image(tIMAGE *image)
{
    if (image != NULL)
    {
        if (image->binary != NULL)
            free(image->binary);

        free(image);
    }
}

static void free_not_selected_image(tUPDATE_INFO *info)
{
    if (info->selected != info->image1)
        free_image(info->image1);

    if (info->selected != info->image2)
        free_image(info->image2);
}

static void print_version(char *name, tVERSION *ver)
{
    char printBuffer[100], *p;
    int i;
    p = printBuffer;

    for (i = 0; i < ver->length; i++)
        p += sprintf(p, "0x%02x.", ver->version[i]);

    OSI_logd("%s: %s", name, printBuffer);
}

static bool check_old_hw_exception(int type)
{
    char HWREV[PROPERTY_VALUE_MAX] = {0};
    char tmp[256];
    int cur_hw_ver;
    int old_hw_ver;

    if (type == IMAGE_TYPE_RF_REG)
    {
        property_get("ro.revision", HWREV, "none");
        OSI_logd("HWREV : %s", HWREV);
        cur_hw_ver = atoi(HWREV);

        if (get_config_int(cfg_name_table[CFG_RO_REVISION_FOR_OLD_HW], &old_hw_ver))
        {
            OSI_logd("CFG_RO_REVISION_FOR_OLD_HW : %d", old_hw_ver);
            if (cur_hw_ver <= old_hw_ver)
            {
                if (get_config_string(cfg_name_table[CFG_RFREG_FILE_FOR_OLD_HW], tmp, sizeof(tmp)))
                {
                    OSI_logd("set CFG_RFREG_FILE_FOR_OLD_HW successful");
                    return true;
                }
            }
        }
    }

    return false;
}
