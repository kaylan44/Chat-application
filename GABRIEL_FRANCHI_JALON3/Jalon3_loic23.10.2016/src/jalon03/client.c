#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "fonction_res216.c"
#include "user.c"

void do_connect(int sock, char hostname[], int port, struct sockaddr_in* sock_host);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc,char** argv)
{

    char input[200]= {0};
    char buffer[400]= {0};
    int port;
    char *mess_max_client ="max_cl";
    char *mess_conn_accepted ="co_acc";
    char buffer_connect[50]= {0};
    char* sub_in;
    int nickn_indicator = 0;


    struct sockaddr_in sock_host;

    if (argc != 3)
    {
        fprintf(stderr,"usage: RE216_CLIENT hostname port\n");
        return 1;
    }

    //get address info from the server
    port = atoi(argv[2]);
    char *hostname = argv[1];

    //get the socket
    int sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
      error("erreur socket");
    //connect to remote socket

    do_connect(sock, hostname, port, &sock_host);





    //read message from the server to know if the connection works fine
    if(read(sock,buffer_connect,sizeof(buffer_connect)) < 0)
      printf("erreur read");

    if (strcmp(buffer_connect, mess_conn_accepted) ==0 ){
        printf("Connection accepted.\n");
        printf("Please login with /nick <your pseudo>\n");


        //loop until /nick pseudo
 	    while(nickn_indicator == 0){
            fgets(input, sizeof(input), stdin);
	        sub_in = str_sub(input, 0, 5);
            
          	if (strcmp(sub_in, "/nick ") ==0){
          	    if (write(sock, input, strlen(input) ) < 0)//send /nick <pseudo>
                    printf("erreur write");
          	    if (read(sock, buffer, sizeof(buffer) ) < 0)// receive <pseudo>
                    printf("erreur read");
          	    printf("Welcome on chat %s \n", buffer);
          	    memset(buffer, '\0', sizeof(buffer));
                nickn_indicator=1;
          	}
            else{
              printf("Please login with /nick <your pseudo>\n");
              memset(buffer, '\0', sizeof(buffer));

            }
        }
    }
    else if (strcmp(buffer_connect, mess_max_client) ==0 ){
        printf("Connection terminated, too much client on the server\n");
        return 0;
    }

    //get user input
    while(1){

        printf("Entrez un message \n");
        fgets(input, sizeof(input), stdin);

        //send message to the server
        if (write(sock, input,strlen(input)+1) < 0)
            printf("erreur write");

	      memset(buffer, '\0', sizeof(buffer)); // important pour le who DAAMMMMMNNNN 10h dessus
        //read message from the server
        if(read(sock,buffer,sizeof(buffer)) < 0)
          printf("erreur read");
        //handle the case where the client want to end the connection
        if (strcmp(buffer, "/quit\n") ==0 ){
            printf("Connection terminated.\n");
            break;
        }
        else if (strcmp(buffer, mess_max_client) ==0 ){
            printf("Connection terminated, too much client on the server\n");
            break;
        }
        // if the user ask /who print an other text (the buffer is still the same)
	      else if (strcmp(input, "/who\n") ==0 ){
            printf("Online user are \n");
	           printf("%s \n \n", buffer);
	      }
	      else{
            printf("\n[Server] : %s \n", buffer);
	      }
    }

    close(sock);
    return 0;


}

void do_connect(int sock, char hostname[], int port, struct sockaddr_in* sock_host ){

    memset(sock_host, '\0', sizeof(*sock_host));
    sock_host->sin_family = AF_INET;
    sock_host->sin_port = htons(port);
    inet_aton(hostname, & sock_host->sin_addr);

    if (connect(sock, (struct sockaddr*)  sock_host, sizeof(*sock_host)) < 0)
      error("erreur connect");

}
