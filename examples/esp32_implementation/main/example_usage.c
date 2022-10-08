#include <stdio.h>
#include "esp_log.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//htu21d components
#include "htu21d_i2c.h"
#include "htu21d_i2c_hal.h"

#include "driver/i2c.h"

static const char *TAG = "example_usage";

static uint8_t i2c_slave_knock(uint8_t i2c_port, uint8_t slave_addr) {
    esp_err_t err;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr << 1) | I2C_MASTER_WRITE, 1);
    i2c_master_stop(cmd);
    err = i2c_master_cmd_begin(i2c_port, cmd, 50 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return err == ESP_OK;
}

static void i2c_scan(void) {
    uint8_t slave_count = 0;
    vTaskDelay(500 / portTICK_PERIOD_MS);
    for (int slave_addr = 0; slave_addr < 127; slave_addr++) {
        if (i2c_slave_knock(0, slave_addr)) {
            ESP_LOGI(TAG, "master %d slave_%d_addr %02X", 0, slave_count,
                     slave_addr);
            slave_count++;
        }
    }

    ESP_LOGI(TAG, "Slave Count %d", slave_count);
}

void app_main(void)
{
    esp_err_t err;
    htu21d_data_t htu_data = {0};
    uint8_t dev_cfg = 0;

    htu21d_i2c_hal_init();

    //i2c_scan();
    
    err = htu21d_i2c_read_config(&dev_cfg);
    
    if(err != ESP_OK) ESP_LOGE(TAG, "Error setting the device!");
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "htu21d initialization successful");
        while(1)
        {
            //Read temp and humidity
            ESP_LOGI(TAG, "Temperature: %d", htu_data.temp);
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
    }
    else{
        ESP_LOGE(TAG, "htu21d initialization failed!");
    }
}
