/********** Code informaation **********/
/**** Creation date: June 29, 2021 *****/
/**** Developer: Alan Kunz Cechinel ****/
/**** e-mail: cechinel.a.k@gmail.com ***/
/***************************************/

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Local includes. */
#include "console.h"

#include <stdio.h>

void vTA(void *pvParameters)
{
    for (;;)
    {
        console_print("Task A\n");
        for (uint32_t i = 0; i < 10; i++)
        {
            for (uint32_t j = 0; j < 100; j++)
                printf("a");

            printf("\n");
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vTB(void *pvParameters)
{
    for (;;)
    {
        console_print("Task B\r\n");
        for (uint32_t i = 0; i < 10; i++)
        {
            for (uint32_t j = 0; j < 100; j++)
                printf("b");

            printf("\n");
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}