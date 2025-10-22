#include "tasks.c"

#include <stdio.h>
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
        // RUN_TEST();

        SemaphoreHandle_t sem;
        sem = xSemaphoreCreateBinary();

        void* args = sem;

        // higher priority thread
        TaskHandle_t task_handle_1;
        xTask_create(task1, "task 1", configMINIMAL_STACK_SIZE, (void*)&args, tskIDLE_PRIORITY+5, &task_handle_1);

        TaskHandle_t task_handle_2;
        xTask_create(task2, "task 2", configMINIMAL_STACK_SIZE, (void*)&args, tskIDLE_PRIORITY+1, &task_handle_2);

        TaskHandle_t task_handle_3;
        xTask_create(task3, "task 3", configMINIMAL_STACK_SIZE, (void*)&args, tskIDLE_PRIORITY+2, &task_handle_3);

        vTaskDelay(pdMS_TO_TICKS(1000));
        
        TaskStatus_t stat_1, stat_2, stat_3;
        
        vTaskGetInfo(task_handle_1, &stat_1, pdTRUE, eInvalid);
        vTaskGetInfo(task_handle_2, &stat_2, pdTRUE, eInvalid);
        vTaskGetInfo(task_handle_3, &stat_3, pdTRUE, eInvalid);

        

        
        


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