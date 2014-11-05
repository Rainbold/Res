/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////


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

	/* Setting the socket option so the (address, port) tuple can be used again 
	   right after the connection is closed */
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

int do_read(const int socket, char buffer[], int size)
{
	int n = read(socket, buffer, size);
	
	if( n < 0 )
		error("ERROR with read() in do_read()");

	
	/* If something was read, the last byte is set to a null byte to make sure
	   the received string is correctly formatted */
	if(n > 0)
		buffer[n] = 0;

	return n;
}

int do_write(const int socket, const char buffer[SIZE_BUFFER])
{
	ssize_t n = 0;
	ssize_t rest = strlen(buffer) + 1;

	do {
		n = write(socket, buffer+n, rest);

		if (n < 0 )	error("ERROR with write() in do_write()");
		else if (n == 0) break;

		/* The number of bytes left to send are now rest-n */
		rest -= n;
	} while (rest > 0);

	return n;
}

