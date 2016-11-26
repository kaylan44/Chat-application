#include "user.h"
#include <time.h>

struct user {
  char* nickname;
  char* date_conexion;
  char* addr_ip;
  int port;
  int id;
};

void set_user(struct user* user,  char* nickname, char* date_conexion, char* addr_ip, int port,int id){
    user->nickname = nickname;
    user->date_conexion = date_conexion;
    user->addr_ip = addr_ip;
    user->port = port;
    user->id=id;
}

void delete_user(struct user* user){
    memset(user, '\0', sizeof(struct user*));
}

char* get_nickname(struct user* user){
        return user->nickname;
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

char* get_pseudo(char* buffer, int position){
	int i=position;
	char* pseudo=malloc(20);
	while(1){
		if((buffer[i] == ' ')  || (buffer[i] == '\n') || (buffer[i] == '\0')){
			pseudo[i-position]='\0';
			return pseudo;
		}
		else{
			pseudo[i-position]=buffer[i];
			i++;
		}
	}	

}


void change_nickname(struct user* user,  char* nickname){
    user->nickname = nickname;
}