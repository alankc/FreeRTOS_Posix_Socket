/********** Code informaation **********/
/**** Creation date: June 29, 2021 *****/
/**** Developer: Alan Kunz Cechinel ****/
/**** e-mail: cechinel.a.k@gmail.com ***/
/***************************************/

#include "communication.h"

int local_socket()
{
    int socket_local;

    socket_local = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_local < 0)
    {
        perror("local_socket");
        exit(0);
    }

    return socket_local;
}

void define_listiner_port(int local_socket, int port)
{
    struct sockaddr_in server; /* Endereço completo do servidor e do cliente */
    int tam_s;                 /* Tamanho da estrutura servidor */

    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    tam_s = sizeof(server);
    if (bind(local_socket, (struct sockaddr *)&server, tam_s) < 0)
    {
        perror("define_listiner_port");
        exit(0);
    }
}

struct sockaddr_in destination_address(char *address, int port)
{
    struct sockaddr_in server;     /* Endereço do servidor incluindo ip e porta */
    struct hostent *dest_internet; /* Endereço destino em formato próprio */
    struct in_addr dest_ip;        /* Endereço destino em formato ip numérico */

    if (inet_aton(address, &dest_ip))
        dest_internet = gethostbyaddr((char *)&dest_ip, sizeof(dest_ip), AF_INET);
    else
        dest_internet = gethostbyname(address);

    if (dest_internet == NULL)
    {
        fprintf(stderr, "Endereço de rede inválido\n");
        exit(0);
    }

    memset((char *)&server, 0, sizeof(server));
    memcpy(&server.sin_addr, dest_internet->h_addr_list[0], sizeof(server.sin_addr));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    return server;
}

void send_msg(int local_socket, struct sockaddr_in destination_address, char *msg)
{
    if (sendto(local_socket, msg, strlen(msg) + 1, 0, (struct sockaddr *)&destination_address, sizeof(destination_address)) < 0)
    {
        perror("send_msg");
        return;
    }
}

int receive_msg(int local_socket, char *buffer, int buffer_size)
{
    int bytes_recebidos; /* Número de bytes recebidos */

    /* Espera pela msg de resposta do servidor */
    bytes_recebidos = recvfrom(local_socket, buffer, buffer_size, 0, NULL, 0);
    if (bytes_recebidos < 0)
    {
        perror("recvfrom");
    }

    return bytes_recebidos;
}

int receive_msg_and_adress(int local_socket, char *buffer, int buffer_size, struct sockaddr_in *client_adress, int *size_c)
{

}
