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
    pthread_mutex_init( &(users_list->mutex), NULL );

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
                pthread_mutex_lock( &(users_list->mutex) );
                users_list->current_user = i;
                pthread_create(  &(users_list->users[i].thread), NULL, client_handling, users_list );
                printf("New client : %d\n", i);
            }
        }
    }

    return NULL;
}

void* client_handling(void* p_data)
{
    struct connected_users* users_list = (struct connected_users*) p_data;
    int id = users_list->current_user;
    int cont = 1;
    struct user_t user = users_list->users[id];
    char name[USERNAME_LEN];
    char msg[MSG_BUFFER];
    char buffer[SIZE_BUFFER];
    cmd_t cmd;

    pthread_mutex_unlock( &(users_list->mutex) );

    send_msg(user.sock, "Welcome on our server !\r\n[Server] Please logon with /nick <your pseudo>\r\n", ANSI_COLOR_RED);
    
    // Asks for a new username as long as the command entered is invalid
    do {
        do_read(user.sock, buffer, SIZE_BUFFER);
        cmd = regex_match(buffer, name, msg);
        if(cmd == NICK)
            cont = 0;
        else
            send_msg(user.sock, "[Server] You have to login using the command /nick <your pseudo>\r\n", ANSI_COLOR_YELLOW);
    } while(cont);

    nick(users_list, name, id);
    

    cont = 1;
    while(cont)
    {
        memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
        memset(name, 0, sizeof(char)*USERNAME_LEN);
        memset(msg, 0, sizeof(char)*MSG_BUFFER);
        do_read(user.sock, buffer, SIZE_BUFFER);
        cmd = regex_match(buffer, name, msg);

        switch(cmd)
        {
            case NICK:
                nick(users_list, name, id);
                break;
            case MSGALL:
                send_broadcast_by_user_name(users_list, buffer, user.username);
                break;
        }
    }

    return NULL;
}

void nick(struct connected_users* users_list, char* name, int id)
{
    int i=0;
    int cont = 1;
    int verif = 1;
    char msg[MSG_BUFFER];
    char buffer[SIZE_BUFFER];
    cmd_t cmd;

    do {
        for(i=0; i<CLIENTS_NB; i++)
        {
            if(!strcmp(name, users_list->users[i].username))
                verif = 0;
        }

        if(!verif)
        {
            send_msg(users_list->users[id].sock, "[Server] This username is already taken\r\n[Server] Please logon with /nick <your pseudo>\r\n", ANSI_COLOR_MAGENTA);
            memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
            memset(name, 0, sizeof(char)*USERNAME_LEN);
            do_read(users_list->users[id].sock, buffer, SIZE_BUFFER);
            cmd = regex_match(buffer, name, msg);
            if(cmd != NICK)
            {
                send_msg(users_list->users[id].sock, "This username is already taken, please enter another one : \r\n",ANSI_COLOR_MAGENTA);
                continue;
            }
            verif = 1;
        }
        else 
        {
            pthread_mutex_lock( &(users_list->mutex) );
            strcpy(users_list->users[id].username, name);
            pthread_mutex_unlock( &(users_list->mutex) );
            cont = 0;
        }
    } while(cont);
}

void send_msg(int sock, char* msg, char* color)
{
    char buffer[SIZE_BUFFER+10];
    strcpy(buffer, color);
    strcat(buffer, msg);
    strcat(buffer, ANSI_COLOR_RESET);
    do_write(sock, buffer);
}
