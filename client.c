/**
 * Titulo: Protocolo UDP (Client)
 * @author JosÃ© Everardo Torres Orozco & Octavio Corona Hernandez
 * @brief Cliente para un protocolo UDP
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

int main(int argc, char **argv)
{

    char mesage[1024];
    int i;
    
    //Guarda el mensaje escrito en consola
    for (i = 1; i < argc; i++)
    {
        strcat(mesage, argv[i]);
        strcat(mesage, " ");
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size;

    memset(&addr, '\0', sizeof(addr) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345); 
    addr.sin_addr.s_addr = INADDR_ANY;
    
    
    //Manda datos al servidor:
    bzero(buffer, 1024);
    strcpy(buffer, mesage);
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
    printf("Data sended: %s\n", buffer);
  
    //Recibe datos del servidor:
    bzero(buffer, 1024);
    addr_size = sizeof(addr);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
    printf("Data received: %s\n", buffer);
    
    return 0;
}
