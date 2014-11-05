/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

#include "server.h"

int main(int argc, char** argv) {

	int sock, ret, i;
	int cont = 1;
    pthread_t t_accept_conn;
    char command_buffer[SIZE_BUFFER];
	struct sockaddr_in server_info;
	struct connected_users users_list;

	if (argc != 2) {
		fprintf(stderr, "Please specify a local port to bind to\n");
		exit(-1);
	}


	//init a fresh socket
    sock = do_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
	//init server address structure
	init_serv_addr(argv[1], &server_info);
		
	//init users list structure
	init_users(sock, &users_list);

	//perform the binding
	do_bind(sock, &server_info);

	//specify the socket to be a server socket and listen for at most 20 concurrent client
	listen(sock, CLIENTS_NB);

	printf("Server listening on port %s\n", argv[1]);

	//creation of the threads accepting the connections
	ret = pthread_create(&t_accept_conn, NULL, server_accepting, &users_list);

	while(cont) {
		memset(command_buffer, 0, SIZE_BUFFER);
		printf("> ");
		fgets(command_buffer, SIZE_BUFFER, stdin);

		if( !strncmp(command_buffer, "/quit", 5) )
			cont = 0;
	}

	// close all the clients' associated sockets and threads
	for(i=0; i<CLIENTS_NB; i++)
        if(users_list.users[i].sock > -1)
        	quit(&users_list, i);

	// Clean up server socket
	close(sock);

	printf("Good bye.\n");
	return 0;
}
