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
 * Send a message to all users, except on the fd for the sender.
 */
void send_broadcast_by_user_name(const struct connected_users* users_list, const char buffer[MSG_BUFFER], const char uname_src[USERNAME_LEN]);

/**
 * Send a message to a user by username
 */
void send_unicast(const struct connected_users* users_list, const char buffer[SIZE_BUFFER], const char *uname,const char* uname_src);

/**
 * Send a message to users by their usernames
 */
void send_multicast(struct connected_users* users_list, char buffer[SIZE_BUFFER], char *cname, char* uname_src);

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
 * Returns the id associated to the channel name
 */
int find_channel_id(struct connected_users* users_list, char* name);

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
 * Creates a channel called name
 */
void create(struct connected_users* users_list, char* name, int id);

/**
 * Joins a channel called name
 */
void join(struct connected_users* users_list, char* name, int id);

/**
 * Quits a channel called name
 */
void quit_chan(struct connected_users* users_list, char* name, int id, int is_quit);

/**
 * Redirects a file request to a user
 */
void send_file(struct connected_users* users_list, char* name, char* msg, int id_src);

/**
 * Sends a message which can be colored
 */
void send_msg(int sock, char* msg, char* color);

#endif //SERVER_H_QSGPNSGPOQNSPGOSNDFG
