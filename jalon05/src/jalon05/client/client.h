#ifndef CLIENT_H_sqdfqsdfqsdf
#define CLIENT_H_sqdfqsdfqsdf

#include "../commons/constant.h"

struct info {
	int sock;
	int port;
	char username[USERNAME_LEN];
	char channel[USERNAME_LEN];
	int req; // used to file transfer
	int fd[2];
	char filename[MSG_BUFFER];
	char inbuf[READ_BUFFER];
	pthread_mutex_t mutex;
};

struct data {
	int port;
	char username[USERNAME_LEN];
	char ip[16];
	char filepath[MSG_BUFFER];
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
char handle_client_message(struct info* pinfo, char outbuf[SIZE_BUFFER]);

/**
 * function called when a file is received
 */
void* handle_file_receive(void* data);

/**
 * function called when we need to send a file
 */
void* handle_send_file(void* pdata);
#endif /* CLIENT_H_ */
