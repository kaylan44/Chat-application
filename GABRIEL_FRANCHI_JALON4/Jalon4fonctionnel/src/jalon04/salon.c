    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>

#include "user.h"
#include "salon.h"

struct salon* init_salon(int max){
    struct salon* tab_salon = malloc(max* sizeof(struct salon*)) ;
    if(tab_salon == NULL){
        printf("erreur allocation salon");
    }
    memset(tab_salon,'\0', sizeof(*tab_salon));
    return tab_salon;
}

//void set_user_salon(t)
void set_salon(struct salon* salon, char* name){
    salon->name = name;
    salon->current_client_nb = 0;
}
void add_client_nb(struct salon* salon){
    salon->current_client_nb++;
}

void delete_salon(struct salon* salon){
    memset(salon, '\0', sizeof(struct salon*));
}

char* get_salon_name(struct salon* salon){
    return salon->name;
}

int salon_existing(struct salon* salon){

    if (get_salon_name(salon) == NULL){
        return 0;
    }else{
        return 1;
    }

}

void create_salon(char* name, struct user* user, struct salon* tab_salon){
    int salon_create_indicator =0;
    int i;
    char * msg_create=malloc(200);

    // le salon existe?
    for(i=0; i<20;i++){// i parcour salon
        if(salon_existing(tab_salon+i)){
            if(strcmp(name, get_salon_name(tab_salon+i))==0){
                strcat(msg_create,"Le salon existe déja, veuillez changer le nom de votre nouveau salon.");
                if(write(get_id(user)+4,msg_create,strlen(msg_create)) <0){
                    printf("erreur salon err_msg");
                }
                salon_create_indicator=1;
            }
        }
    }


    if (salon_create_indicator == 0){
        for(i=0; i<20;i++){
            if(!salon_existing(tab_salon+i)){
                set_salon(tab_salon+i, name);
                printf("Salon créé\n");
                strcat(msg_create,"You have created channel ");
                strcat(msg_create,name);
                strcat(msg_create," \n");
                printf("%s\n", msg_create);
                if(write(get_id(user)+4,msg_create,strlen(msg_create)) <0){
                    printf("erreur salon err_msg");
                }
                break;
            }
        }
    }
}


void join_salon(struct user* user, struct salon* tab_salon, char* name_salon){
    char* send = malloc(50);
    int i;
    int flag_existing_salon=0;


    if(get_salon(user) != NULL){
        if(strcmp(get_salon(user), name_salon)==0 ){

            send = "Vous etes deja dans le salon";
            if(write(get_id(user)+4,send,strlen(send)) <0){
                printf("erreur salon join");
            }
        }
        else{
            send = "Vous ne pouvez pas rejoindre un autre salon";
            if(write(get_id(user)+4,send,strlen(send)) <0){
                printf("erreur salon join");
            }
        }
    }
    else{

        for(i=0; i<20;i++){ // parcours salon
            if(salon_existing(tab_salon+i)){
                if(strcmp(name_salon, get_salon_name(tab_salon+i))==0){ // On se trouve dans le bon salon
                    set_salon_user(user, name_salon);
                    add_client_nb(tab_salon+i);

                    send = "Vous avez rejoint le salon";
                    if(write(get_id(user)+4,send,strlen(send)) <0){
                        printf("erreur salon join");
                    }
                    flag_existing_salon = 1;
                    break;

                }
            }

        }


        if(flag_existing_salon == 0){    
            send = "le salon n'existe pas";
            if(write(get_id(user)+4,send,strlen(send)) <0){
                printf("erreur salon join");
            }
        }

    }
}

void quit_salon(struct salon* tab_salon, struct user* user, char* name_salon){
    char* send = malloc(50);
    if(get_salon(user) != NULL){
        int i;
        
        send = "Vous  avez quitté le salon";
        for(i=0; i<20;i++){ // parcours salon
            if(salon_existing(tab_salon+i)){
                if(strcmp(name_salon, get_salon_name(tab_salon+i))==0){ // On se trouve dans le bon salon
                    (tab_salon+i)->current_client_nb--;
                    set_salon_user(user, NULL);
                    if ((tab_salon+i)->current_client_nb == 0){
                        delete_salon(tab_salon+i);
                    }
                    if(write(get_id(user)+4,send,strlen(send)) <0){
                        printf("erreur salon quit");
                    }
                }
            }
        }
    }else{
        send = "Vous n'etes dans aucun salon";
        if(write(get_id(user)+4,send,strlen(send)) <0){
            printf("erreur salon quit");
        }
    }
}

void write_in_salon(struct user* tab_user, char* msgall, struct user* sending_user ,int user_id ){
    int i;
    char* msgall_write = malloc(130);
    int flag_other_user=0;
    for(i=0; i<20;i++){
        if(user_existing(tab_user+i) && (user_id != i) && (get_user_salon(tab_user+i) != NULL)){
            if(strcmp(get_user_salon(tab_user+i),get_user_salon(sending_user)) == 0){

                strcat( msgall_write,"[");
                strcat( msgall_write,get_nickname(tab_user+user_id));
                strcat( msgall_write,"](salon) : ");
                strcat( msgall_write,msgall);

                if(write(i+4,msgall_write, strlen(msgall_write) ) <0){
                    printf("erreur sendall salon");
                }
                flag_other_user=1;
            }
        }
    }
    if(flag_other_user == 0){
        msgall_write="Il n'y a pas d'autres utilisateurs dans le salon.";
        if(write(user_id+4,msgall_write, strlen(msgall_write) ) <0){
            printf("erreur sendall salon");
        }
    }
}


