#ifndef SALON_H_
#define SALON_H_
#include "user.h"


struct salon{
    char* name;
    int current_client_nb;
};

struct salon* init_salon(int max);
void set_salon(struct salon* salon, char* name);
void add_client_nb(struct salon* salon);

void delete_salon(struct salon* salon);
char* get_salon_name(struct salon* salon);
void create_salon(char* name, struct user* first_user, struct salon* tab_salon);
int salon_existing(struct salon* salon);
struct user* get_user(struct salon* salon, int j);
void quit_salon(struct salon* salon, struct user* user, char* name_salon);
void write_in_salon(struct user* tab_user, char* msgall, struct user* sending_user ,int user_id );


#endif /* SALON_H_ */
