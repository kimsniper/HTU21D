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
#include "stm32f4xx_gpio.h"
#include "main.h"

/* I2C User Defines */
#define I2C_SCL         GPIO_Pin_6
#define I2C_SDA         GPIO_Pin_7
#define I2C_CLK_SPEED   400000

int16_t htu21d_i2c_hal_init()
{
    int16_t err = HTU21D_OK;

    //User implementation here

    GPIO_InitTypeDef GPIO_InitStruct;
    I2C_InitTypeDef I2C_InitStruct;

    /* Enable GPIOx Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    // Initialize pins as alternating function
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Enables the specified I2C peripheral. */
    I2C_Cmd(I2C1, ENABLE);

    /* Initialise I2C */
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0x78;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Disable ;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStruct.I2C_ClockSpeed = I2C_CLK_SPEED;
    I2C_Init(I2C1, &I2C_InitStruct);

    return err == HTU21D_OK ? HTU21D_OK :  HTU21D_ERR;
}

int16_t htu21d_i2c_hal_read(uint8_t address, uint8_t *reg, uint8_t *data, uint16_t count)
{
    int16_t err = HTU21D_OK;

    //User implementation here
    
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, address << 1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ));
    I2C_GenerateSTOP(I2C1, ENABLE);

    htu21d_i2c_hal_ms_delay(60);
    
    I2C_GenerateSTART(I2C1, ENABLE);
    I2C_SendData(I2C1, address << 1);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED ));
    while(count > 0)
    {
      while(! I2C_GetFlagStatus(I2C1,I2C_FLAG_TXE));
      *data = I2C_ReceiveData(I2C1);
      data++;
      count--;
      while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED ));
    }
    I2C_GenerateSTOP(I2C1, ENABLE);

    return err == HTU21D_OK ? HTU21D_OK :  HTU21D_ERR;
}

int16_t htu21d_i2c_hal_write(uint8_t address, uint8_t *data, uint16_t count)
{
    int16_t err = HTU21D_OK;

    //User implementation here
    
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, address << 1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ));

    while(count > 0)
    {
      while(! I2C_GetFlagStatus(I2C1,I2C_FLAG_TXE));
      I2C_SendData(I2C1, *data);
      data++;
      count--;
      while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED ));
    }
    I2C_GenerateSTOP(I2C1, ENABLE);

    return err == HTU21D_OK ? HTU21D_OK :  HTU21D_ERR;
}

void htu21d_i2c_hal_ms_delay(uint32_t ms) {
    //User implementation here
    Delay(ms);
}
