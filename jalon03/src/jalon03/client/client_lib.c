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

	/* getaddrinfo will fill the res structure with information about the
	   server based on its hostname
	   it returns 0 on success */
	if( getaddrinfo(host, port, &hint, &res) )
    {
    	perror("getaddrinfo");
    	exit(errno);
    }

    memset(serv_info, 0, sizeof(*serv_info));
    	serv_info->sin_family = AF_INET;
    	serv_info->sin_port =  htons(atoi(port));

    /* These information are then stored into the addr structure*/
    addr = (struct sockaddr_in *)res->ai_addr;

    /* The server's IP address is stored into the serv_info structure */
    serv_info->sin_addr = addr->sin_addr;

    /* res is freed */
    freeaddrinfo(res);

    return 0;
}

/* handle_client_message stores the user input into buffer buf while protecting the application from a buffer overflow
   and sends the message contained into the buffer buf to the server */
void handle_client_message(struct info* pinfo, char outbuf[SIZE_BUFFER])
{
	memset(outbuf, 0, SIZE_BUFFER);

	fgets(outbuf, SIZE_BUFFER, stdin);

	if( strcmp("/quit\n", outbuf) )
	{
		if(strlen(outbuf) > 1)
			do_write(pinfo->sock, outbuf);

		/* If the user is connected */
		if(strlen(pinfo->username) != 0)
		{
			colour(0);
			printf("%s> ", pinfo->username);
		}
		else
		{
			colour(0);
			printf("> ");
		}
		fflush(stdout);
	}
}

/* Thread handling the reading */
void* handle_server_message(void* info)
{
	struct info* pinfo = info;
	int len = 1;
	cmd_t cmd;
	pthread_t p2p;

	char buf[50];

	char inbuf[READ_BUFFER];
	char userorchannel[USERNAME_LEN];
	char message[MSG_BUFFER];

	char ip[16];

	memset(buf, 0, 50);

	memset(inbuf, 			0, READ_BUFFER);
	memset(userorchannel,	0, USERNAME_LEN);
	memset(message,	0, MSG_BUFFER);

	memset(ip,				0, 16);

	while(1)
	{
		len = do_read(pinfo->sock, inbuf, READ_BUFFER);
		if(len == 0) break;

		cmd = regex_match(inbuf, userorchannel, message);

		switch(cmd)
		{
			case NICK:
				memset(pinfo->username, 0, USERNAME_LEN);
				memset(ip, 0, 16);
				memcpy(pinfo->username, userorchannel, strlen(userorchannel));
				strcpy(ip, message);
				printf("Change of username\n");
				break;
			case MSGCHANNEL: /* message from server */
				printf("%s", inbuf);
				break;
			default:
				printf("\nUnknown command: %s\n", inbuf);
				break;
		}

		if(strlen(pinfo->username) != 0)
		{
			colour(0);
			printf("%s> ", pinfo->username);
		}
		else
		{
			colour(0);
			printf("> ");
		}

		fflush(stdout);
		memset(inbuf, 0, len);
	}
	
	regex_free();
	close(pinfo->sock);

	/* When the thread terminates, a signal is sent to the main processus
	   to terminate it too. That's because the latter is likely to be waiting for
	   a user input. */
	kill(getpid(), 15);

	return NULL;
}
