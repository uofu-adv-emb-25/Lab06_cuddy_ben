#include "tasks.h"

void task1(void *args)
{
    busy_wait_ms(100);
    SemaphoreHandle_t semaphore = *(SemaphoreHandle_t *) args;
    xSemaphoreTake(semaphore, portMAX_DELAY);
}

void task2(void *args)
{
    SemaphoreHandle_t semaphore = *(SemaphoreHandle_t *) args;
    xSemaphoreTake(semaphore, portMAX_DELAY);
}

void task3(void *args)
{
    SemaphoreHandle_t semaphore = *(SemaphoreHandle_t *) args;
    xSemaphoreTake(semaphore, portMAX_DELAY);
}