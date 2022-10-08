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

htu21d_err_t htu21d_i2c_write_config(htu21d_config_t dt)
{
    uint8_t reg = REG_USER_WRITE;
    uint8_t data[2];
    data[0] = reg;
    data[1] = dt.msr_res_bit7   << 7 | 
              dt.chip_heat_en   << 2 |
              dt.otp_reload_dis << 1 |
              dt.msr_res_bit0;
    htu21d_err_t err = htu21d_i2c_hal_write(I2C_ADDRESS_HTU21D, data, 2);
    return err;
}

htu21d_err_t htu21d_i2c_read_config(uint8_t *dt)
{
    uint8_t reg = REG_USER_READ;
    htu21d_err_t err = htu21d_i2c_hal_read(I2C_ADDRESS_HTU21D, &reg, dt, 1);
    return err;
}

htu21d_err_t htu21d_i2c_reset()
{
    uint8_t reg = REG_SOFT_RESET;
    htu21d_err_t err = htu21d_i2c_hal_write(I2C_ADDRESS_HTU21D, reg, 1);
    htu21d_i2c_hal_ms_delay(4);
    return err;
} 

htu21d_err_t htu21d_i2c_temp_read(uint16_t *dt)
{
    uint8_t reg = REG_RTEMP_READ_HOLD;
    uint16_t data;
    htu21d_err_t err = htu21d_i2c_hal_read(I2C_ADDRESS_HTU21D, &reg, &data, 1);
    *dt = RTEMP_TO_TEMP(data); 
    return err;
}

htu21d_err_t htu21d_i2c_hum_read(uint16_t *dt)
{
    uint8_t reg = REG_RHUM_READ_HOLD;
    uint8_t data;
    htu21d_err_t err = htu21d_i2c_hal_read(I2C_ADDRESS_HTU21D, &reg, &data, 1);
    *dt = RTEMP_TO_TEMP(data);
    return err;
}