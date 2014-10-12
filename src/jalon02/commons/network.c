/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <regex.h>
#include <resolv.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include "user.h"
#include "callbacks.h"
#include "colors.h"
#include "network.h"

void error(const char* msg) {
	perror(msg);
	exit(-1);
}

/**************************************************
 * In this file, you should implement every code that
 * can be used by both client and server
 */

int do_socket(int domain, int type, int protocol) {
	int yes = 1;
	int fd = socket(domain, type, protocol);
	if(fd == -1) {
		error("ERROR with socket() in do_socket()");
	}
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		error("ERROR setting socket options");
	return fd;
}

void do_connect(int sockfd, const struct sockaddr_in *addr, socklen_t addrlen) {
	if( connect(sockfd, (struct sockaddr*)addr, addrlen)  != 0 )
		error("Error with connect() in do_connect()");
}

void init_serv_addr(const char* port, struct sockaddr_in *serv_addr) {
	memset(serv_addr, 0, sizeof(*serv_addr));
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(atoi(port));
	serv_addr->sin_addr.s_addr = INADDR_ANY;
}

void do_bind(const int fd, struct sockaddr_in *serv_addr) {
	if( bind(fd, (struct sockaddr*) serv_addr, sizeof(*serv_addr)) == -1 )
		error("Error with bind() in do_bind()");
}

void do_accept(const int server_fd, int *client_fd, struct sockaddr_in *client_addr, socklen_t addrlen) {
	int fd = accept(server_fd, (struct sockaddr*)client_addr, &addrlen);
	if(fd == -1)
		error("Error with accept in do_accept()");
	*client_fd = fd;
}

int do_read(const int socket, char buffer[256]) {

}

int do_write(const int socket, const char buffer[256]) {


}

