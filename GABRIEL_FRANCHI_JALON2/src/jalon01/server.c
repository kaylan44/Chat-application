#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

struct sockaddr_in init_serv_addr(int port);

int main(int argc, char** argv)
{

    char buffer[100] = {0};
    int sock_acc = 0;

    if (argc != 2)
    {
        fprintf(stderr, "usage: RE216_SERVER port\n");
        return 1;
    }



    //create the socket, check for validity!
    int port = atoi(argv[1]);
    int sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
      error("erreur socket");

    //init the serv_add structure
    struct sockaddr_in addr = init_serv_addr(port);
    socklen_t addrlen =  sizeof(addr);

    //perform the binding
    //we bind on the tcp port specified
    int bindfd = bind(sock, (struct sockaddr*) & addr, sizeof(addr) );
    if(bindfd < 0){
      error("erreur bind");
    }

    //specify the socket to be a server socket and listen for at most 20 concurrent client
    int listenfd = listen(sock, 20);
    if(listenfd < 0)
      error("erreur listen");

    printf("Serveur en écoute \n");

    for (;;)
    {

        //accept connection from client
        sock_acc = accept(sock, (struct sockaddr*) & addr, &addrlen);
        if (sock_acc < 0)
            error("Erreur acceptation");

        //Respond to the client messages until the client send "/quit"
        while(strcmp(buffer, "/quit\n") !=0 ){
          memset(buffer, '\0', sizeof(buffer));
          //read what the client has to say
          if (read(sock_acc,buffer,sizeof(buffer)) < 0)
              error("erreur read");

          printf("Message reçu = %s \n", buffer);

          //write back to the client
          if(write(sock_acc,buffer,sizeof(buffer)) < 0)
                error("erreur write");
        }
        // Erase the old value of the buffer
        memset(buffer, '\0', sizeof(buffer));
        close(sock_acc);

    }

    //clean up server socketsock_acc
    close(sock);
    return 0;
}

struct sockaddr_in init_serv_addr(int port){
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(port) ;
  return addr;
}
