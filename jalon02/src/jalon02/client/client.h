#ifndef CLIENT_H_sqdfqsdfqsdf
#define CLIENT_H_sqdfqsdfqsdf

#include "../commons/constant.h"

#define PM_COLOR
#define CHANNEL_COLOR
#define ALL_COLOR
#define SERVER_COLOR
#define ERROR_MSG

struct info {
	int sock;
	int port;
	int running;
	char username[USERNAME_LEN];
};

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
void handle_client_message(struct info* pinfo, char outbuf[SIZE_BUFFER]);

#endif /* CLIENT_H_ */
