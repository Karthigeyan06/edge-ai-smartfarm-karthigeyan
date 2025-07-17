
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt_client.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "dht.h"



#define BROKER_URI "mqtt://broker.hivemq.com"

static const char *TAG = "SMART_FARMING";
esp_mqtt_client_handle_t mqtt_client;

void mqtt_publish_data(int soil_value, int temp, int hum) {
    char msg[64];
    sprintf(msg, "{\"soil\": %d, \"temp\": %d, \"hum\": %d}", soil_value, temp, hum);
    esp_mqtt_client_publish(mqtt_client, "farm/data", msg, 0, 1, 0);
}

void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = event_data;
    mqtt_client = event->client;

    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT connected");
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT disconnected");
            break;
        default:
            break;
    }
}

void mqtt_app_start() {
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = BROKER_URI,
    };
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(mqtt_client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(mqtt_client);
}

void wifi_init() {
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS
        }
    };

    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
    esp_wifi_connect();
}

void app_main(void) {
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_init();
    mqtt_app_start();

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); // GPIO34

    while (1) {
        int soil = adc1_get_raw(ADC1_CHANNEL_6);

        int16_t temperature = 0, humidity = 0;
        if (dht_read_data(DHT_TYPE_DHT11, GPIO_NUM_4, &humidity, &temperature) == ESP_OK) {
            ESP_LOGI(TAG, "Soil: %d, Temp: %d°C, Hum: %d%%", soil, temperature, humidity);
            mqtt_publish_data(soil, temperature, humidity);
        } else {
            ESP_LOGE(TAG, "Failed to read DHT11");
        }

        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}
