/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

#include "server.h"


int handle_server_socket_event(const int server_socket_fd) {

}

void handle_client_socket_event(int client_socket_fd) {

}

void send_broadcast_by_fd(const char buffer[SIZE_BUFFER], const int fd) {

}

void send_broadcast_by_user_name(const struct connected_users* users_list, const char buffer[SIZE_BUFFER], const char* uname_src) {
    int i=0;
    char str[SIZE_BUFFER+50];
    strcpy(str, uname_src);
    strcat(str, " ");
    strcat(str, buffer);

    for(i=0; i<CLIENTS_NB; i++)
    {
        if(users_list->users[i].sock != -1)
        {
            do_write(users_list->users[i].sock, str);
        }
    }
}

void send_unicast(const char buffer[SIZE_BUFFER], const char *uname_dest,
		const char* uname_src) {

}

void send_multicast(const char buffer[SIZE_BUFFER], const char **unames,
		const char* uname_src) {

}

void process_client_request(const char buffer[SIZE_BUFFER], const int client_socket_fd) {

}

void init_users(int sock, struct connected_users* users_list) {
    int i=0;

    users_list->current_user = -1;
    users_list->sock_serv = sock;
    pthread_mutex_init( &(users_list->sock_serv), NULL );

    for (i=0; i<CLIENTS_NB; i++)
    {
        users_list->users[i].sock = -1;
        strcpy(users_list->users[i].username, "");
        memset(&(users_list->users[i].info), 0, sizeof(struct sockaddr_in));
        users_list->users[i].info_len = sizeof(struct sockaddr_in);
        users_list->users[i].connection_time = 0;
        users_list->users[i].timer = 0;
    }
}

void* server_accepting(void* p_data)
{
    struct connected_users* users_list = p_data;
    int i = 0;

    for (;;)
    {
        //accept connection from client
        for(i=0; i<CLIENTS_NB; i++)
        {
            //looks for an empty spot in the array to store the connection data
            if(users_list->users[i].sock == -1)
            {
                do_accept(users_list->sock_serv, &(users_list->users[i].sock), &(users_list->users[i].info), users_list->users[i].info_len );
                pthread_create(  &(users_list->users[i].thread), NULL, client_handling, &(users_list->users[i]) );
                printf("New client : %d\n", i);
            }
        }
    }

    return NULL;
}

void* client_handling(void* p_data)
{
    struct user_t* user = (struct user_t*) p_data;
    char username[USERNAME_LEN];

    do_write(user->sock, "Welcome on our server !\r\n Please enter your nickname (30 alphanumeric characters max) : \r\n> ");
    do_read(user->sock, username, USERNAME_LEN);
    printf("%s just went online\n", username);

    return NULL;
}

int username_exists(struct user_t* users_list, )
{
    struct user_t* user = (struct user_t*) p_data;
    char username[USERNAME_LEN];

    do_write(user->sock, "Welcome on our server !\r\n Please enter your nickname (30 alphanumeric characters max) : \r\n> ");
    do_read(user->sock, username, USERNAME_LEN);
    printf("%s just went online\n", username);

    return NULL;
}
