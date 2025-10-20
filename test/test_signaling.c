s#include <stdio.h>
#include <pico/stdlib.h>
#include "pico/cyw43_arch.h"
#include <stdint.h>
#include <unity.h>
#include <task.h>
#include <semphr.h>

void test_task(void *params) {
    while(1){
        UNITY_BEGIN();
        // Run Tests

        // Activity 0

        // Activity 1

        // Activity 2

        // -- Same Priority --
        // Both busy_busy
        // Both busy_yield
        // One busy_busy, one busy_yield

        // -- Different Priority --
        // Both busy_busy
        // Both busy_yield
        // One busy_busy, one busy_yield
        UNITY_END():
        vTASK_DELAY(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    stdio_init_all();
    TaskHandle_t TestTaskHandle;
    xTask_create(test_task, "test_task", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, &TestTaskHandle);
    vTaskStartScheduler();
    return 0;
}