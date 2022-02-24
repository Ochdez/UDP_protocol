#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    char buffer[50] = {0};
    //Para guardar la información de la dirección
    struct sockaddr_in servaddr = {0};

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd == -1)
    {
        perror("error al crear el socket\n");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(12345); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 

    //Guarda la dirección ip del servidor en servaddr (indo de las tres lineas anteriores)
    int rc = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr) );

    if(rc == -1)
    {
        perror("error bind\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    socklen_t len = 0;
    //MSG_WAITALL espera a que el cliente mande el mensaje
    int n = recvfrom(sockfd, (char *)buffer, 50, MSG_WAITALL, 0, &len);

    buffer[n] = '\n';
    printf("%s",buffer);
    close(sockfd);

    return 0;
}