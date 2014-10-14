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

	char outbuf[SIZE_BUFFER];

    if (argc != 3)
    {
        fprintf(stderr,"usage: RE216_CLIENT hostname port\n");
        return 1;
    }

   	get_addr_info(&serv_info, argv[1], argv[2]);
	sock = do_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	do_connect(sock, &serv_info, sizeof(serv_info));

	pthread_create(&thread, NULL, handle_server_message, &sock);

	while( strncmp("/quit", outbuf, 5) != 0 )
	{
		handle_client_message(sock, outbuf);
	}

	close(sock);

    return 0;
}
