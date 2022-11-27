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

#include "math.h"

#include "htu21d_i2c.h" 
#include "htu21d_i2c_hal.h" 
#include "crc_calc.h"

htu21d_err_t htu21d_i2c_read_config(uint8_t *dt)
{
    uint8_t reg = REG_USER_READ;
    htu21d_err_t err = htu21d_i2c_hal_read(I2C_ADDRESS_HTU21D, &reg, dt, 1);
    return err;
}

htu21d_err_t htu21d_i2c_set_resolution(htu21d_resolution_t dt)
{
    uint8_t reg = REG_USER_WRITE;
    uint8_t data[2], cfg_mask;
    htu21d_err_t err = htu21d_i2c_read_config(&cfg_mask);
    if (err != HTU21D_OK) return err;
    data[0] = reg;
    data[1] = (cfg_mask & 0x7E) | (dt & (1<<0)) | ((dt & (1<<1)) << 6);
    err = htu21d_i2c_hal_write(I2C_ADDRESS_HTU21D, data, 2);
    return err;
}

htu21d_err_t htu21d_i2c_get_resolution(htu21d_resolution_t *dt)
{
    uint8_t reg = REG_USER_READ;
    uint8_t data;
    htu21d_err_t err = htu21d_i2c_hal_read(I2C_ADDRESS_HTU21D, &reg, &data, 1);   
    *dt = ((data & (1<<7)) >> 6) | (data & (1<<0));
    return err;
}

htu21d_err_t htu21d_i2c_reset()
{
    uint8_t reg = REG_SOFT_RESET;
    htu21d_err_t err = htu21d_i2c_hal_write(I2C_ADDRESS_HTU21D, &reg, 1);
    return err;
} 

htu21d_err_t htu21d_i2c_temp_read(float *dt)
{
    uint8_t reg = REG_RTEMP_READ_HOLD;
    uint8_t data[3];
    htu21d_err_t err = htu21d_i2c_hal_read(I2C_ADDRESS_HTU21D, &reg, data, 3);
    uint16_t data_raw = (data[0] << 8) | data[1];
    uint8_t crc = data[2];

    if(crc_check(data_raw, crc) == CRC_NOTMATCH) return HTU21D_CRC_ERR;

    data_raw &= 0xFFFC;
    *dt = RTEMP_TO_TEMP(data_raw); 
    return err;
}

htu21d_err_t htu21d_i2c_hum_read(float *dt)
{
    uint8_t reg = REG_RHUM_READ_HOLD;
    uint8_t data[3];
    htu21d_err_t err = htu21d_i2c_hal_read(I2C_ADDRESS_HTU21D, &reg, data, 3);
    uint16_t data_raw = (data[0] << 8) | data[1];
    uint8_t crc = data[2];

    if(crc_check(data_raw, crc) == CRC_NOTMATCH) return HTU21D_CRC_ERR;

    data_raw &= 0xFFFC;
    *dt = RHUM_TO_HUM(data_raw);
    return err;
}