#include "tasks.h"

void task1(void *args)
{
    busy_wait_ms(100);
    TaskArgs *task_args = (TaskArgs*) args;
    xSemaphoreTake(task_args->sem, portMAX_DELAY);
}

void task2(void *args)
{
    TaskArgs *task_args = (TaskArgs*) args;
    xSemaphoreTake(task_args->sem, portMAX_DELAY);
    //xSemaphoreTake(task_args->sem, 666);
}

void task3(void *args)
{
    TaskArgs *task_args = (TaskArgs*) args;
    xSemaphoreTake(task_args->sem, portMAX_DELAY);
    //xSemaphoreTake(task_args->sem, 666);
}