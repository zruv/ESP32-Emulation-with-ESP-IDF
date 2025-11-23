#include "dht_driver.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <rom/ets_sys.h> // For ets_delay_us

#define DHT_MAX_CYCLES 1000

static const char *TAG_DHT = "DHT_DRIVER";

static int dht_read_data_internal(gpio_num_t gpio_num, int *humidity, int *temperature) {
    uint8_t data[5] = {0, 0, 0, 0, 0};
    uint8_t last_state = 1;
    uint8_t counter = 0;
    uint16_t i;
    uint8_t j = 0;

    // Send start signal
    gpio_set_direction(gpio_num, GPIO_MODE_OUTPUT);
    gpio_set_level(gpio_num, 0);
    ets_delay_us(18000); // 18ms low
    gpio_set_level(gpio_num, 1);
    ets_delay_us(40); // 40us high
    gpio_set_direction(gpio_num, GPIO_MODE_INPUT);

    // Read response
    for (i = 0; i < DHT_MAX_CYCLES; i++) {
        counter = 0;
        while (gpio_get_level(gpio_num) == last_state) {
            counter++;
            ets_delay_us(1);
            if (counter == 255) break;
        }
        last_state = gpio_get_level(gpio_num);
        if (counter == 255) break;

        // Skip 3 initial bits
        if ((i >= 4) && (i % 2 == 0)) {
            data[j / 8] <<= 1;
            if (counter > 45) { // Data is around 26-28us for 0, 70us for 1
                data[j / 8] |= 1;
            }
            j++;
        }
    }

    if (j >= 40 && data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        *humidity = data[0];
        *temperature = data[2];
        return ESP_OK;
    } else {
        ESP_LOGE(TAG_DHT, "Data corrupted or sensor not responding, checksum error or too few bits: %d", j);
        return ESP_FAIL;
    }
}

esp_err_t dht_read_float_data(dht_sensor_type_t sensor_type, gpio_num_t gpio_num, float *humidity, float *temperature) {
    int hum_int, temp_int;
    esp_err_t ret = dht_read_data_internal(gpio_num, &hum_int, &temp_int);

    if (ret == ESP_OK) {
        *humidity = (float)hum_int;
        *temperature = (float)temp_int;
    }
    return ret;
}
