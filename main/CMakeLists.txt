idf_component_register(SRCS "app_main.c" "temperature_sensor.c" "dht_driver.c"
                       INCLUDE_DIRS "."
                       REQUIRES esp_driver_gpio freertos)
