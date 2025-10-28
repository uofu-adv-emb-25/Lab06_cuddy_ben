#pragma once

#include <pico/stdlib.h>
#include <pico/time.h>
#include <FreeRTOS.h>
#include <stdio.h>
#include <semphr.h>

void task1(void *args);
void task2(void *args);
void task3(void *args);