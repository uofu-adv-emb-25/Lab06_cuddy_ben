#include <stdio.h>
#include <pico/stdlib.h>
#include "pico/cyw43_arch.h"
#include <pico/time.h>
#include <stdint.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <unity.h>
#include <task.h>
#include "tasks.h"
#include <unity.h>
#include "unity_config.h"

void setUp(void) {}
void tearDown(void) {}

void test_task(void *params) {
    while(1){
        UNITY_BEGIN();
        // Run Tests

        // Activity 0
        // RUN_TEST();

        SemaphoreHandle_t sem;
        sem = xSemaphoreCreateBinary();

        TaskArgs args = {
            .sem = sem,
            .t1_fn = task1,
            .t1_priority = tskIDLE_PRIORITY + 5,
            .t2_fn = task2,
            .t2_priority = tskIDLE_PRIORITY + 1,
            .t3_fn = task3,
            .t3_priority = tskIDLE_PRIORITY + 2
        };

        TaskHandle_t task_handle_1;
        xTaskCreate(args.t1_fn, "task 1", configMINIMAL_STACK_SIZE, (void*)&args, tskIDLE_PRIORITY+5, &task_handle_1);

        TaskHandle_t task_handle_2;
        xTaskCreate(args.t2_fn, "task 2", configMINIMAL_STACK_SIZE, (void*)&args, tskIDLE_PRIORITY+1, &task_handle_2);

        TaskHandle_t task_handle_3;
        xTaskCreate(args.t3_fn, "task 3", configMINIMAL_STACK_SIZE, (void*)&args, tskIDLE_PRIORITY+2, &task_handle_3);

        vTaskDelay(pdMS_TO_TICKS(1000));

        TaskStatus_t stat_1, stat_2, stat_3;
        
        vTaskGetInfo(task_handle_1, &stat_1, pdTRUE, eInvalid);
        vTaskGetInfo(task_handle_2, &stat_2, pdTRUE, eInvalid);
        vTaskGetInfo(task_handle_3, &stat_3, pdTRUE, eInvalid);

        uint64_t t1 = 0, t2 = 0, t3 = 0;

        t1 = ulTaskGetRunTimeCounter(task_handle_1);
        t2 = ulTaskGetRunTimeCounter(task_handle_2);
        t3 = ulTaskGetRunTimeCounter(task_handle_3);

        printf("Task 1 time: %llu\n", t1);
        printf("Task 2 time: %llu\n", t2);
        printf("Task 3 time: %llu\n", t3);
        

        
        


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
        UNITY_END();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    stdio_init_all();
    TaskHandle_t TestTaskHandle;
    xTaskCreate(test_task, "test_task", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, &TestTaskHandle);
    vTaskStartScheduler();
    return 0;
}