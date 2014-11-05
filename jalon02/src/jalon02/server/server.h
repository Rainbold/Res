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
 * Close the connection of a specific user
 */
void quit(struct connected_users* users_list, int id);

#endif //SERVER_H_QSGPNSGPOQNSPGOSNDFG
