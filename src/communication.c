#include "communication.h"

#include <FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t xSocketMutex;

int sockfd;
char buffer[BUFFER_SIZE];
struct sockaddr_in send_addr, receive_addr;

void start_socket()
{
    xSocketMutex = xSemaphoreCreateMutex();

    xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed!!");
        exit(EXIT_FAILURE);
    }

    xSemaphoreGive(xSocketMutex);
}

void set_destination(char *address, uint32_t port)
{
    xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    // Preparing structs
    memset(&send_addr, 0, sizeof(send_addr));
    memset(&receive_addr, 0, sizeof(receive_addr));

    // Filling information to send msg
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(port);
    send_addr.sin_addr.s_addr = inet_addr(address);

    xSemaphoreGive(xSocketMutex);
}

void send_message(char *msg)
{
    xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    sendto(sockfd, (const char *)msg, strlen(msg),
           MSG_CONFIRM, (const struct sockaddr *)&send_addr,
           sizeof(send_addr));

    xSemaphoreGive(xSocketMutex);
}

void send_request_message(char *token)
{
    xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    //The request is composed by its token followed by a zero
    sprintf(buffer, "%s0", token);

    sendto(sockfd, (const char *)buffer, strlen(buffer),
           MSG_CONFIRM, (const struct sockaddr *)&send_addr,
           sizeof(send_addr));

    xSemaphoreGive(xSocketMutex);
}

void send_set_message(char *token, double value)
{
    xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    //The set-operation is composed by its token followed by the chosen number
    sprintf(buffer, "%s%lf", token, value);

    sendto(sockfd, (const char *)buffer, strlen(buffer),
           MSG_CONFIRM, (const struct sockaddr *)&send_addr,
           sizeof(send_addr));

    xSemaphoreGive(xSocketMutex);
}

int receive_message(char *token, double *read_value, char blocking)
{
    int n, len = sizeof(receive_addr);
    xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    do
    {
        n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
                     MSG_WAITALL, (struct sockaddr *)&receive_addr,
                     &len);
    } while ((blocking == COMMUNICATION_BLOCKING) && (n <= 0));

    if (n > 0)
    {
        buffer[n] = '\0';

        char *num_ptr;
        //verify if it has the token
        num_ptr = strstr(buffer, token);
        //if it has the token, put the value in read_value
        if (num_ptr != NULL)
        {
            //num_ptr + strlen(token): puts the pointer at the start of the number
            sscanf(num_ptr + strlen(token), "%lf", read_value);
            xSemaphoreGive(xSocketMutex);
            return 1;
        }
    }
    // If no datagram has been received or
    // the received message is not of token type
    xSemaphoreGive(xSocketMutex);
    return 0;
}

int receive_raw_message(char *out_buffer, uint32_t buffer_size, char blocking)
{
    int n, len = sizeof(receive_addr);
    xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    do
    {
        n = recvfrom(sockfd, (char *)out_buffer, buffer_size,
                     MSG_WAITALL, (struct sockaddr *)&receive_addr,
                     &len);
    } while ((blocking == COMMUNICATION_BLOCKING) && (n <= 0));

    if (n > 0)
    {
        out_buffer[n] = '\0';
        xSemaphoreGive(xSocketMutex);
        return 1;
    }
    // If no datagram has been received or
    xSemaphoreGive(xSocketMutex);
    return 0;
}