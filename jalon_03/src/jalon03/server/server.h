/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

#ifndef SERVER_H_QSGPNSGPOQNSPGOSNDFG
#define SERVER_H_QSGPNSGPOQNSPGOSNDFG

#include "../commons/constant.h"

/**
 * Initialize the connected_users structure
 */
void init_users(int sock, struct connected_users* users_list);

/**
 * Accepts the incoming connections
 */
void* server_accepting(void* p_data);

/**
 * Handles the client's associated thread
 */
void* client_handling(void* p_data);

/**
 * Returns the id associated to the username name
 */
int find_username_id(struct connected_users* users_list, char* name);

/**
 * Changes a specific username
 */
void nick(struct connected_users* users_list, char pname[USERNAME_LEN], int id);

/**
 * Sends the connected users list
 */
void whois(struct connected_users* users_list, char* name, int id);

/**
 * Sends the connected users list
 */
void who(struct connected_users* users_list, int id);

/**
 * Disconnects the user
 */
void quit(struct connected_users* users_list, int id);

/**
 * Sends a message which can be colored
 */
void send_msg(int sock, char* msg, char* color);

#endif //SERVER_H_QSGPNSGPOQNSPGOSNDFG
