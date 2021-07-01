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
#include "communication.h"

void vTA(void *pvParameters)
{
    for (;;)
    {
        double r;
        char t[100];
        if (receive_raw_message(t, 100))
        {
            printf("Server: %s\n", t);

            //Testing if it is a response from the set-operation SET_NA
            char *ptr = strstr(t, SET_NA);
            if (ptr != NULL)
            {
                sscanf(ptr + strlen(SET_NA), "%lf", &r);
                printf("Server (%s): %lf\n", SET_NA, r);
            }
        }

        /*  Alternatively, if you know the expected message type

        double value = 0;
        if (receive_message(REQUEST_TA, &value))
            printf("Server (%s): %lf \n", REQUEST_TA, value);

        */

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void vTB(void *pvParameters)
{
    double i = 1;
    for (;;)
    {
        send_request_message(REQUEST_TA);
        send_request_message(REQUEST_T);
        send_request_message(REQUEST_TI);
        send_request_message(REQUEST_NO);
        send_request_message(REQUEST_H);

        vTaskDelay(pdMS_TO_TICKS(50));

        send_set_message(SET_NI, i);
        send_set_message(SET_Q, i);
        send_set_message(SET_NA, i);
        send_set_message(SET_NF, i);

        i *= 1.028;
        printf("Client\n");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}