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
	struct pollfd fds;
    int ret;

	memset(outbuf, 0, SIZE_BUFFER);
    
    fds.fd = 0;
    fds.events = POLLIN;

    /* Checks if there is data waiting in stdin */
    ret = poll(&fds, 1, 1);
    
    /* if there is, fgets is executed */
    if(ret == 1)
    {
		fgets(outbuf, SIZE_BUFFER, stdin);

		if(pinfo->req == 1)
		{
			write(pinfo->fd[1], outbuf, strlen(outbuf));
			pinfo->req = 0;
		}
		else
		{
			if(strlen(outbuf) > 1)
				do_write(pinfo->sock, outbuf);
		}
	}
}

/* Thread handling the reading */
void* handle_server_message(void* info)
{
	struct info* pinfo = info;
	struct data data;
	int len = 1;
	cmd_t cmd;
	pthread_t p2p;

	char buf[50];

	char inbuf[READ_BUFFER];
	char userorchannel[USERNAME_LEN];
	char message[MSG_BUFFER];
	char filename[MSG_BUFFER];

	char ip[16];

	memset(buf, 0, 50);

	memset(inbuf, 			0, READ_BUFFER);
	memset(userorchannel,	0, USERNAME_LEN);
	memset(message,			0, MSG_BUFFER);
	memset(filename,		0, MSG_BUFFER);

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
			case QUITCHANNEL:
				memset(pinfo->channel, 0, USERNAME_LEN*sizeof(char));
				break;
			case MSG:
				colour(COLOR_PM);
				printf("[%s] : %s", userorchannel, message);
				colour(0);
				break;
			case CMSGALL:
				colour(COLOR_ALL);
				printf("[%s] : %s", userorchannel, message);
				colour(0);
				break;
			case JOIN:
				memset(pinfo->channel, 0, USERNAME_LEN);
				memcpy(pinfo->channel, userorchannel, strlen(userorchannel));
				break;
			case CHAN:
				colour(COLOR_CHANNEL);
				printf("%s> : %s", userorchannel, message);
				colour(0);
				break;
			case MSGCHANNEL: /* message from server */
				printf("%s", inbuf);
				break;
			case SEND:
				pinfo->req = 1;
				message[strlen(message)-1] = 0;
				regex_get_filename(message, filename);
				printf("%s wants you to accept the transfer of the file named \"%s\". Do you accept? Press enter and then [y/n]\n> ", userorchannel, filename);
				fflush(stdout);
				read(pinfo->fd[0], buf, 50);
				if(buf[0] == 'y')
				{
					memset(pinfo->filename, 0, MSG_BUFFER);
					memcpy(pinfo->filename, filename, strlen(filename));
					pthread_create(&p2p, NULL, handle_file_receive, pinfo);
					memset(buf, 0, 50);
					sprintf(buf, "/filere %s %s %d %s\n", userorchannel, ip, ++(pinfo->port), message);
					do_write(pinfo->sock, buf);
				}
				else
				{
					printf("Abort\n");
					memset(buf, 0, 50);
					sprintf(buf, "/filere %s\n", userorchannel);
					do_write(pinfo->sock, buf);
				}
				break;
			case FILERE:
				if(strlen(message) >= 2)
				{
					printf("Sending file to %s\n", userorchannel);
					memset(pinfo->inbuf, 0, READ_BUFFER);
					strcpy(pinfo->inbuf, message);
					pthread_create(&p2p, NULL, handle_send_file, pinfo);
				}
				else
					printf("> %s cancelled file transfer\n", userorchannel);
				break;

			default:
				printf("\nUnknown command: %s\n", inbuf);
				break;
		}

		if(strlen(pinfo->channel) != 0)
		{
			if(cmd == JOIN)
				printf("\n");

			printf("%s@", pinfo->username);
			colour(COLOR_CHANNEL);
			printf("%s", pinfo->channel);
			colour(0);
			printf("> ");
		}
		else if(strlen(pinfo->username) != 0)
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

	/* The running variable is set to 0 in order to terminate the loop used in the main thread */	
    pthread_mutex_lock( &(pinfo->mutex) );
	pinfo->running = 0;
    pthread_mutex_unlock( &(pinfo->mutex) );

	return NULL;
}

void* handle_file_receive(void* pdata)
{
	struct info* pinfo = pdata;
	int sock, client, addrlen, r;
	struct sockaddr_in server_info;
	struct sockaddr_in client_addr;
	char port[6];
	char bufin[RW_BUFFER];
	FILE* file;

	memset(bufin, 0, RW_BUFFER);
	sprintf(bufin, "./inbox/%s", pinfo->filename);
	file = fopen(bufin, "wb+");
	memset(bufin, 0, RW_BUFFER);

	memset(port, 0, 6);
	sprintf(port, "%d", pinfo->port);

	if(file == NULL)
	{
		printf("Error with fopen in handle_file_receive - directory inbox does not exist\n");
		file = fopen("./RE216_pwd", "wb+");
		if(file != NULL) fclose(file);
		return NULL;
	}

	// Create a server
	sock = do_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	init_serv_addr(port, &server_info);
	do_bind(sock, &server_info);
	listen(sock, 1);
	client = accept(sock, (struct sockaddr*)&client_addr, &addrlen);
	int a = 0;
	do {
		r = read(client, bufin, 1024);
		a = fwrite(bufin, 1, r, file);
	} while(r != 0);

	fclose(file);
	printf("\n> File received\n> ");
	fflush(stdout);
	close(client);
	close(sock);
}

// Thread which handle the sending of a file
void* handle_send_file(void* pdata)
{
	int sock;
	struct sockaddr_in serv_info;
	char ip[16];
	char port[6];
	char filepath[MSG_BUFFER];
	int c;
	FILE* file;
	char bufout[RW_BUFFER];
	struct info* pinfo = pdata;
	ssize_t r,n,t;

	regex_get_filere(pinfo->inbuf, ip, port, filepath);
	printf("%s\n", ip);
	printf("%s\n", port);
	printf("%s\n", filepath);

	// todo erno
	file = fopen(filepath, "rb");

	if(file == NULL)
	{
		printf("\n> Error : file does not exist\n> ");
		fflush(stdout);
		return NULL;
	}
	get_addr_info(&serv_info, ip, port);
	sock = do_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	c = connect(sock, (struct sockaddr*)&serv_info, sizeof(serv_info));

	if(c != 0)
	{
		printf("\n> Cannot connect to client\n> ");
		fflush(stdout);
		fclose(file);
		close(sock);
		return NULL;
	}

	// Send the file
	do {
		t = fread(bufout, 1, RW_BUFFER, file);
		r = t;
		do {
			n = write(sock, bufout, r);
			if (n < 0 )	error("ERROR with write() in do_write()");
			r -= n;
		} while (r > 0);
	} while(t == RW_BUFFER);

	printf("\n> File transfered.\n> ");
	fflush(stdout);

	fclose(file);
	close(sock);
}
