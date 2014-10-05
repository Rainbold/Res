#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define STRLEN 512

int get_addr_info(struct sockaddr_in* serv_info, char* host, char* port);
int do_socket();
void do_connect(int sock, struct sockaddr_in *serv_info);
void readline(char* buf);
void handle_client_message(int sock, char* buffer);
ssize_t readline(int fd, void *str, size_t maxlen);
ssize_t sendline(int fd, const void *str, size_t maxlen);

int main(int argc,char** argv)
{
	int sock = 0;
	struct sockaddr_in serv_info;
	char buf[STRLEN];

    if (argc != 3)
    {
        fprintf(stderr,"usage: RE216_CLIENT hostname port\n");
        return 1;
    }

   	get_addr_info(&serv_info, argv[1], argv[2]);
	sock = do_socket();

	do_connect(sock, &serv_info);

	while( strncmp("/quit", buf, 5) != 0 )
	{
		readline(buf);
		handle_client_message(sock, buf);
	}

	close(sock);

    return 0;
}

/* get_addr_info fills the sockaddr_in structure with information such as the server's ip address, the server's port, etc... */
int get_addr_info(struct sockaddr_in* serv_info, char* host, char* port)
{
	//struct hostent* h = gethostbyname(host);
	struct addrinfo *res, hint;
	struct sockaddr_in *addr;

	memset(&hint, 0, sizeof(struct addrinfo));

	/* getaddrinfo returns 0 on success */
	if( getaddrinfo(host, port, &hint, &res) )
    {
    	perror("getaddrinfo");
    	exit(errno);
    }

    memset(serv_info, 0, sizeof(*serv_info));
    	serv_info->sin_family = AF_INET;
    	serv_info->sin_port =  htons(atoi(port));

    addr = (struct sockaddr_in *)res->ai_addr; 
    serv_info->sin_addr = addr->sin_addr;

    return 0;
}

/* do_socket create the socket used throughout the application */
int do_socket()
{
	int sock;

	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

	return sock;
}

/* do_connect connects to the remote or local server based on the data stored in serv_info */
void do_connect(int sock, struct sockaddr_in *serv_info)
{
	if( connect(sock, (struct sockaddr*)serv_info, sizeof(*serv_info)) != 0 )
	{
		perror("Connect");
		exit(errno);
	}
}

/* handle_client_message stores the user input into buffer buf while protecting the application from a buffer overflow
   and sends the message contained into the buffer buf to the server */
void handle_client_message(int sock, char* buffer)
{
	int n = 0;
	char f[20]; 

	memset(buffer, 0, STRLEN);
	printf("> ");
	fgets(buffer, STRLEN, stdin);

	sendline(sock, buffer, strlen(buffer));
	readline(sock, buffer, strlen(buffer));

	printf("Server ECHO : %s\n", buffer);
}

ssize_t readline(int sock, void *buffer, size_t maxlen)
{
	ssize_t n = read(sock, buffer, maxlen);
	
	if( n < 0 )
	{
		perror("Read");
		exit(errno);
	}
	else if( n == 0 )
	{
		perror("Server dead");
		close(sock);
		exit(errno);
	}

	return n;
}

ssize_t sendline(int fd, const void *buffer, size_t maxlen)
{
	ssize_t n;
	if( (n = write(sock, buffer, maxlen)) < 0 )
	{
		perror("Write");
		exit(errno);
	}

	return n;
}