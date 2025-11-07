#include "tasks.h"

#include <stdint.h>

void task1(void *args)
{
    
    TaskArgs *task_args = (TaskArgs*) args;
    xSemaphoreTake(task_args->sem, portMAX_DELAY);

    volatile int counter = 0;
    for(int i = 0; i < 10000000; i++)
    {
        counter++;
    }

    vTaskDelete(NULL);
}

void task2(void *args)
{
    TaskArgs *task_args = (TaskArgs*) args;
    xSemaphoreTake(task_args->sem, portMAX_DELAY);
    
    volatile int counter = 0;
    for(int i = 0; i < 10000000; i++)
    {
        counter++;
    }

    vTaskDelete(NULL);
}

void task3(void *args)
{
    TaskArgs *task_args = (TaskArgs*) args;
    xSemaphoreTake(task_args->sem, portMAX_DELAY);

    volatile int counter = 0;
    for(int i = 0; i < 10000000; i++)
    {
        counter++;
    }

    vTaskDelete(NULL);
}

void busy_busy(void *args){
    for (;;);
}

void busy_yield(void *args){
    for (;;){
        taskYIELD();
    }
}