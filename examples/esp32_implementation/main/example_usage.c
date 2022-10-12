#include <stdio.h>
#include "esp_log.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//htu21d components
#include "htu21d_i2c.h"
#include "htu21d_i2c_hal.h"

static const char *TAG = "example_usage";

void app_main(void)
{
    esp_err_t err;
    htu21d_data_t htu_data = {0};

    htu21d_i2c_hal_init();

    htu21d_i2c_hal_ms_delay(30);

    err = htu21d_i2c_reset();
    if(err != ESP_OK) ESP_LOGE(TAG, "Error resetting the device!");
    htu21d_i2c_hal_ms_delay(30);   
    
    if(err != ESP_OK) ESP_LOGE(TAG, "Error setting the device!");
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "htu21d initialization successful");
        while(1)
        {
            //Read temp and humidity
            err = htu21d_i2c_temp_read(&htu_data.temp);
            err += htu21d_i2c_hum_read(&htu_data.hum);
            if(err == ESP_OK)
            {
                ESP_LOGI(TAG, "Temperature: %.01f°C", htu_data.temp);
                ESP_LOGI(TAG, "Humidity: %.01f%%", htu_data.hum);
            }
            else{
                ESP_LOGE(TAG, "Data read error!");
            }
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
    }
    else{
        ESP_LOGE(TAG, "htu21d initialization failed!");
    }
}
