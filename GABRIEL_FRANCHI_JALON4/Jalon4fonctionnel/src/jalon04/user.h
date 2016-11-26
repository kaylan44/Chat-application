#ifndef USER_H_
#define USER_H_


//struct user;

struct user {
  char* nickname;
  char* date_conexion;
  char* addr_ip;
  int port;
  int id;
  char* salon;
};

struct user* init_tab_user(int max);
void set_user(struct user* user,  char* nickname, char* date_conexion, char* addr_ip, int port,int id);
void desc_user(struct user* user);
char* get_nickname(struct user* user);
int get_id(struct user* user);
char* get_user_salon(struct user* user);
char* who(struct user* user);
void delete_user(struct user* user);

void getdate(char* date_in);
void whois_user(struct user* user, char* nickname, char* string_whois);
char* get_pseudo(char* buffer, int position);
void get_msgall(const char* buffer,char* msg);
void send_all(struct user* tab_user, char* msgall, int sending_user);

void extract_unicast(char* buffer, char* pseudo, char* msg_to_send, int postion);
void unicast(struct user* tab_user, char* buffer, int sending_user);

char* get_salon(struct user*);
void set_salon_user(struct user* user, char* name_salon);

#endif /* USER_H_ */
