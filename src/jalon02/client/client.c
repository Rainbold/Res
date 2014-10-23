/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

#include "client.h"

int main(int argc,char** argv)
{
	int sock = 0;
	struct sockaddr_in serv_info;
	pthread_t thread;
	struct info info;
	char outbuf[SIZE_BUFFER];

	regex_init();

    if (argc != 3)
    {
        fprintf(stderr,"usage: RE216_CLIENT hostname port\n");
        return 1;
    }

   	get_addr_info(&serv_info, argv[1], argv[2]);
	sock = do_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	do_connect(sock, &serv_info, sizeof(serv_info));

	info.sock = sock;
	info.port = atoi(argv[2]);
	memset(info.username, 0, USERNAME_LEN);
	memset(info.channel, 0, USERNAME_LEN);
	info.req = 0;
	pipe(info.fd);

	pthread_create(&thread, NULL, handle_server_message, &info);

	printf("> ");
	fflush(stdout);

	while( strcmp("/quit\n", outbuf) != 0)
		handle_client_message(&info, outbuf);

	close(sock);
	regex_free();
	//freeaddrinfo((struct addrinfo*) &serv_info);
    return 0;
}
