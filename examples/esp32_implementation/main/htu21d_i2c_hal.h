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

#ifndef EXAMPLES_ESP32_IMPLEMENTATION_MAIN_htu21d_I2C_HAL
#define EXAMPLES_ESP32_IMPLEMENTATION_MAIN_htu21d_I2C_HAL

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

typedef enum{
    HTU21D_ERR = -1,
    HTU21D_OK,
} htu21d_err_t;

/**
 * @brief User implementation for I2C initialization.
 * @details To be implemented by user based on hardware platform.
 */
htu21d_err_t htu21d_i2c_hal_init();

/**
 * @brief User implementation for I2C read.
 * @details To be implemented by user based on hardware platform.
 */
htu21d_err_t htu21d_i2c_hal_read(uint8_t address, uint8_t *reg, uint8_t *data, uint16_t count);

/**
 * @brief User implementation for I2C write.
 * @details To be implemented by user based on hardware platform.
 */
htu21d_err_t htu21d_i2c_hal_write(uint8_t address, uint8_t *data, uint16_t count);

/**
 * @brief User implementation for milliseconds delay.
 * @details To be implemented by user based on hardware platform.
 */
void htu21d_i2c_hal_ms_delay(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* EXAMPLES_ESP32_IMPLEMENTATION_MAIN_htu21d_I2C_HAL */
