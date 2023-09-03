/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "app_log.h"
#include "htu21d_i2c.h"
#include "htu21d_i2c_hal.h"
#include "app.h"

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  sl_status_t err = HTU21D_OK;
  htu21d_data_t htu_data = {0};

  htu21d_i2c_hal_init();

  htu21d_i2c_hal_ms_delay(30);

  err = htu21d_i2c_reset();

  if(err != SL_STATUS_OK)
    app_log_error("Error resetting the device!\n\r");

  htu21d_i2c_hal_ms_delay(30);

  if(err != HTU21D_OK)
    app_log_error("Error setting the device!\n\r");
  if (err == HTU21D_OK)
  {
      app_log_info("htu21d initialization successful\n\r");
      while(1)
      {
          //Read temp and humidity
          err = htu21d_i2c_temp_read(&htu_data.temp);
          err += htu21d_i2c_hum_read(&htu_data.hum);
          if(err == HTU21D_OK)
          {
              app_log_info("Temperature: %d °C\n\r", (int)htu_data.temp);
              app_log_info("Humidity: %d %%\n\r", (int)htu_data.hum);
          }
          else{
              app_log_error("Data read error!\n\r");
          }
          htu21d_i2c_hal_ms_delay(2000);
      }
  }
  else{
      app_log_error("htu21d initialization failed!\n\r");
  }
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}
