#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    srand(time(NULL));

    while (1) {
        float temperature = (rand() % 50) + 10.5;
        printf("Temperature: %.2f°C\n", temperature);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}