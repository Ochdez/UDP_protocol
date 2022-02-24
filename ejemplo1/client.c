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
    char *hello = "hello from client";
    /*
    Crea la dirección del socket
    Carga la estructura en una pila con direccion 0.0.0.0 que se modidicará despues
    */
    struct sockaddr_in servaddr ={0}; 
     
    /*
    Creamos el socket
    AF_INET indica que se mandará a traves de una ipv4
    SOCK_DGRAM determina que se trata de un paquete por UDP
    Protocolo 0
    */
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   
    if(sockfd == -1)
    {
        perror("error al crear el socket\n");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET; //Destino
    servaddr.sin_port = htons(12345); //Puerto - ?
    servaddr.sin_addr.s_addr = INADDR_ANY; //Para haceptar cualquier dirección ip - ? 
    
    /*
    Mensaje a enviar:
    (const char *) - para que el mensaje no pueda ser modificado
    0 - Para que no indique ningun error que pueda surgir
    servaddr -> Destno al que se enviará
    */
    int len = sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    if(len == -1)
    {
        perror("falla al enviar\n");
    }
    close(sockfd);

    return 0;
}