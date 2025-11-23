#ifndef DHT_DRIVER_H
#define DHT_DRIVER_H

#include <driver/gpio.h>
#include <esp_err.h>

typedef enum {
    DHT_TYPE_DHT11,
    // Add other DHT types if needed
} dht_sensor_type_t;

esp_err_t dht_read_float_data(dht_sensor_type_t sensor_type, gpio_num_t gpio_num, float *humidity, float *temperature);

#endif // DHT_DRIVER_H
