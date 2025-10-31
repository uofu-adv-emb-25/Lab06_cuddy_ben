#pragma once

#include <pico/stdlib.h>
#include <pico/time.h>
#include <FreeRTOS.h>
#include <stdio.h>
#include <semphr.h>

void task1(void *args);
void task2(void *args);
void task3(void *args);

typedef struct{
    SemaphoreHandle_t sem;      // semaphore for priority inversion test

    TaskFunction_t t1_fn;       // function pointer for task
    UBaseType_t t1_priority;    // priority for task

    TaskFunction_t t2_fn;
    UBaseType_t t2_priority;

    TaskFunction_t t3_fn;
    UBaseType_t t3_priority;

    QueueHandle_t statQ;
} TaskArgs;

typedef struct 
{
    uint64_t t1;
    uint64_t t2;
    uint64_t t3;
    
} TaskInfo;
