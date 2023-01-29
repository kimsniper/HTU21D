#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"
#include <stdio.h>
#include <string.h>

//htu21d components
#include "htu21d_i2c.h"
#include "htu21d_i2c_hal.h"
#include "ftoa.h"

//Macro
#define LED_PC13        GPIO_Pin_13
#define PUSH_BUTTON     GPIO_Pin_0

static __IO uint32_t TimingDelay;

/* Delay functions */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0)
  { 
    TimingDelay--;
  }
}

static void sysTick_initialize()
{
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
}

void tim_initialize(uint16_t tm_ms)
{
  NVIC_InitTypeDef NVIC_InitDef;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  NVIC_InitDef.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitDef.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitDef.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitDef.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitDef);
  
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseDef;
  
  uint16_t tm_prescaler = 7200;
  uint16_t tm_period = 2 * tm_ms * (25000 / tm_prescaler);

  TIM_TimeBaseDef.TIM_Period = tm_period;
  TIM_TimeBaseDef.TIM_Prescaler = tm_prescaler - 1;
  TIM_TimeBaseDef.TIM_ClockDivision = 0;
  TIM_TimeBaseDef.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseDef);
  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
  TIM_Cmd(TIM3, ENABLE);
}

void uart_initialize()
{
  GPIO_InitTypeDef     GPIO_InitStruct;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
   
  // Initialize pins as alternating function
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

  USART_InitTypeDef USART_InitStruct;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
   
  USART_InitStruct.USART_BaudRate = 115200;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_Init(USART1, &USART_InitStruct);
  USART_Cmd(USART1, ENABLE);
}

void print(char *str)
{
  uint8_t len = strlen(str);
  while(len > 0)
  {
    while(! USART_GetFlagStatus(USART1,USART_FLAG_TXE));
    USART_SendData(USART1, *str);
    str++;
    len--;
    while( ! USART_GetFlagStatus(USART1,USART_FLAG_TC));
  }
}

int main()
{
  RCC_HSEConfig(RCC_HSE_ON);
  while (!RCC_WaitForHSEStartUp());
  sysTick_initialize();
  uart_initialize();
  
  int16_t err;
  htu21d_data_t htu_data = {0};
  
  htu21d_i2c_hal_init();
  
  htu21d_i2c_hal_ms_delay(30);

  err = htu21d_i2c_reset();
  if(err != HTU21D_OK) 
    print("Error resetting the device!\n\r");
  htu21d_i2c_hal_ms_delay(30);   
  
  if(err != HTU21D_OK) 
    print("Error setting the device!\n\r");
  
  if (err == HTU21D_OK)
  {
    print("HTU21D initialization successful\n\r");
    //Entering while loop
    
    while(1)
    {
      //Read temp and humidity
      err = htu21d_i2c_temp_read(&htu_data.temp);
      err += htu21d_i2c_hum_read(&htu_data.hum);
      if(err == HTU21D_OK)
      {
        char temp_to_string[10] = {0};
        char hum_to_string[10] = {0};
        print("Temperature: %.01f°C");
        ftoa(htu_data.temp, temp_to_string, 4);
        print(temp_to_string);
        print("\n\r");
        print("Humidity: %.01f%%");
        ftoa(htu_data.hum, hum_to_string, 4);
        print(hum_to_string);
        print("\n\r");
      }
      else{
        print("Data read error!\n\r");
      }
      Delay(1000);
    }
  }
  
  return 1;
}