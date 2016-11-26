#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include "user.h"
#include "file.h"


int extract_file(char* buffer, char* receiving_user, char* filename, int position){
    int i=position;

    while((buffer[i] != ' ') ){
        if (buffer[i] == '\n'){
            return 1;
        }
        receiving_user[i-position]=buffer[i];
        i++;
    }
    receiving_user[i-position]='\0';
    i++;
    while((buffer[i] != '\n')){
        filename[i-position - strlen(receiving_user)-1]=buffer[i];
        i++;
    }
    filename[i-position - strlen(receiving_user) ]='\0';
    return 0;
}


void extract_addr_p2p(struct user* tab_user, char* receiving_user,char* dest_addr,char* dest_port){
    memset(dest_port, '\0', sizeof(dest_port));
    memset(dest_addr, '\0', sizeof(dest_addr));
    int i;
    for(i=0; i< MAX_CLIENT ;i++){
        if(user_existing(tab_user+i)){
            if(strcmp(receiving_user, get_nickname(tab_user+i))==0){
                strcat(dest_addr,get_address(tab_user+i));
                get_port((tab_user+i),dest_port);
                printf("addr= %s \n port= %s \n",dest_addr,dest_port);
            }

        }
    }
}