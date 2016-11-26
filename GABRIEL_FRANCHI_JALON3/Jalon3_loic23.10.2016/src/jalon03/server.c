#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/select.h>
#include "fonction_res216.c"
#include "user.c"
#include <time.h>
#include <arpa/inet.h>

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



    struct user* tab_user = malloc(20* sizeof(*tab_user)) ;
    //struct user* tab_user = malloc(20* sizeof(struct user*)) ;
    if (tab_user == NULL)
	     printf("erreur allocation");
    memset(tab_user,'\0', sizeof(*tab_user));

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

                  if(i == sock_serv){

                      sock_acc = accept(sock_serv, (struct sockaddr*) & addr, &addrlen);
                      nb_connexion++;

                      if (sock_acc < 0)
                          error("Erreur acceptation");
                      //handle the case when there is too much client connected
                      else if (nb_connexion > max_client){
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
                          memset(buffer, '\0', sizeof(buffer));
                  			  if (read(sock_acc,buffer,sizeof(buffer)) < 0)
                  			  	error("erreur read");

                          pseudo=get_pseudo(buffer,6);

                  			  if(write(sock_acc,pseudo,sizeof(pseudo)) < 0){
                              error("erreur write");
                          }

                          //Load the current date
                          getdate(date);
                          
                          //Get the IP adress
                          addrINET = inet_ntoa(addr.sin_addr);

                          // create a user
                  			  set_user((tab_user+sock_acc-4), pseudo, date, addrINET, port, sock_acc-4);
                          printf("connexion avec %s\n", get_nickname(tab_user + sock_acc -4));
                          FD_SET(sock_acc, &masterfs);

                          if (sock_acc >= max_fd) {    // keep track of the max
                              max_fd =sock_acc+1;
                          }


                      }
                  }
                  else{

                      //Respond to the client messages until the client send "/quit"
                      if (strcmp(buffer, "/quit\n") != 0 ){
                          memset(buffer, '\0', sizeof(buffer));
                          //read what the client has to say
                          if (read(i,buffer,sizeof(buffer)) < 0){
                              error("erreur read");
                          }

                          printf("Message reçu du client %s : %s \n",get_nickname(tab_user +i -4), buffer);

                          // /who
                          if (strcmp(buffer, "/who\n") == 0){
                  			      all_user = who(tab_user);
                  			      if(write(i,all_user,strlen(all_user)) < 0){
                                 error("erreur write");
                              }
                              memset(buffer, '\0', sizeof(buffer));

                  			  }
                          // /whois
                          if (strcmp(str_sub(buffer,0,6), "/whois ") == 0){

                            pseudo=get_pseudo(buffer,7);

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

                          //When the user want to change his nickname
                          if (strcmp(str_sub(buffer,0,5), "/nick ") == 0){
                            pseudo=get_pseudo(buffer,6);                            
                            getdate(date); //Load the current date                            
                            addrINET = inet_ntoa(addr.sin_addr); //Get the IP adress

                            // change the nickname
                            change_nickname((tab_user+i-4), pseudo);
                            printf("pseudo modifié : %s\n", get_nickname(tab_user + i -4));
                            if(write(i,"pseudo modifié",20) < 0){
                                 error("erreur write");
                              }
                          }
                          else{
                             //write back to the client
                             if(write(i,buffer,sizeof(buffer)) < 0)
                                error("erreur write");
			                    }
                      }

                      if (strcmp(buffer, "/quit\n") ==0 ){
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
