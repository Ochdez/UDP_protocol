/**
 * Titulo: Protocolo UDP (Server)
 * @author JosÃ© Everardo Torres Orozco & Octavio Corona Hernandez
 * @brief Servidor para un protocolo UDP
 * @date 2022-02-27
 *  
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void revers (char ar[]);

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_size;
    int n;

    if(sockfd < 0)
    {
        perror("socket error");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr) );
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);  
    server_addr.sin_addr.s_addr = INADDR_ANY; 

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
    printf("Data received: %s\n",buffer);

    //Revierte la cadena
    revers(buffer); 

    //Manda datos al cliente:
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
    printf("Data sended: %s\n",buffer);

    return 0;   
}
/*
Invierte la cadena dada
*/
void revers (char* str)
{
    int len = strlen(str);
    int left, right;
    char temp;
    for(left = 0, right = len-1;left<(len/2);left++,right--)
    {
        temp = str[left];
        str[left] = str[right];
        str[right] = temp;
    }
    return;
}