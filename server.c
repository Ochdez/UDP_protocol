#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void reves (char ar[]);

int main(int argc, char **argv)
{
    /*
    if(argc != 2){ //Al ejecutarlo se debe indicar el puerto 
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }
    */

    //char *ip = "127.0.0.1"; //dirección local
    //int port = atoi(argv[1]);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_size;
    int n;

    //printf("PORT NUMBER: %d\n",port);

    if(sockfd < 0)
    {
        perror("socket error");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr) );
    server_addr.sin_family = AF_INET; //Determina que se trata de un protocolo UDP
    server_addr.sin_port = htons(12345);  //12345 para aceptar cualquier puerto
    //server_addr.sin_addr.s_addr = inet_addr(ip); Para especficar que ip será aceptada
    server_addr.sin_addr.s_addr = INADDR_ANY; //indica que aceptará cualquier ip

    //Guarda la dirección ip del servidor en servaddr (info de las tres lineas anteriores)
    n = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    if(n < 0)
    {
        perror("BIND error");
        exit(1);
    }
    //Captura datos del cliente
    bzero(buffer, 1024);
    addr_size = sizeof(client_addr);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
    printf("Data recived: %s\n",buffer);

    reves(buffer); //Revierte la cadena

    //Manda datos al cliente:
    //bzero(buffer, 1024);
    //strcpy(buffer, "Welcome to de UDP Server. ");
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
    printf("Data send: %s\n",buffer);

    return 0;   
}

void reves (char* ar)
{
    int len = strlen(ar);
    int left, right;
    char temp;
    for(left = 0, right = len-1;left<(len/2);left++,right--)
    {
        temp = ar[left];
        ar[left] = ar[right];
        ar[right] = temp;
    }
    return;
}