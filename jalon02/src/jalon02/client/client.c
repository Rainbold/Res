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
	info.running = 1;

	/* Creation of the threads handling the messages */
	pthread_create(&thread, NULL, handle_server_message, &info);

	fflush(stdout);

	while( strcmp("/quit\n", outbuf) != 0 && info.running)
		handle_client_message(&info, outbuf);

	close(sock);
    return 0;
}
