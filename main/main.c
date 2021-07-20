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
   DHT11_init(GPIO_NUM_4);
   ESP_LOGI(TAG, "Starting DHT measurement!");
   while(1)
   {
    ESP_LOGI(TAG, "Temperature: %d", DHT11_read().temperature);
    ESP_LOGI(TAG, "Humidity: %d", DHT11_read().humidity);
    ESP_LOGI(TAG, "Status code: %d", DHT11_read().status);
    vTaskDelay(3000 / portTICK_RATE_MS);
   }
}

void app_main(void)
{
    nvs_flash_init();
    // system_init();
    vTaskDelay(1000 / portTICK_RATE_MS);
    xTaskCreate(&DHT_task, "DHT_task", 2048, NULL, 5, NULL);

// DHT11_init(GPIO_NUM_4);

//     while(1) {
//         printf("Temperature is %d \n", DHT11_read().temperature);
//         printf("Humidity is %d\n", DHT11_read().humidity);
//         printf("Status code is %d\n", DHT11_read().status);
//         vTaskDelay(3000 / portTICK_RATE_MS);
//     }

}
