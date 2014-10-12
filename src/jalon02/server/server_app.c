/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

#include "server.h"


int main(int argc, char** argv) {

	int sock;
    pthread_t t_accept_conn;
	struct sockaddr_in server_info;

	if (argc != 2) {
		fprintf(stderr, "Please specify a local port to bind to\n");
		exit(-1);
	}

	//init a fresh socket
    sock = do_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
	//init server address structure
	init_serv_addr(argv[1], &server_info);

	//perform the binding
	do_bind(sock, &server_info);

	//specify the socket to be a server socket and listen for at most 20 concurrent client
	listen(sock, CLIENTS_NB);

	//init the fdset

	printf("Server listening on port %s\n", argv[1]);

	//creation of the threads accepting the connections


	while(1) {

	}

	// Clean up each threads
		// send broadcast : "[Server] Server is shutting down\n"
		// kill all threads
		// close all client socket

	// Clean up server socket
	close(sock);

	// Clean up memory
		// free...

	printf("Good bye.\n");
	return 0;
}
