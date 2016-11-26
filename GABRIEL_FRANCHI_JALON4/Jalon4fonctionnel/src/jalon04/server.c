#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/select.h>
#include "fonction.h"
#include "user.h"
#include <time.h>
#include <arpa/inet.h>
#include "salon.h"
#include "file.h"

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
    fd_set readfs;
    fd_set masterfs;
    int port;
    struct sockaddr_in addr;
    socklen_t addrlen;
    int i;
    int j;
    int max_fd;
    int max_client = 20;
    int _select;
    int max_fd_tmp;
    int sock_serv;
    int nb_connexion =0;
    char *mess_max_client ="max_cl";
    char *mess_conn_accepted ="co_acc";
    char* pseudo = malloc(20);
    char* all_user = malloc(200);
    char* date = malloc(20);
    char* addrINET = malloc(20);
    char* string_whois = malloc(100);
    int whois_indicator =0;
    int nick_user_indicator =0;
    char* msg_all = malloc(100);
    //Jalon5
    char* receiving_user = malloc(100);
    char* filename = malloc(100);



    struct user* tab_user = malloc(max_client* sizeof(*tab_user)) ;
    //struct user* tab_user = init_tab_user(max_client);
    //struct salon* tab_salon = init_salon(max_client);
    if (tab_user == NULL){
        printf("erreur allocation");
    }
    memset(tab_user,'\0', sizeof(*tab_user));



    struct salon* tab_salon = malloc(max_client* sizeof(*tab_salon)) ;
    //struct user* tab_user = init_tab_user(max_client);
    //struct salon* tab_salon = init_salon(max_client);
    if (tab_salon == NULL){
        printf("erreur allocation");
    }
    memset(tab_salon,'\0', sizeof(*tab_salon));



    if (argc != 2)
    {
        fprintf(stderr, "usage: RE216_SERVER port\n");
        return 1;
    }


    //create the socket, check for validity!
    port = atoi(argv[1]);
    sock_serv = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if (sock_serv < 0)
        error("erreur socket");

    max_fd = sock_serv+1;

    //init the serv_add structure
    addr = init_serv_addr(port);
    addrlen =  sizeof(addr);

    //perform the binding
    //we bind on the tcp port specified
    if (bind(sock_serv, (struct sockaddr*) & addr, sizeof(addr)) < 0)
        error("erreur bind");

    //specify the socket to be a server socket and listen for at most 20 concurrent client
    if (listen(sock_serv, max_client) < 0)
        error("erreur listen");

    printf("Serveur en écoute \n");

    //clean the set before adding file descriptors
    FD_ZERO(&readfs);
    FD_ZERO(&masterfs);

    //add the fd for server connection
    FD_SET(sock_serv, &readfs);
    FD_SET(sock_serv, &masterfs);


    for (;;)
    {
        readfs = masterfs;

        _select = select(max_fd, &readfs, NULL, NULL,NULL);
        if (_select > 0){
            max_fd_tmp = max_fd;
            for(i=0; i<max_fd_tmp; i++){
                if(FD_ISSET(i,&readfs)){
                    // socket server
                    if(i == sock_serv){

                        sock_acc = accept(sock_serv, (struct sockaddr*) & addr, &addrlen);
                        nb_connexion++;

                        if (sock_acc < 0)
                            error("Erreur acceptation");

                        //handle the case when there is too much client connected
                        if (nb_connexion > max_client){
                            if(write(sock_acc,mess_max_client,sizeof(mess_max_client)) < 0){
                                error("erreur write");
                            }
                            close(sock_acc);
                            nb_connexion--;
                        }
                        // send mess to client to let him know the connection has been accepted
                        else{
                            if(write(sock_acc,mess_conn_accepted,sizeof(mess_conn_accepted)) < 0){
                                error("erreur write");
                            }
                            // read the nickname (message receive is  /nick <pseudo>)
                            FD_SET(sock_acc, &masterfs);

                            if (sock_acc >= max_fd) {    // keep track of the max
                                max_fd =sock_acc+1;
                            }
                        }
                    } // end socket server


                    // socket client
                    else{

                        //Respond to the client messages until the client send "/quit"
                        if (strcmp(buffer, "/quit\n") != 0 ){
                            memset(buffer, '\0', sizeof(buffer));
                            //read what the client has to say
                            if (read(i,buffer,sizeof(buffer)) < 0){
                                error("erreur read");
                            }


                            //Deal with different cases when looking at the buffer
                            // /who
                            if (strcmp(buffer, "/who\n") == 0){
                                all_user = who(tab_user);
                                if(write(i,all_user,strlen(all_user)) < 0){
                                    error("erreur write");
                                }
                                memset(buffer, '\0', sizeof(buffer));

                            }

                            // --------------------- /whois ----------------------
                            else if (strcmp(str_sub(buffer,0,6), "/whois ") == 0){

                                pseudo=get_2_arg(buffer,7);

                                for(j=0;j<nb_connexion;j++){

                                    // Search the fitting user in the table
                                    if (strcmp(pseudo,get_nickname(tab_user +j))==0){
                                        desc_user(tab_user+j);


                                        whois_user(tab_user +j, pseudo, string_whois); //Fill the string with the right informations
                                        if(write(i,string_whois,200) < 0){
                                            error("erreur write");
                                        }
                                        memset(string_whois, '\0', sizeof(string_whois));
                                        whois_indicator = 1;
                                        break;
                                    }
                                }
                                if (whois_indicator == 0){
                                    if(write(i,"User not found in tab",50) < 0){
                                        error("erreur write");
                                    }
                                }
                                if (whois_indicator == 1){
                                    whois_indicator=0;
                                }


                            }

                            // /nick --- When the user want to log in or change his nickname
                            else if (strcmp(str_sub(buffer,0,5), "/nick ") == 0){
                                pseudo=get_2_arg(buffer,6);

                                // change the nickname
                                if (user_existing(tab_user+i-4)){
                                    change_nickname((tab_user+i-4), pseudo);
                                    printf("pseudo modifié : %s\n", get_nickname(tab_user + i -4));
                                    if(write(i,"pseudo modifié",20) < 0){
                                        error("erreur write");
                                    }
                                }
                                else{
                                    pseudo=get_2_arg(buffer,6);

                                    if(write(i,pseudo,strlen(pseudo)) < 0){
                                        error("erreur write");
                                    }
                                    //Load the current date
                                    getdate(date);
                                    //Get the IP adress
                                    addrINET = inet_ntoa(addr.sin_addr);
                                    // create a user
                                    set_user((tab_user+i-4), pseudo, date, addrINET, addr.sin_port, i-4);
                                    printf("connexion avec %s\n", get_nickname(tab_user + i -4));
                                }
                            }
                            // /msgall
                            else if (strcmp(str_sub(buffer,0,7), "/msgall ") == 0){

                                get_msgall(buffer,msg_all);
                                printf("msg= %s \n",msg_all);
                                send_all(tab_user, msg_all, i-4);

                                memset(msg_all, '\0', sizeof(msg_all));
                                memset(buffer, '\0', sizeof(buffer));

                            }
                            // /unicast
                            else if (strcmp(str_sub(buffer,0,4), "/msg ") == 0){

                                unicast(tab_user,buffer, i-4);
                                memset(buffer, '\0', sizeof(buffer));

                            }

                            // /create (salon)
                            else if (strcmp(str_sub(buffer,0,7), "/create ") == 0){

                                create_salon(get_2_arg(buffer,8), tab_user+i-4, tab_salon );
                                memset(buffer, '\0', sizeof(buffer));

                            }
                            // /join (salon)
                            else if (strcmp(str_sub(buffer,0,5), "/join ") == 0){

                                join_salon(tab_user+i-4, tab_salon,get_2_arg(buffer,6));
                                memset(buffer, '\0', sizeof(buffer));
                            }
                            // /quit (salon)
                            else if(strcmp(str_sub(buffer,0,5), "/quit ") == 0){
                                printf("affiche: %s\n", get_2_arg(buffer,6));
                            //    if (strcmp(get_2_arg(buffer,6), "\0") == 0){
                                //    printf("im in quit\n");
                                quit_salon(tab_salon, tab_user+i-4, get_2_arg(buffer,6));
                                memset(buffer, '\0', sizeof(buffer));
                                //}
                            }
                            else if(strcmp(str_sub(buffer,0,5), "/send ") == 0){
                                extract_file(buffer, receiving_user, filename, 6)


                            }


                            //write back to the client

                            else{
                                if(get_user_salon(tab_user+i-4) != NULL){
                                    write_in_salon(tab_user,buffer,tab_user+i-4 ,i-4);
                                }
                                else{

                                    printf("Message reçu du client %s : %s \n",get_nickname(tab_user +i -4), buffer);
                                    if(write(i,buffer,sizeof(buffer)) < 0){
                                        error("erreur write");
                                    }
                                }
                            }
                        }

                        // /quit
                        else { //if(strcmp(str_sub(buffer,0,5), "/quit\n") ==0 )
                            quit_salon(tab_salon, tab_user+i-4, get_2_arg(buffer,6));
                            printf("fin de la connexion avec %s \n",get_nickname(tab_user +i -4));
                            delete_user(tab_user+i-4);
                            close(i);
                            nb_connexion--;
                            FD_CLR(i,&masterfs);
                            memset(buffer, '\0', sizeof(buffer));
                        }
                    }
                }




            }
        }




        else{
            printf("erreur select = %d \n",_select);
        }
    }

    //clean up server socketsock_acc
    close(sock_serv);
    return 0;
}

struct sockaddr_in init_serv_addr(int port){
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(port) ;
    return addr;
}
