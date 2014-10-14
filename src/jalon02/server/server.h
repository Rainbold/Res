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
 * handle the event when the server socket receives a new connection
 * @return the new client socket fd
 */
int handle_server_socket_event(const int server_socket_fd);

/**
 * handle the event when a client write something to us
 */
void handle_client_socket_event(int client_socket_fd);

/**
 * parse a client input and react accordingly
 */
void parse_client_input(const char buffer[SIZE_BUFFER], const int client_socket_fd);

/**
 * Send a message to all users, except on the fd for the sender.
 */
void send_broadcast_by_user_name(const struct connected_users* users_list, const char buffer[MSG_BUFFER], const char uname_src[USERNAME_LEN]);
void send_broadcast_by_fd(const char buffer[SIZE_BUFFER], const int fd);

/**
 * Send a message to a user by username
 */
void send_unicast(const struct connected_users* users_list, const char buffer[SIZE_BUFFER], const char *uname,const char* uname_src);

/**
 * Send a message to users by their usernames
 */
void send_multicast(const char buffer[SIZE_BUFFER], const char **unames,const char* uname_src);

/**
 * main function that understands the type of packets
 */
void process_client_request(const char buffer[SIZE_BUFFER], const int client_socket_fd);

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


void send_msg(int sock, char* username, char* msg, char* color);

#endif //SERVER_H_QSGPNSGPOQNSPGOSNDFG
