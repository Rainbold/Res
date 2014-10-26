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
	struct info info;
	char outbuf[SIZE_BUFFER];
	pthread_t thread;

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
	info.running = 1;
    pthread_mutex_init( &(info.mutex), NULL );

	/* Creation of the threads handling the messages */
	pthread_create(&thread, NULL, handle_server_message, &info);

	printf("> ");
	fflush(stdout);

	while(info.running)
		handle_client_message(&info, outbuf);

	close(sock);
	regex_free();
    return 0;
}
