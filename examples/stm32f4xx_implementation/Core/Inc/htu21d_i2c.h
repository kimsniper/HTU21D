/*
 * Copyright (c) 2022, Mezael Docoy
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EXAMPLES_ESP32_IMPLEMENTATION_MAIN_htu21d_I2C
#define EXAMPLES_ESP32_IMPLEMENTATION_MAIN_htu21d_I2C

#ifdef __cplusplus
extern "C" {
#endif

#include "htu21d_i2c_hal.h" 
#include <math.h>

typedef struct{
    float temp;
    float hum;
} htu21d_data_t;

typedef struct{
    uint8_t msr_res_bit7 : 1;
    uint8_t batt_sts : 1;
    uint8_t res : 3;
    uint8_t chip_heat_en : 1;
    uint8_t otp_reload_dis : 1;
    uint8_t msr_res_bit0 : 1;
} htu21d_config_t;

typedef enum{
    REG_RESOLUTION_HUM12_TEMP14 = 0x00,
    REG_RESOLUTION_HUM8_TEMP12 = 0x01,
    REG_RESOLUTION_HUM10_TEMP13 = 0x02,
    REG_RESOLUTION_HUM11_TEMP11 = 0x03,
} htu21d_resolution_t;

/**
 * @brief HTU21D I2C slave address
 */
#define I2C_ADDRESS_HTU21D              0x40

/**
 * @brief HTU21D command code registers.
 * @details R/W Command registers
 */
#define REG_RTEMP_READ_HOLD             0xE3
#define REG_RHUM_READ_HOLD              0xE5
#define REG_RTEMP_READ                  0xF3
#define REG_RHUM_READ                   0xF5
#define REG_USER_WRITE                  0xE6
#define REG_USER_READ                   0xE7
#define REG_SOFT_RESET                  0xFE

/**
 * @brief HTU21D Humidity and Temperature conversion formula
 */
#define RHUM_TO_HUM(_rhum)              (125 * (_rhum/(pow(2,16)))) - 6
#define RTEMP_TO_TEMP(_rtemp)           (175.72 * (_rtemp/(pow(2,16)))) - 46.85

/**
 * @brief Read HTU21D parameters
 */
htu21d_err_t htu21d_i2c_read_config(uint8_t *dt);

/**
 * @brief Set HTU21D resolution
 */
htu21d_err_t htu21d_i2c_set_resolution(htu21d_resolution_t dt);

/**
 * @brief Read HTU21D resolution
 */
htu21d_err_t htu21d_i2c_get_resolution(htu21d_resolution_t *dt);

/**
 * @brief HTU21D reset
 */
htu21d_err_t htu21d_i2c_reset();

/**
 * @brief HTU21D temperature read in deg C
 */
htu21d_err_t htu21d_i2c_temp_read(float *dt);

/**
 * @brief HTU21D relative humidity read
 */
htu21d_err_t htu21d_i2c_hum_read(float *dt);

#ifdef __cplusplus
}
#endif

#endif /* EXAMPLES_ESP32_IMPLEMENTATION_MAIN_htu21d_I2C */
