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

    create_tasks();

    vTaskStartScheduler();

    return 0;
}
