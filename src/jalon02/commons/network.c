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

void do_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {


}

void init_serv_addr(const char* port, struct sockaddr_in *serv_addr) {
	memset(pt_server_info, 0, sizeof(*pt_server_info));
	pt_server_info->sin_family = AF_INET;
	pt_server_info->sin_port = htons(atoi(port));
	pt_server_info->sin_addr.s_addr = INADDR_ANY;
}

void do_bind(const int fd, struct sockaddr_in *serv_addr) {

}

void do_accept(const int server_fd, int *client_fd,
		struct sockaddr * client_addr) {



}

int do_read(const int socket, char buffer[256]) {

}

int do_write(const int socket, const char buffer[256]) {


}

