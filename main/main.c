#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp32/rom/ets_sys.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

#include "dht11.h"

static const char *TAG = "DHT11";

void DHT_task(void *pvParameter)
{
   DHT11_init(GPIO_NUM_8);
   ESP_LOGI(TAG, "Starting DHT measurement!");
   struct dht11_reading dth11_data;
   while(1)
   {
        ESP_ERROR_CHECK(DHT11_read(&dth11_data));
        ESP_LOGI(TAG, "Temperature: %d", dth11_data.temperature);
        ESP_LOGI(TAG, "Humidity: %d", dth11_data.humidity);
        vTaskDelay(3000 / portTICK_RATE_MS);
   }
}

void app_main(void)
{
    nvs_flash_init();
    vTaskDelay(1000 / portTICK_RATE_MS);
    xTaskCreate(&DHT_task, "DHT_task", 2048, NULL, 5, NULL);
}
