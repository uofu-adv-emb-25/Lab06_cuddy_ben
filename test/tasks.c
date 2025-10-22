#include <stdio.h>
#include <semphr.h>
#include <pico/stdlib.h>


void task1(void*)
{
    vTaskDelay(pdMS_TO_TICKS(500));
    SemaphoreHandle_t *semaphore = *(SemaphoreHandle_t *) args;
    xSemaphoreTake(semaphore, portMAX_DELAY);
}

void task2(void* args)
{
    SemaphoreHandle_t *semaphore = *(SemaphoreHandle_t *) args;
    xSemaphoreTake(semaphore, portMAX_DELAY);
}

void task2(void* args)
{
    SemaphoreHandle_t *semaphore = *(SemaphoreHandle_t *) args;
    xSemaphoreTake(semaphore, portMAX_DELAY);
}