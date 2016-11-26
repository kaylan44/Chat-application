#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <errno.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "fonction.h"
#include "user.h"
#include "salon.h"
#include "file.h"
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>






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
    char path[SIZE_MSG];
    char nick[SIZE_MSG];
    struct sockaddr_in addr;
    socklen_t addrlen;
    int sock_p2p;
    int port_p2p;
    int port_recv;
    int sock_file;
    int sock_recv;



    struct sockaddr_in sock_host;
    struct sockaddr_in addr_p2p;
    struct sockaddr_in sock_clientp2p;

    if (argc != 3)
    {
        fprintf(stderr,"usage: RE216_CLIENT hostname port port_p2p\n");
        return 1;
    }

    //get address info from the server
    port = atoi(argv[2]);



    char *hostname = argv[1];

    //create the socket
    int sock_client = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if (sock_client < 0)
        error("erreur socket");

    //connect to remote socket
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
        error("erreur read");

    if (strcmp(buffer_connect, mess_conn_accepted) ==0 ){
        printf("Connection accepted.\n");
        printf("Please login with /nick <your pseudo>\n");


        //loop until /nick pseudo
        while(nickn_indicator == 0){
            fgets(input, sizeof(input), stdin);
            sub_in = str_sub(input, 0, 5);

            if (strcmp(sub_in, "/nick ") ==0){
                if (write(sock_client, input, strlen(input) ) < 0)//send /nick <pseudo>
                    error("erreur write");
                if (read(sock_client, buffer, sizeof(buffer) ) < 0)// receive port_p2p + nick
                    error("erreur read");

                //port_p2p=port du client connecté au serveur pour pouvoir ensuite faire un bind
                port_p2p = atoi(get_1_arg(buffer));
                sprintf(nick, "%s",get_2_arg(buffer));

                printf("Welcome on chat %s\n", nick);
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
    sock_p2p = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if (sock_p2p < 0)
        error("erreur socket");

    max_fd = sock_p2p+1;

    //init the p2p_addr structure
    addr_p2p = init_serv_addr(port_p2p);
    addrlen =  sizeof(addr_p2p);

    //perform the binding
    //we bind on the tcp port specified
    if (bind(sock_p2p, (struct sockaddr*) & addr_p2p, sizeof(addr_p2p)) < 0)
        error("erreur bind");

    //specify the socket to be listening for incoming connections
    if (listen(sock_p2p,  MAX_CLIENT ) < 0)
        error("erreur listen");

    //add the fd for p2p connections
    FD_SET(sock_p2p, &readfs);
    FD_SET(sock_p2p, &masterfs);


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
                            error("erreur read");
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
                            printf("\n------------------------------ \n");
                        }
                        else if (buffer[0]== '['){
                            printf("%s \n ", buffer);
                            printf("\n------------------------------ \n");
                        }
                        // P2P (server send msg with /connect after client used /send )
                        else if (strcmp(str_sub(buffer,0,8), "/connect ") == 0){
                            memset(buffer_connect, '\0', sizeof(buffer_connect));
                            dest_adress = get_2_arg(buffer);
                            port_recv = atoi(get_3_arg(buffer));
                            printf("port_recv=%d\n",port_recv);
                            sprintf(path,"%s", get_3_arg(input));
                            //get the socket

                            sock_file = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
                            if (sock_file < 0){
                                error("erreur socket");
                            }

                            //connect to remote socket
                            do_connect(sock_file, dest_adress, port_recv, &sock_clientp2p);
                            //read message from the server to know if the connection works fine
                            if(read(sock_file,buffer_connect,sizeof(buffer_connect)) < 0){
                                error("erreur read");
                            }
                            printf("P2P : %s\n",buffer_connect);

                            printf("\n------------------------------ \n");

                            int fdfile = open(path, O_RDONLY);
                            printf("fdfile = %i\n", fdfile);
                            struct stat buf;
                            fstat(fdfile, &buf);

                            char sizec[10];
                            int size_file_send = (int) buf.st_size;
                            sprintf(sizec,"%d", (int) buf.st_size);
                            printf("size %s\n", sizec);

                            //user1 wants you to accept the transfer of the file named "file.txt". Do you accept? [Y/n]

                            sprintf(buffer, "%s", nick);
                            strcat(buffer, " wants you to accept the transfer of the file named ");
                            strcat( buffer, get_3_arg(input));
                            strcat(buffer, ". Do you accept? [y/n]\n");
                            //printf("input ? %s\n", buffer);
                            if (write(sock_file, buffer, strlen(buffer))<0){
                                error("write ");
                            }
                            memset(buffer, '\0', strlen(buffer));
                            if (read(sock_file, buffer, SIZE_MSG) < 0){
                                error("read y/n");
                            }
                            printf("erreur de buffer? %s\n", buffer);
                            //printf("get arg1 %s\n", get_1_arg(buffer));
                            if (strcmp(get_1_arg(buffer), "y") == 0){
                                printf("%s a accepter le transfert \n", get_2_arg(buffer));
                                if (write(sock_file, sizec, SIZE_MSG)<0){
                                    error("write size");
                                }

                                off_t offset = 0;
                                int nb_sent=0;
                                while (((nb_sent = sendfile(sock_file, fdfile, &offset, SIZE_MSG)) > 0) && (size_file_send > 0)) {
                                      size_file_send -= nb_sent;
                                      printf("nb_sent : %d\n",nb_sent );
                                      printf("offset: %d\n", (int) offset );
                                }
                            }
                            else{
                              printf("%s a annulé l'operartion \n", get_2_arg(buffer));
                            }

                            /*if (sendfile(sock_file, fdfile, NULL, buf.st_size) < 0){
                                error("sendfile");
                            }*/

                            printf("\n------------------------------ \n");
                            close(fdfile);
                            close(sock_file);


                        }

                        else{
                            printf("\n[Server] : %s \n", buffer);
                            printf("\n------------------------------ \n");
                        }


                    }

                    //get user input
                    if(current_fd == STDIN_FILENO){
                        fgets(input, sizeof(input), stdin);

                            //send message to the server
                        if (write(sock_client, input,strlen(input)+1) < 0){
                            error("erreur write");
                        }
                        printf("\n------------------------------ \n");

                    }

                    // Handle the connections for p2p
                    if(current_fd == sock_p2p){
                            //read message from the p2p  client
                        sock_recv = accept(sock_p2p, (struct sockaddr*) & addr_p2p, &addrlen);
                        printf("P2P accepted\n");
                        if(write(sock_recv,"Connexion with the distant client P2P",50) < 0){
                            error("erreur read");
                        }
                        printf("\n------------------------------ \n");

                        if (read(sock_recv, buffer, SIZE_MSG) < 0){
                          error("read y/n");
                        }
                        printf("%s", buffer );
                        fgets(input, sizeof(input), stdin);
                        printf("input %s\n", input);
                        sprintf(buffer, "%c", input[0]);
                        strcat(buffer, " ");
                        strcat(buffer, nick);
                        printf("a envoyer:%s\n", buffer);
                        if(write(sock_recv, buffer, strlen(buffer))< 0){
                          error("write answer");
                        }


                        if(read(sock_recv, buffer, SIZE_MSG) < 0){
                            error("erreur read");
                        }

                        int size_file_rcv = atoi(buffer);
                        printf("size_file_recv : %d\n", size_file_rcv);


                        int received_file = open("/home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON5/Jalon5/build/jalon05/receive/file_received", O_CREAT | O_WRONLY, S_IRWXU );

                        //int received_file = open("/home/loic/Desktop/Jalon5/src/jalon05/receive.txt", O_CREAT, S_IRWXU | S_IRWXG |S_IWOTH);
                        int nb_rcv = 0;
                        while (((nb_rcv = read(sock_recv, buffer, SIZE_MSG)) > 0) && (size_file_rcv > 0)) {
		                        if(write(received_file, buffer, nb_rcv) < 0){
                              error("write in the file receive");
                            }
                            //printf("nb_receive %d\n", nb_rcv);
		                        size_file_rcv -= nb_rcv;
                            //printf("size_file_rcv en cours : %d\n", size_file_rcv);
                        }
                        //printf("si 0, tout a ete ecrit : %d\n", size_file_rcv);

                        /*if(read(sock_recv, buffer,SIZE_MSG) < 0){
                            printf("erreur read");
                        }*/

                      //  printf("fichier lu : %s\n",test);
                        close(received_file);
                        close(sock_recv);
                         printf("\n------------------------------ \n");
                    }/*
                    if(current_fd == sock_file){

                        if(read(sock_file,buffer,sizeof(buffer)) < 0){
                            printf("erreur read");
                        }
                        printf("%s \n ", buffer);
                        printf("\n------------------------------ \n");
                    }*/
                    memset(buffer, '\0', sizeof(buffer)); // important pour le who DAAMMMMMNNNN 10h dessus

                }
                if(flag_quit == 1){
                    break;
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
