#include "client.h"
#include <netdb.h>
#include <errno.h>


/* get_addr_info fills the sockaddr_in structure with information such as the server's ip address, the server's port, etc... */
int get_addr_info(struct sockaddr_in* serv_info, char* host, char* port)
{
	//struct hostent* h = gethostbyname(host);
	struct addrinfo* res;
	struct addrinfo hint;
	struct sockaddr_in *addr;

	memset(&hint, 0, sizeof(hint));

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

/* handle_client_message stores the user input into buffer buf while protecting the application from a buffer overflow
   and sends the message contained into the buffer buf to the server */
void handle_client_message(int sock, char outbuf[SIZE_BUFFER])
{
	memset(outbuf, 0, SIZE_BUFFER);
	printf("> ");
	fgets(outbuf, SIZE_BUFFER, stdin);

	do_write(sock, outbuf);
}

// Thread which handle the reading
void* handle_server_message(void* psock)
{
	int sock = *((int*) psock);
	char inbuf[READ_BUFFER];
	char userorchannel[USERNAME_LEN];
	char message[MSG_BUFFER];
	int len = 1;
	cmd_t cmd;

	memset(inbuf, 0, READ_BUFFER);
	regex_init();

	while(1)
	{
		len = do_read(sock, inbuf, READ_BUFFER);

		if(len == 0) break;

		cmd = regex_match(inbuf, userorchannel, message);

		switch(cmd)
		{
		case MSG:
			colour(COLOR_PM);
			printf("[%s] : %s", userorchannel, message);
			colour(0);
			break;
		case MSGCHANNEL: // message from server
			colour(COLOR_SERVER);
			printf("%s", message);
			colour(0);
			break;
		case MSGALL:
			colour(COLOR_ALL);
			printf("[%s] : %s", userorchannel, message);
			colour(0);
			break;
		default:
			printf("case default\n");
			break;
		}
		printf("> ");

		memset(inbuf, 0, len);
	}

	regex_free();
	pthread_exit(NULL);
	return NULL;
}

void handle_file_decline(const char* addr, const char* port) {

}
void handle_file_receive(const char *file_name, const char* addr,
		const char* port) {

}

void handle_send_file(const int socket, const char* file_path) {

}
