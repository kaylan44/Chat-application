#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void do_connect(int sock, char hostname[], int port, struct sockaddr_in* sock_host);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc,char** argv)
{

  char input[100]= {0};
  char buffer[100]= {0};

    if (argc != 3)
    {
        fprintf(stderr,"usage: RE216_CLIENT hostname port\n");
        return 1;
    }

    //get address info from the server
    int port = atoi(argv[2]);
    char *hostname = argv[1];

    //get the socket
    int sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
      error("erreur socket");
    //connect to remote socket
    struct sockaddr_in sock_host;
    do_connect(sock, hostname, port, &sock_host);

    //get user input
    while(1){
        printf("Entrez un message \n");
        fgets(input, sizeof(input), stdin);

        //send message to the server
        if (write(sock, input,strlen(input)) < 0)
            printf("erreur write");

        //read message from the server
        if(read(sock,buffer,sizeof(buffer)) < 0)
          printf("erreur read");
        //handle the case where the client want to end the connection
        if (strcmp(buffer, "/quit\n") ==0 ){
            printf("Connection terminated.\n");
            break;
        }
        printf("Le serveur a renvoyé le message suivant = %s \n", buffer);
    }

    close(sock);
    return 0;


}

void do_connect(int sock, char hostname[], int port, struct sockaddr_in* sock_host ){

    memset(sock_host, '\0', sizeof(sock_host));
    sock_host->sin_family = AF_INET;
    sock_host->sin_port = htons(port);
    inet_aton(hostname, & sock_host->sin_addr);

    if (connect(sock, (struct sockaddr*)  sock_host, sizeof(*sock_host)) < 0)
      error("erreur connect");

}
