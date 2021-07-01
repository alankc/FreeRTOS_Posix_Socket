/********** Code informaation **********/
/**** Creation date: June 29, 2021 *****/
/**** Developer: Alan Kunz Cechinel ****/
/**** e-mail: cechinel.a.k@gmail.com ***/
/***************************************/

/* Unix includes. */
/* General porpouse includes. */
#include <stdlib.h>
#include <stdio.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Local includes. */
#include "console.h"
#include "list_of_tasks.h"
#include "communication.h"

int main(void)
{
    console_init();

    start_socket();
    set_destination("192.168.0.134", 12345);


    xTaskCreate(&vTA, "Task A", 1024, NULL, 1, NULL);
    xTaskCreate(&vTB, "Task B", 1024, NULL, 2, NULL);

    vTaskStartScheduler();

    return 0;
}
