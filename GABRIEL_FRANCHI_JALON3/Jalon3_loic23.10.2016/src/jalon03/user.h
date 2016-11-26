#ifndef USER_H_
#define USER_H_


struct user;

void set_user(struct user* user,  char* nickname, char* date_conexion, char* addr_ip, int port,int id);
void desc_user(struct user* user);
char* get_nickname(struct user* user);
char* who(struct user* user);
void delete_user(struct user* user);

void getdate(char* date_in);
void whois_user(struct user* user, char* nickname, char* string_whois);
char* get_pseudo(char* buffer, int position);

#endif /* USER_H_ */
