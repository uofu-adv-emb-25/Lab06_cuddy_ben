#include "tasks.h"

#include <stdint.h>

void task1(void *args)
{
    // printf("task1E\n");
    vTaskDelay(pdMS_TO_TICKS(500));
    TaskArgs *task_args = (TaskArgs*) args;
    xSemaphoreTake(task_args->sem, portMAX_DELAY);
    // printf("task1\n");
    xSemaphoreGive(task_args->sem);
    // printf("task1F\n");
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task2(void *args)
{
    // printf("task2E\n");
    TaskArgs *task_args = (TaskArgs*) args;
    xSemaphoreTake(task_args->sem, portMAX_DELAY);
    // printf("task2\n");
    xSemaphoreGive(task_args->sem);
    // printf("task2F\n");
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task3(void *args)
{
    // printf("task3E\n");
    TaskArgs *task_args = (TaskArgs*) args;
    xSemaphoreTake(task_args->sem, portMAX_DELAY);
    // printf("task3\n");
    xSemaphoreGive(task_args->sem);
    // printf("task3F\n");
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void busy_busy(void *args){
    for (int i = 0; ;i++);
}

void busy_yield(void *args){
    for (int i = 0; ;i++){
        taskYIELD();
    }
}