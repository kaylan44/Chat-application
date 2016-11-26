#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "fonction.h"
#include "user.h"
#include "salon.h"
#include "file.h"



void do_connect(int sock_client, char hostname[], int port, struct sockaddr_in* sock_host);

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
    //Jalon4
    fd_set readfs;
    fd_set masterfs;
    int max_fd;
    int current_fd;
    int _select;
    int flag_quit = 0;
    //Jalon 5
    char * dest_adress=malloc(100);
    char * dest_port=malloc(50);


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
    int sock_client = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if (sock_client < 0)
        error("erreur socket");
    //connect to remote socket
    max_fd = sock_client + 1;

    do_connect(sock_client, hostname, port, &sock_host);



    //clean the set before adding file descriptors
    FD_ZERO(&readfs);
    FD_ZERO(&masterfs);

    //add the fd for client connection
    FD_SET(sock_client, &readfs);
    FD_SET(sock_client, &masterfs);

    //add the fd for standard input
    FD_SET(STDIN_FILENO, &readfs);
    FD_SET(STDIN_FILENO, &masterfs);

    //read message from the server to know if the connection works fine
    if(read(sock_client,buffer_connect,sizeof(buffer_connect)) < 0)
        printf("erreur read");

    if (strcmp(buffer_connect, mess_conn_accepted) ==0 ){
        printf("Connection accepted.\n");
        printf("Please login with /nick <your pseudo>\n");


        //loop until /nick pseudo
        while(nickn_indicator == 0){
            fgets(input, sizeof(input), stdin);
            sub_in = str_sub(input, 0, 5);

            if (strcmp(sub_in, "/nick ") ==0){
                if (write(sock_client, input, strlen(input) ) < 0)//send /nick <pseudo>
                    printf("erreur write");
                if (read(sock_client, buffer, sizeof(buffer) ) < 0)// receive <pseudo>
                    printf("erreur read");
                printf("Welcome on chat %s \n", buffer);
                printf("\nEntrez un message \n");
                memset(buffer, '\0', sizeof(buffer));
                memset(input, '\0', sizeof(input));
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

    //create the socket, check for validity!
    port = atoi(argv[1]);
    sock_p2p = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if (sock_p2p < 0)
        error("erreur socket");

    max_fd = sock_p2p+1;

    //init the serv_add structure
    addr = init_serv_addr(port);
    addrlen =  sizeof(addr);

    //perform the binding
    //we bind on the tcp port specified
    if (bind(sock_p2p, (struct sockaddr*) & addr, sizeof(addr)) < 0)
        error("erreur bind");

    //specify the socket to be a p2p socket and listen for at most 20 concurrent client
    if (listen(sock_p2p, max_client) < 0)
        error("erreur listen");
    //add the fd for standard input
    FD_SET(sock_p2p, &readfs);
    FD_SET(sock_p2p, &masterfs);







    //get user input
    while(1){
        readfs = masterfs;

        _select = select(max_fd, &readfs, NULL, NULL,NULL);
        if (_select > 0){

            for(current_fd=0; current_fd<max_fd; current_fd++){
                if(FD_ISSET(current_fd,&readfs)){
                    // socket server
                    if(current_fd == sock_client){

                        //read message from the server
                        if(read(sock_client,buffer,sizeof(buffer)) < 0){
                            printf("erreur read");
                        }
                        //handle the case where the client want to end the connection
                        if (strcmp(input, "/quit\n") ==0 ){
                            printf("Connection terminated.\n");
                            flag_quit = 1;
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
                            printf("\nEntrez un message \n");
                        }
                        else if (buffer[0]== '['){
                            printf("%s \n ", buffer);
                            printf("\nEntrez un message \n");
                        }
                        else if (strcmp(str_sub(buffer,0,8), "/connect ") == 0){
                            extract_file(buffer, dest_adress, dest_port, 9);
                            port = atoi(dest_port);
                            //get the socket
                            int sock_file = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
                            if (sock_file < 0)
                                error("erreur socket");
                            //connect to remote socket

                            do_connect(sock_file, dest_adress, port, &sock_host);
                            if(write(i,"Test connexion client-client",50) < 0){
                                error("erreur write");
                            }

                        }

                        else{
                            printf("\n[Server] : %s \n", buffer);
                            printf("\nEntrez un message \n");
                        }


                    }
                    if(current_fd == STDIN_FILENO){

                        //printf("Entrez un message \n");
                        fgets(input, sizeof(input), stdin);

                        //send message to the server
                        if (write(sock_client, input,strlen(input)+1) < 0){
                            printf("erreur write");
                        }
                        printf("\nEntrez un message \n");

                    }
                    if(current_fd == sock_p2p){
                        //read message from the p2p  client
                        if(read(sock_client,buffer,sizeof(buffer)) < 0){
                            printf("erreur read");
                        }
                        printf("buffer_p2p= %s",buffer);

                    }
                    memset(buffer, '\0', sizeof(buffer)); // important pour le who 
                }
            }
            if(flag_quit == 1){
                break;
            }
        }
    }
    close(sock_client);
    return 0;
}

void do_connect(int sock_client, char hostname[], int port, struct sockaddr_in* sock_host ){

    memset(sock_host, '\0', sizeof(*sock_host));
    sock_host->sin_family = AF_INET;
    sock_host->sin_port = htons(port);
    inet_aton(hostname, & sock_host->sin_addr);

    if (connect(sock_client, (struct sockaddr*)  sock_host, sizeof(*sock_host)) < 0)
        error("erreur connect");

}
