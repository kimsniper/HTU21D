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

#include "htu21d_i2c_hal.h" 

/* Hardware Specific Components */
#include "stm32f4xx_hal.h"
/* I2C User Defines */
I2C_HandleTypeDef hi2c1;

htu21d_err_t htu21d_i2c_hal_init()
{
    int err = HTU21D_OK;

    //User implementation here
    hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		err = HTU21D_ERR;
	}

    return err == HTU21D_OK ? HTU21D_OK :  HTU21D_ERR;
}

htu21d_err_t htu21d_i2c_hal_read(uint8_t address, uint8_t *reg, uint8_t *data, uint16_t count)
{
    int err = HTU21D_OK;

    //User implementation here

    err = HAL_I2C_Master_Transmit(&hi2c1, address<<1, reg, 1, HAL_MAX_DELAY);
    htu21d_i2c_hal_ms_delay(60);
    err += HAL_I2C_Master_Receive(&hi2c1, address<<1, data, count, HAL_MAX_DELAY);

    return err == HTU21D_OK ? HTU21D_OK :  HTU21D_ERR;
}

htu21d_err_t htu21d_i2c_hal_write(uint8_t address, uint8_t *data, uint16_t count)
{
    int err = HTU21D_OK;

    //User implementation here

    err = HAL_I2C_Master_Transmit(&hi2c1, address<<1, data, count, HAL_MAX_DELAY);

    return err == HTU21D_OK ? HTU21D_OK :  HTU21D_ERR;
}

void htu21d_i2c_hal_ms_delay(uint32_t ms) {
    //User implementation here
	HAL_Delay(ms);
}
