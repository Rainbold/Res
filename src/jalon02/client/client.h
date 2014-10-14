#ifndef CLIENT_H_sqdfqsdfqsdf
#define CLIENT_H_sqdfqsdfqsdf

#include "../commons/constant.h"

#define PM_COLOR
#define CHANNEL_COLOR
#define ALL_COLOR
#define SERVER_COLOR
#define ERROR_MSG

/**
 * a function that given the address and the port fill the addrinfo
 */
int get_addr_info(struct sockaddr_in* serv_info, char* host, char* port);

/**
 * a function that is called when we receive a message from the server
 */
void* handle_server_message(void* psock);

/**
 * a function called with user input
 */
void handle_client_message(int sock, char outbuf[SIZE_BUFFER]);

/**
 * function called when a file is received
 */
void handle_file_receive(const char *file_path, const char* addr,
		const char* port);

/**
 * function called when we need to send a file
 */
void handle_send_file(const int socket, const char* file_path);

#endif /* CLIENT_H_ */
