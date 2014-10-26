#include "client.h"
#include <netdb.h>
#include <errno.h>


/* get_addr_info fills the sockaddr_in structure with information such as the server's ip address, the server's port, etc... */
int get_addr_info(struct sockaddr_in* serv_info, char* host, char* port)
{
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
		
		if(strlen(outbuf) > 1)
			do_write(pinfo->sock, outbuf);
		fflush(stdout);
    }    
}

/* Thread handling the reading */
void* handle_server_message(void* info)
{
	struct info* pinfo = info;
	int len = 1;

	char buf[50];
	char inbuf[READ_BUFFER];
	char ip[16];

	memset(buf, 0, 50);
	memset(inbuf, 0, READ_BUFFER);
	memset(ip, 0, 16);

	while(1)
	{
		len = do_read(pinfo->sock, inbuf, READ_BUFFER);
		if(len == 0) break;

		printf("%s", inbuf);

		fflush(stdout);
		memset(inbuf, 0, len);
	}
	
	close(pinfo->sock);

	/* The running variable is set to 0 in order to terminate the loop used in the main thread */
	
    pthread_mutex_lock( &(pinfo->mutex) );
	pinfo->running = 0;
    pthread_mutex_unlock( &(pinfo->mutex) );
	
	return NULL;
}
