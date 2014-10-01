#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define STRLEN 512

int get_addr_info(struct sockaddr_in* serv_info, char* host, char* port);
int do_socket();
void do_connect(int sock, struct sockaddr_in *serv_info);
void readline(char* buf);
void handle_client_message(int sock, char* buffer);

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
	struct hostent* h = gethostbyname(host);

    memset(serv_info, 0, sizeof(*serv_info));
    	serv_info->sin_family = AF_INET;
    	serv_info->sin_port =  htons(atoi(port));

    if (inet_aton(host, serv_info->sin_addr) != 1)
    {
    	perror("inet_aton");
    	exit(errno);
    }

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

/* readline stores the user input into buffer buf while protecting the application from a buffer overflow */
void readline(char* buf)
{
	char f[20]; 

	memset(buf, 0, STRLEN);
	printf("> ");
	fgets(buf, STRLEN, stdin);
}

/* handle_client_message sends the message contained into the buffer buf to the server */
void handle_client_message(int sock, char* buffer)
{
	int n = 0;

	if( write(sock, buffer, strlen(buffer)) < 0 )
	{
		perror("Write");
		exit(errno);
	}
}