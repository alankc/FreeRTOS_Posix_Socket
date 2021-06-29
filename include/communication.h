/********** Code informaation **********/
/**** Creation date: June 29, 2021 *****/
/**** Developer: Alan Kunz Cechinel ****/
/**** e-mail: cechinel.a.k@gmail.com ***/
/***************************************/

#ifndef COMUMUNICATION_H
#define COMUMUNICATION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>

int local_socket();

void define_listiner_port(int local_socket, int port);

struct sockaddr_in destination_address(char *address, int port);

void send_msg(int local_socket, struct sockaddr_in destination_address, char *msg);

int receive_msg(int local_socket, char *buffer, int buffer_size);

int receive_msg_and_adress(int local_socket, char *buffer, int buffer_size, struct sockaddr_in *client_adress, int *size_c);



#endif