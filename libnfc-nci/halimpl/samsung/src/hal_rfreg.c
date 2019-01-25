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
 *   distributed under the License is distributed on n "S IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *   Author: Woonki Lee <woonki84.lee@samsung.com>
 *   Version: 2.1
 *
 */

#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>

#include "osi.h"
#include "hal.h"
#include "util.h"

char MAGIC_NUMBER[] = { 0x53, 0x52, 0x6F, 0x62 };
// RF register - special information length
#define RFREG_META_FW_VERSION_LENGTH    2
#define RFREG_META_PROJECT_NO_LENGTH    1
#define RFREG_META_RF_VERSION_LENGTH    2
#define RFREG_META_BUILD_TIME_LENGTH    5
#define RFREG_META_BRANCH_NO_LENGTH     1
#define RFREG_META_MINOR_VERSION_LENGTH 1
#define RFREG_META_TARGET_INFOR_LENGTH  3
#define RFREG_META_RFU_LENGTH           1
#define RFREG_META_DATA_LENGTH          16

// RF register - special information address
#define RFREG_META_FW_VERSION           0
#define RFREG_META_PROJECT_NO           ((RFREG_META_FW_VERSION) + (RFREG_META_FW_VERSION_LENGTH))
#define RFREG_META_RF_VERSION           ((RFREG_META_PROJECT_NO) + (RFREG_META_PROJECT_NO_LENGTH))
#define RFREG_META_BUILDTIME            ((RFREG_META_RF_VERSION) + (RFREG_META_RF_VERSION_LENGTH))
#define RFREG_META_BRANCH_NO            ((RFREG_META_BUILDTIME) + (RFREG_META_BUILD_TIME_LENGTH))
#define RFREG_META_MINOR_VERSION        ((RFREG_META_BRANCH_NO) + (RFREG_META_BRANCH_NO_LENGTH))
#define RFREG_META_TARGET_INFOR         ((RFREG_META_MINOR_VERSION) + (RFREG_META_MINOR_VERSION_LENGTH))
#define RFREG_META_RFU                  ((RFREG_META_TARGET_INFOR) + (RFREG_META_TARGET_INFOR_LENGTH))

// RF one binary field's length
#define RFONE_MAGIC_NUMBER_LENGTH       sizeof(MAGIC_NUMBER)
#define RFONE_FILE_SIZE_LENGTH          4
#define RFONE_VERSION_LENGTH            6
#define RFONE_OPTION_LENGTH             1
#define RFONE_COUNT_LENGTH              1
#define RFONE_BASE_REG_SIZE_LENGTH      2

#define RFONE_DELTA_ID_LENGTH           3
#define RFONE_DELTA_COUNT_LENGTH        1
#define RFONE_DELTA_FINAL_SIZE_LENGTH   2

#define RFONE_ALR_ADDRESS_LENGTH        2
#define RFONE_ALR_LEN_LENGTH            1

// RF one binary field's address
#define RFONE_MAGIC_NUMBER              0
#define RFONE_FILE_SIZE                 ((RFONE_MAGIC_NUMBER) + (RFONE_MAGIC_NUMBER_LENGTH))
#define RFONE_VERSION                   ((RFONE_FILE_SIZE) + (RFONE_FILE_SIZE_LENGTH))
#define RFONE_OPTION                    ((RFONE_VERSION) + (RFONE_VERSION_LENGTH))
#define RFONE_COUNT                     ((RFONE_OPTION) + (RFONE_OPTION_LENGTH))
#define RFONE_BASE_REG_SIZE             ((RFONE_COUNT) + (RFONE_COUNT_LENGTH))
#define RFONE_BASE_REG_START            ((RFONE_BASE_REG_SIZE) + (RFONE_BASE_REG_SIZE_LENGTH))

#define RFONE_DELTA_ID                  0
#define RFONE_DELTA_COUNT               ((RFONE_DELTA_ID) + (RFONE_DELTA_ID_LENGTH))
#define RFONE_DELTA_FINAL_SIZE          ((RFONE_DELTA_COUNT) + (RFONE_DELTA_COUNT_LENGTH))

#define RFONE_ALR_ADDRESS               0
#define RFONE_ALR_LEN                   ((RFONE_ALR_ADDRESS) + (RFONE_ALR_ADDRESS_LENGTH))
#define RFONE_ALR_REG                   ((RFONE_ALR_LEN) + (RFONE_ALR_LEN_LENGTH))

// RF one binary header size
#define RFONE_FILE_HEADER_SIZE          ((RFONE_BASE_REG_SIZE) + (RFONE_BASE_REG_SIZE_LENGTH))
#define RFONE_DELTA_HEADER_SIZE         ((RFONE_DELTA_FINAL_SIZE) + (RFONE_DELTA_FINAL_SIZE_LENGTH))
#define RFONE_ALR_HEADER_SIZE           ((RFONE_ALR_LEN) + (RFONE_ALR_LEN_LENGTH))

typedef struct {
    // common fields
    FILE        *file;
    int         file_size;
    bool        is_one_binary;

    // Only for one binary fields
    struct {
        uint8_t     file_version[RFONE_VERSION_LENGTH];
        uint8_t     file_options[RFONE_OPTION_LENGTH];
        int         delta_count;
        int         reg_size;
        int         reg_start_addr;
        int         delta_start_addr;
    };
} tNFC_RF_BINARY;

typedef struct {
    uint8_t     id[RFONE_DELTA_ID_LENGTH];
    int         count;
    int         final_size;
    int         alr_start_addr;
} tNFC_RFONE_DELTA;

// Utilities
static inline int copy_stream_to_int(uint8_t *stream, int length);

// Register handle
static uint8_t *get_meta_data(uint8_t *reg, int size);
static void set_id_to_rf_reg(uint8_t *reg, int size, uint8_t *id);

// File operations
static FILE *find_and_open_rf_reg();
static tNFC_RF_BINARY get_binary_information(FILE *file);
static bool fill_one_binary_base_register(tNFC_RF_BINARY *binary, uint8_t *buffer, int buffer_size);
static tNFC_RFONE_DELTA find_delta_record(tNFC_RF_BINARY *binary, uint8_t* id, int id_size);

// Get file information
static int get_file_size(uint8_t *binary);
static bool get_version(uint8_t *binary, uint8_t *buffer);
static bool get_option(uint8_t *binary, uint8_t *buffer);
static int get_count(uint8_t *binary);
static int get_base_reg_size(uint8_t *binary);
static bool get_base_reg(uint8_t *binary, uint8_t *buffer, uint8_t size);
static bool check_magic_number(uint8_t *binary);
static bool check_file_size(uint8_t *binary, int size);
static bool check_one_binary(uint8_t *binary, int file_size);

// Temporary functions
uint8_t* tmp_reg_id = NULL;
uint8_t* nfc_hal_rf_get_reg_id_tmp(void)
{
    OSI_logd("ID: %s", tmp_reg_id);
    return tmp_reg_id;
}

void nfc_hal_rf_set_reg_id_tmp(uint8_t *new_id)
{
    tmp_reg_id = new_id;
    OSI_logd("ID: %s", tmp_reg_id);
}

char* tmp_file_name = NULL;
uint8_t tmp_file_option = 0;
char* nfc_hal_rf_get_file_name_tmp(void)
{
    OSI_logd("file name: %s", tmp_file_name);
    return tmp_file_name;
}

void nfc_hal_rf_set_file_tmp(char *new_file_name, uint8_t option)
{
    tmp_file_name = new_file_name;
    tmp_file_option = option;
    OSI_logd("file name: %s", tmp_file_name);
    OSI_logd("file option: %d", tmp_file_option);
}

bool is_default = false;
bool nfc_hal_rf_is_default(void)
{
    return is_default;
}

bool is_one_binary = false;
bool nfc_hal_rf_is_one_binary(void)
{
    return is_one_binary;
}

void nfc_hal_rf_set_id(uint8_t *reg, int size, uint8_t *id)
{
    set_id_to_rf_reg(reg, size, id);
}
// End temp

// APIs
int nfc_hal_rf_get_reg(uint8_t *reg_buffer, int reg_buffer_size)
{
    tNFC_RF_BINARY binary;
    tNFC_RFONE_DELTA delta;
    FILE *file;
    uint8_t alr_header[RFONE_ALR_HEADER_SIZE] = {0, };
    uint8_t *reg = NULL;
    int alr_address;
    unsigned int alr_length;

    if (reg_buffer == NULL)
        return -1;

    if ((file = find_and_open_rf_reg()) == NULL)
    {
        OSI_loge("Cannot open rf register file!!");
        return -1;
    }

    binary = get_binary_information(file);
    OSI_logd("file size: %d", binary.file_size);
    is_one_binary = binary.is_one_binary;

    if (binary.is_one_binary == true)
    {
        OSI_logd("This is one binary!");
        OSI_logd(" - version: %d.%d.%d.%d.%d.%d", binary.file_version[0], binary.file_version[1], 
                binary.file_version[2], binary.file_version[3], binary.file_version[4], binary.file_version[5]);
        OSI_logd(" - options: 0x%02X", binary.file_options[0]);
        OSI_logd(" - reg_start_addr: 0x%04X", binary.reg_start_addr);
        OSI_logd(" - reg_size: 0x%04X", binary.reg_size);
        OSI_logd(" - delta_start_addr: 0x%04X", binary.delta_start_addr);
        OSI_logd(" - delta_count: 0x%04X", binary.delta_count);

        if (!fill_one_binary_base_register(&binary, reg_buffer, reg_buffer_size))
        {
            OSI_loge("failed to get RF base register");
            goto fail;
        }

        OSI_logd("Find delta record");
        delta = find_delta_record(&binary, nfc_hal_rf_get_reg_id_tmp(), RFONE_DELTA_ID_LENGTH);

        if (delta.alr_start_addr > 0)
        {
            OSI_logd("delta record is found");
            OSI_logd(" - ID: %c%c%c", delta.id[0], delta.id[1], delta.id[2]);
            OSI_logd(" - ALR addr: 0x%04X", delta.alr_start_addr);
            OSI_logd(" - Final Size: %d", delta.final_size);
            if (fseek(file, delta.alr_start_addr, SEEK_SET) < 0)
            {
                OSI_loge("Invalid ALR address");
                memset(&delta, 0, sizeof(delta));
            }
            is_default = false;
        }
        else
        {
            OSI_logd("Not found delta record. Use base register set (default)");
            is_default = true;
        }

        // Overwrite ALRs to register
        while (delta.count-- > 0)
        {
            if (fread(alr_header, 1, RFONE_ALR_HEADER_SIZE, file) != RFONE_ALR_HEADER_SIZE)
                break;

            alr_address = copy_stream_to_int(alr_header + RFONE_ALR_ADDRESS, RFONE_ALR_ADDRESS_LENGTH);

            if (alr_header[RFONE_ALR_LEN] == 0 || alr_header[RFONE_ALR_LEN] > 255) 
                break;

            alr_length = alr_header[RFONE_ALR_LEN];
            if (fread(reg_buffer + alr_address, 1, alr_length, file) != alr_length)
                break;
        }
        // Get REG!!
    }
    else
    {
        OSI_logd("This is normal rf register file");
        if (fseek(file, 0, SEEK_SET) < 0)
            goto fail;

        if (fread(reg_buffer, 1, binary.file_size, file) != (size_t)binary.file_size)
            goto fail;

        binary.reg_size = binary.file_size;
        is_default = false;
    }

    // Set ID to META data
    OSI_logd("Write ID to meta data");
    if (!is_default)
        set_id_to_rf_reg(reg_buffer, binary.reg_size, nfc_hal_rf_get_reg_id_tmp());
    else
        set_id_to_rf_reg(reg_buffer, binary.reg_size, "DEF" /* get_default_code */);
    
    fclose(file);
    return binary.reg_size;
fail:
    OSI_loge("failed to get RF register set");
    fclose(file);
    return -1;
}

/****************************
 * Utilities
 ***************************/
static inline int copy_stream_to_int(uint8_t *stream, int length)
{
    int i, ret;
    if (stream == NULL || length > 4 || length < 0)
        return 0;

    ret = 0;
    for (i = 0; i < length; i++)
        ret += (stream[i] << (8*(length-1-i)));

    return ret;
}

/****************************
 * Register handle
 ***************************/
static uint8_t *get_meta_data(uint8_t *reg, int size)
{
    return reg + (size - RFREG_META_DATA_LENGTH);
}

static void set_id_to_rf_reg(uint8_t *reg, int size, uint8_t *id)
{
    uint8_t *meta = NULL;
    if (reg == NULL || size < RFREG_META_DATA_LENGTH || id == NULL)
        return;

    meta = get_meta_data(reg, size);
    memcpy(meta + RFREG_META_TARGET_INFOR, id, RFREG_META_TARGET_INFOR_LENGTH);
}

/****************************
 * File operations
 ***************************/
static FILE *find_and_open_rf_reg()
{
    FILE *file;
    struct stat attrib;
    //char file_name[256];
    char *file_name = NULL;

    // get rf reg
    /*
    if (!get_config_string(cfg_name_table[CFG_RFREG_FILE], file_name, sizeof(file_name)))
        return NULL;
    */
    file_name = nfc_hal_rf_get_file_name_tmp();

    // is exist 
    if (stat(file_name, &attrib) != 0)
        return NULL;

    // Open RF binary
    if ((file = fopen(file_name, "rb")) == NULL)
        return NULL;
    
    return file;
}

static tNFC_RF_BINARY get_binary_information(FILE *file)
{
    tNFC_RF_BINARY new_binary;
    uint8_t buffer[RFONE_FILE_HEADER_SIZE];

    memset(&new_binary, 0, sizeof(new_binary));
    new_binary.is_one_binary = false;

    if (file == NULL)
        return new_binary;

    new_binary.file = file;

    // Get header information
    if (fseek(file, 0, SEEK_SET) < 0)
        return new_binary;

    if (fread(buffer, 1, RFONE_FILE_HEADER_SIZE, file) != RFONE_FILE_HEADER_SIZE)
        return new_binary;

    // Get size
    if (fseek(file, 0, SEEK_END) < 0)
        return new_binary;
    new_binary.file_size = (int)ftell(file);

    if (check_one_binary(buffer, new_binary.file_size))
    {
        get_version(buffer, new_binary.file_version);
        get_option(buffer, new_binary.file_options);

        new_binary.reg_start_addr = RFONE_BASE_REG_START;
        new_binary.reg_size = get_base_reg_size(buffer);

        new_binary.delta_start_addr = new_binary.reg_start_addr + new_binary.reg_size;
        new_binary.delta_count = get_count(buffer);

        new_binary.is_one_binary = true;
    }

    return new_binary;
}

static bool fill_one_binary_base_register(tNFC_RF_BINARY *binary, uint8_t *buffer, int buffer_size)
{
    if (binary == NULL || binary->file == NULL || binary->is_one_binary == false)
        return false;

    if (buffer_size < binary->reg_size)
        return false;

    if (fseek(binary->file, binary->reg_start_addr, SEEK_SET) >= 0)
        if (fread(buffer, 1, binary->reg_size, binary->file) == (size_t)binary->reg_size)
            return true;

    return false;
}

static tNFC_RFONE_DELTA find_delta_record(tNFC_RF_BINARY *binary, uint8_t* id, int id_size)
{
    tNFC_RFONE_DELTA delta;
    uint8_t buffer[RFONE_DELTA_HEADER_SIZE];
    int count;

    memset(&delta, 0, sizeof(delta));
    if (binary == NULL || binary->file == NULL || binary->is_one_binary == false || id == NULL || id_size <= 0)
        return delta;

    if (fseek(binary->file, binary->delta_start_addr, SEEK_SET) < 0)
        return delta;

    for (count = 0; count < binary->delta_count; count++)
    {
        memset(&delta, 0, sizeof(delta));
        if (fread(buffer, 1, RFONE_DELTA_HEADER_SIZE, binary->file) != RFONE_DELTA_HEADER_SIZE)
            break;

        memcpy(&delta.id, buffer + RFONE_DELTA_ID, RFONE_DELTA_ID_LENGTH);
        delta.count = copy_stream_to_int(buffer + RFONE_DELTA_COUNT, RFONE_DELTA_COUNT_LENGTH);

        if (!memcmp(id, delta.id, id_size))
        {
            delta.final_size = copy_stream_to_int(buffer + RFONE_DELTA_FINAL_SIZE, RFONE_DELTA_FINAL_SIZE_LENGTH);
            delta.alr_start_addr = (int)ftell(binary->file);
            // Find!
            break;
        }

        // Skip all of ALR
        while (delta.count-- > 0)
        {
            if (fread(buffer, 1, RFONE_ALR_HEADER_SIZE, binary->file) == RFONE_ALR_HEADER_SIZE)
            {
                if (fseek(binary->file, buffer[RFONE_ALR_LEN], SEEK_CUR) == 0)
                    continue;
            }

            // Err
            memset(&delta, 0, sizeof(delta));
            return delta;
        }
    }

    return delta;
}

/****************************
 * Get file informations
 ***************************/
static int get_file_size(uint8_t *binary)
{
    return copy_stream_to_int(binary + RFONE_FILE_SIZE, RFONE_FILE_SIZE_LENGTH);
}

static bool get_version(uint8_t *binary, uint8_t *buffer)
{
    if (binary == NULL || buffer == NULL)
        return false;

    memcpy(buffer, binary + RFONE_VERSION, RFONE_VERSION_LENGTH);
    return true;
}

static bool get_option(uint8_t *binary, uint8_t *buffer)
{
    if (binary == NULL || buffer == NULL)
        return false;

    memcpy(buffer, binary + RFONE_OPTION, RFONE_OPTION_LENGTH);
    return true;
}

static int get_count(uint8_t *binary)
{
    if (binary == NULL)
        return -1;

    return (int)binary[RFONE_COUNT];
}

static int get_base_reg_size(uint8_t *binary)
{
    return copy_stream_to_int(binary + RFONE_BASE_REG_SIZE, RFONE_BASE_REG_SIZE_LENGTH);
}

static bool get_base_reg(uint8_t *binary, uint8_t *buffer, uint8_t size)
{
    int len;
    if (binary == NULL || buffer == NULL)
        return false;

    len = get_base_reg_size(binary);
    if (size < get_base_reg_size(binary))
        return false;

    memcpy(buffer, binary + RFONE_BASE_REG_SIZE, len);
    return true;
}

static bool check_magic_number(uint8_t *binary)
{
    int addr = RFONE_MAGIC_NUMBER;
    int i;

    if (binary == NULL)
        return false;

    for (i = 0; i < (int)RFONE_MAGIC_NUMBER_LENGTH; i++)
    {
        if (MAGIC_NUMBER[i] != binary[addr + i])
            return false;
    }
    return true;
}

static bool check_file_size(uint8_t *binary, int size)
{
    if (binary == NULL)
        return false;

    if (get_file_size(binary) != size)
        return false;
    return true;
}

static bool check_one_binary(uint8_t *binary, int file_size)
{
    if (binary != NULL)
        if (check_magic_number(binary))
            if (check_file_size(binary, file_size))
                return true;

    return false;
}
