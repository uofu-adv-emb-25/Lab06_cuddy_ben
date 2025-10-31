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

QueueHandle_t statQ;

void setUp(void) {}
void tearDown(void) {}

void run_test(void *params, TaskInfo *out_data){
    TaskArgs *args = (TaskArgs *) params;

    //TaskHandle_t task_handle_1;
    //xTaskCreate(args->t1_fn, "task 1", configMINIMAL_STACK_SIZE, (void*)args, args->t1_priority, &task_handle_1);

    TaskHandle_t task_handle_2;
    xTaskCreate(args->t2_fn, "task 2", configMINIMAL_STACK_SIZE, (void*)args, args->t2_priority, &task_handle_2);

    TaskHandle_t task_handle_3;
    xTaskCreate(args->t3_fn, "task 3", configMINIMAL_STACK_SIZE, (void*)args, args->t3_priority, &task_handle_3);


    
    vTaskDelay(pdMS_TO_TICKS(1000));

    printf("here\n");

    TaskStatus_t stat_1, stat_2, stat_3;
    
    //vTaskGetInfo(task_handle_1, &stat_1, pdTRUE, eInvalid);
    //vTaskGetInfo(task_handle_2, &stat_2, pdTRUE, eInvalid);
    //vTaskGetInfo(task_handle_3, &stat_3, pdTRUE, eInvalid);

    uint64_t t1 = 0, t2 = 0, t3 = 0;

    //t1 = ulTaskGetRunTimeCounter(task_handle_1);
    //t2 = ulTaskGetRunTimeCounter(task_handle_2);
    //t3 = ulTaskGetRunTimeCounter(task_handle_3);

    out_data->t1 = t1;
    out_data->t2 = t2;
    out_data->t3 = t3;

    printf("Task 1 time: %llu\n", t1);
    printf("Task 2 time: %llu\n", t2);
    printf("Task 3 time: %llu\n", t3);

    //vTaskDelete(task_handle_1);
    vTaskDelete(task_handle_2);
    //vTaskDelete(task_handle_3);
}

void priority_inversion(void){  // Most of the test cases should be similar to this
    SemaphoreHandle_t sem;
    sem = xSemaphoreCreateBinary();
    xSemaphoreGive(sem);

    statQ = xQueueCreate(3, sizeof(uint8_t));
    
    TaskArgs args = {
        .sem = sem,
        .t1_fn = task1,
        .t1_priority = tskIDLE_PRIORITY + 5,
        .t2_fn = task2,
        .t2_priority = tskIDLE_PRIORITY + 1,
        .t3_fn = task3,
        .t3_priority = tskIDLE_PRIORITY + 2,
        .statQ = statQ,
    };

    TaskInfo output = {};

    run_test((void*)&args, &output);

    TEST_ASSERT_GREATER_THAN(output.t2, output.t1);
    TEST_ASSERT_GREATER_THAN(output.t3, output.t1);

    vSemaphoreDelete(sem);
}

void mutex_semaphore(void)
{
    SemaphoreHandle_t sem;
    sem = xSemaphoreCreateMutex();
    xSemaphoreGive(sem);

    statQ = xQueueCreate(3, sizeof(uint8_t));
    
    TaskArgs args = {
        .sem = sem,
        .t1_fn = task1,
        .t1_priority = tskIDLE_PRIORITY + 5,
        .t2_fn = task2,
        .t2_priority = tskIDLE_PRIORITY + 1,
        .t3_fn = task3,
        .t3_priority = tskIDLE_PRIORITY + 2,
        .statQ = statQ,
    };

    TaskInfo output = {};

    run_test((void*)&args, &output);

    TEST_ASSERT_GREATER_THAN(output.t2, output.t1);
    TEST_ASSERT_GREATER_THAN(output.t3, output.t1);

    vSemaphoreDelete(sem);
}

void test_task(__unused void *params) {
    
    UNITY_BEGIN();
    // Run Tests
    // Activity 0
    //RUN_TEST(priority_inversion);
    // Activity 1
    RUN_TEST(mutex_semaphore);
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
    for(;;) { vTaskDelay(2000); }
}

int main(void)
{
    stdio_init_all();

    hard_assert(cyw43_arch_init() == PICO_OK);


    sleep_ms(10000);
    printf("Launching test runner\n");

    
    xTaskCreate(test_task, "test_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    vTaskStartScheduler();
    return 0;
}