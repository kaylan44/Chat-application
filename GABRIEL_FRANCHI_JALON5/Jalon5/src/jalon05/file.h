#ifndef FILE_H_
#define FILE_H_


// Extract the filename and receiving user from string buffer ( /send <user> <filename> )
int extract_file(char* buffer, char* receiving_user, char* filename, int position);

// Get the adress and port by looking in the tab_user for the name of the user
void extract_addr_p2p(struct user* tab_user, char* receiving_user,char* dest_addr,char* dest_port);

#endif /* FILE_H_ */
