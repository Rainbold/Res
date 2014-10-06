#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE_BUFFER 1000

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int do_socket();
void init_serv_addr(struct sockaddr_in* pt_server_info, int port);
void do_bind(int sock, struct sockaddr_in* adr);
int do_accept(int sock, struct sockaddr* pt_client_info, socklen_t* pt_client_info_size);
ssize_t do_read(int client, char* buf);
void do_write(int client, char* buf);
ssize_t readline (int fd, void *str, size_t maxlen);
ssize_t sendline (int fd, const void *str, size_t maxlen);

int main(int argc, char** argv)
{
	int sock;
	int client;
	struct sockaddr_in server_info;
	struct sockaddr_in client_info;
	socklen_t client_info_len;
	char buf[SIZE_BUFFER];
	int len;
	int i;

    if (argc != 2)
    {
        fprintf(stderr, "usage: RE216_SERVER port\n");
        return 1;
    }

    //create the socket with check for validity
    sock = do_socket();

    //init the serv_add structure
    init_serv_addr(&server_info, atoi(argv[1]));

    //perform the binding
    //we bind on the tcp port specified
    do_bind(sock, &server_info);

    //specify the socket to be a server socket and listen for at most 20 concurrent client
    listen(sock, 20);

    printf("Server running and listening on port %s\n", argv[1]);

    for (;;)
    {
        //accept connection from client
        client = do_accept(sock, (struct sockaddr*) &client_info, &client_info_len);

        printf("New client : %s\n", inet_ntoa(client_info.sin_addr));

        while(1) {
        	//read what the client has to say
        	len = do_read(client, buf);
        	printf("%s\n", buf);

        	if(len == -1)
        		error("Error: len == -1");

        	// if len == 0, it means that the connection has been closed
        	if(len == 0)
        		break;

      		//we write back to the client
      		do_write(client, buf);

      		if(!strncmp("/quit", buf, 5))
      			break;

      		// buffer reset
      		memset(buf, 0, len);
        }

        //clean up client socket
        close(client);

        printf("Connection closed.\n");
    }

    //clean up server socket
    close(sock);

    return 0;
}

int do_socket() {
	int yes = 1;
	int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd == -1) {
		error("Error with socket() in do_socket()");
	}
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		error("ERROR setting socket options");
	return fd;
}

void init_serv_addr(struct sockaddr_in* pt_server_info, int port) {
	memset(pt_server_info, 0, sizeof(*pt_server_info));
	pt_server_info->sin_family = AF_INET;
	pt_server_info->sin_port = htons(port);
	pt_server_info->sin_addr.s_addr = INADDR_ANY;
}

void do_bind(int sock, struct sockaddr_in* adr) {
	if( bind(sock, (struct sockaddr*) adr, sizeof(*adr)) == -1 )
		error("Error with bind() in do_bind()");
}

int do_accept(int sock, struct sockaddr* pt_client_info, socklen_t* pt_client_info_size) {
	int fd = accept(sock, pt_client_info, pt_client_info_size);
	if(fd == -1)
		error("Error with accept in do_accept()");
	return fd;
}

ssize_t do_read(int client, char* buf) {
	ssize_t size = readline(client, buf, SIZE_BUFFER);
	// makes sure that the last char is \0
	buf[size] = '\0';
	return size;
}

void do_write(int client, char* buf) {
	sendline(client, buf, strlen(buf));
}

ssize_t readline (int fd, void *str, size_t maxlen) {
	return read(fd, str, maxlen);
}
ssize_t sendline (int fd, const void *str, size_t maxlen) {
	return write(fd, str, maxlen);
}
