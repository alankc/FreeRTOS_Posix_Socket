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

#include <stdio.h>

#define PORT 8080
#define MAXLINE 1024

void vTA(void *pvParameters)
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr); //len is value/resuslt

    for (;;)
    {
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        buffer[n] = '\0';
        if (n > 0)
            printf("Server : %s\n", buffer);
    }
}

void vTB(void *pvParameters)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    for (;;)
    {
        printf("Client send: %s\n", hello);
        sendto(sockfd, (const char *)hello, strlen(hello),
               MSG_CONFIRM, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}