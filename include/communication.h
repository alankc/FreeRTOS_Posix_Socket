/********** Code informaation **********/
/**** Creation date: June 29, 2021 *****/
/**** Developer: Alan Kunz Cechinel ****/
/**** e-mail: cechinel.a.k@gmail.com ***/
/***************************************/

#ifndef COMUMUNICATION_H
#define COMUMUNICATION_H

#include <stdio.h>          // printf(), perror()
#include <stdlib.h>         // EXIT_FAILURE
#include <sys/types.h>      // AF_INET, SOCK_STREAM
#include <sys/socket.h>     // socket(), connect()
#include <netinet/in.h>     // struct sockaddr_in
#include <arpa/inet.h>      // htons(), inet_addr()
#include <unistd.h>         // close()
#include <string.h>         // strlen()

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 1000
#endif

/*
"sta0" lê valor de Ta
"st-0" lê valor de T
"sti0" lê valor de Ti
"sno0" lê valor de No
"sh-0" lê valor de H
"ani123.4" define valor de Ni como 123.4
"aq-567.8" define valor de Q como 567.8
"ana123.4" define valor de Na como 123.4
"anf123.4" define valor de Nf como 123.4
*/

#define REQUEST_TA "sta"
#define REQUEST_T "st-"
#define REQUEST_TI "sti"
#define REQUEST_NO "sno"
#define REQUEST_H "sh-"

#define SET_NI "ani"
#define SET_Q "aq-"
#define SET_NA "ana"
#define SET_NF "anf"

#define COMMUNICATION_BLOCKING 1
#define COMMUNICATION_NON_BLOCKING 0


/**
 * Creates and starts the client socket
 *
 **/
void start_socket();

/**
 * Defines the address and port of the boiler socket. 
 *
 * @param address When using linux: "localhost" or "127.0.0.1". 
 *                When using windows WSL: the machine IP address like "192.168.0.25". 
 * @param port the port used in the boiler socket. 
 **/
void set_destination(char* address, uint32_t port);

/**
 * Sends a message to the boiler socket. 
 *
 * @param msg Ideally composed by a token and a number. 
 **/
void send_message(char* msg);

/**
 * Sends a request to the boiler socket. 
 * It adds a 0 to the token and sends the message. 
 *
 * @param token Must use one of the REQUEST_ tokens. 
 **/
void send_request_message(char* token);

/**
 * Sends a set-operation to the boiler socket. 
 * It adds the value to the token and sends the message. 
 *
 * @param token Must use one of the SET_ tokens. 
 * @param value Value of the parameter to be set. 
 **/
void send_set_message(char* token, double value);

/**
 * Receives a message and verify it has the token. If it has the token, then
 * puts the received value in the read_value.
 *
 * @param token Must use one of the tokens. 
 * @param read_value Value informed by the boiler. 
 * @param blocking function blocked until receive a message
 * @return 1 if it received a message and found the token in the string. 0 otherwise.
 **/
int receive_message(char* token, double* read_value, char blocking);

/**
 * Receives a message and puts in the out_buffer.
 *
 * @param out_buffer Buffer to store the message. 
 * @param buffer_size Size of the buffer.
 * @param blocking function blocked until receive a message 
 * @return 1 if it received a message. 0 otherwise.
 **/
int receive_raw_message(char* out_buffer, uint32_t buffer_size, char blocking);

#endif