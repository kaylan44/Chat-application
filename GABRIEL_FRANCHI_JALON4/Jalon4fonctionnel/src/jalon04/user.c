#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include "user.h"

/*
struct user {
char* nickname;
char* date_conexion;
char* addr_ip;
int port;
int id;
};
*/
struct user* init_tab_user(int max){
    struct user* tab_user = malloc(max* sizeof(struct user*)) ;
    if(tab_user == NULL){
        printf("erreur allocation user");
    }
    memset(tab_user,'\0', sizeof(*tab_user));
    return tab_user;
}

void set_user(struct user* user,  char* nickname, char* date_conexion, char* addr_ip, int port,int id){
    user->nickname = nickname;
    user->date_conexion = date_conexion;
    user->addr_ip = addr_ip;
    user->port = port;
    user->id=id;
    user->salon = NULL;
}

void delete_user(struct user* user){
    memset(user, '\0', sizeof(struct user*));
}

char* get_nickname(struct user* user){
    return user->nickname;
}
int get_id(struct user* user){
    return user->id;
}
char* get_address(struct user* user){
    return user->address;
}
char* get_port(struct user* user){
    char port[10];
    sprintf(port,"%d", user->port);
    return port;
}
char* get_user_salon(struct user* user){
    return user->salon;

}


void desc_user(struct user* user){
    if (get_nickname(user) != NULL){
        printf("nickname = %s\n", user->nickname);
        printf("date_conexion = %s\n", user->date_conexion);
        printf("addr_ip = %s\n", user->addr_ip);
        printf("port = %d\n", user->port);
        printf("id = %d\n", user->id);
    }
}



char* who(struct user* user){
    int i;
    char* str_out = calloc(200,sizeof(char));

    if (str_out != NULL){
        for (i =0; i<10; i++){
            if (get_nickname(user+i) != NULL){
                strcat(str_out, get_nickname(user+i));
                strcat(str_out, "\n");
            }
        }
    }
    return str_out;
}

int user_existing(struct user* user){

    if (get_nickname(user) == NULL){
        return 0;
    }else{
        return 1;
    }

}





void getdate(char* date_in){


    time_t secondes;
    struct tm instant;
    char date[20] ={0};
    char tmp[5];
    time(&secondes);
    instant=*localtime(&secondes);



    sprintf(tmp, "%d", instant.tm_mday);
    strcat(date,tmp);
    strcat(date,"/");

    sprintf(tmp, "%d", instant.tm_mon+1);
    strcat(date,tmp);
    strcat(date,"/");


    sprintf(tmp,"%d", instant.tm_year+1900);
    strcat(date,tmp);
    strcat(date,"@");

    sprintf(tmp, "%d", instant.tm_hour);
    strcat(date,tmp);
    strcat(date,":");

    sprintf(tmp, "%d", instant.tm_min);
    strcat(date,tmp);


    strcpy(date_in, date);


}



void whois_user(struct user* user, char* nickname, char* string_whois){

    char port[10];
    sprintf(port,"%d", user->port);

    strcat(string_whois,nickname);
    strcat(string_whois," connected since ");

    strcat(string_whois,user->date_conexion);
    strcat(string_whois," with IP address ");

    strcat(string_whois,user->addr_ip);
    strcat(string_whois," and port number ");

    strcat(string_whois,port);

}





void change_nickname(struct user* user,  char* nickname){
    user->nickname = nickname;
}

void get_msgall(const char* buffer, char* msg){
    int i=8;
    while(buffer[i] != '\n'){
        msg[i-8]=buffer[i];
        i++;
    }
    msg[i-8]='\0';
}

void send_all(struct user* tab_user, char* msgall, int sending_user){
    int i;
    char* msgall_write = malloc(130);
    for(i=0; i<20;i++){
        if(user_existing(tab_user+i) && (sending_user != i)){

            strcat( msgall_write,"[");
            strcat( msgall_write,get_nickname(tab_user+sending_user));
            strcat( msgall_write,"](msgall) : ");
            strcat( msgall_write,msgall);

            if(write(i+4,msgall_write, strlen(msgall_write) ) <0){
                printf("erreur sendall");
            }
        }
    }
}


void extract_unicast(char* buffer, char* receiving_user, char* msg_to_send, int position){
    int i=position;

    while((buffer[i] != ' ') ){
        receiving_user[i-position]=buffer[i];
        i++;
    }
    receiving_user[i-position]='\0';
    i++;
    while((buffer[i] != '\n') ){
        msg_to_send[i-position - strlen(receiving_user)-1]=buffer[i];
        i++;
    }
    msg_to_send[i-position - strlen(receiving_user) ]='\0';
}



void unicast(struct user* tab_user, char* buffer, int sending_user){
    int i;
    char* unicast_write = malloc(200);
    char* msg_unicast = malloc(100);
    char* receiving_user = malloc(30);

    extract_unicast(buffer, receiving_user, msg_unicast,5);

    for(i=0; i<20;i++){
        if(user_existing(tab_user+i)){
            if(strcmp(receiving_user, get_nickname(tab_user+i))==0){
                strcat( unicast_write,"[");
                strcat( unicast_write,get_nickname(tab_user+sending_user));
                strcat( unicast_write,"] : ");
                strcat( unicast_write,msg_unicast);
                if(write(i+4,unicast_write, strlen(unicast_write) ) <0){
                    printf("erreur uniscast");
                }
            }
        }
    }
}

char* get_salon(struct user* user){
    return user->salon;
}

void set_salon_user(struct user* user, char* name_salon){
    user->salon = name_salon;
}
void get_info_p2p(struct user* tab_user, char* name, char* dest_address, char* dest_port){
        for(i=0; i<20;i++){
        if(user_existing(tab_user+i)){
            if(strcmp(name, get_nickname(tab_user+i))==0){
                dest_address=
            }
        }
    }


}
