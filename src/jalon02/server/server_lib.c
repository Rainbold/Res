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

void send_broadcast_by_user_name(const struct connected_users* users_list, const char buffer[MSG_BUFFER], const char uname_src[USERNAME_LEN]) {
    int i=0;
    char str[SIZE_BUFFER] = "";

    strcpy(str, "/cmsgall ");
    strcat(str, uname_src);
    strcat(str, " ");
    strcat(str, buffer);

    for(i=0; i<CLIENTS_NB; i++)
    {
        // sends a message to all the connected users except to the one who sent it
        if(users_list->users[i].sock != -1 && strcmp(users_list->users[i].username, uname_src) )
            send_msg(users_list->users[i].sock, (char*)users_list->users[i].username, str, "");
        else if( !strcmp(users_list->users[i].username, uname_src) )
            send_msg(users_list->users[i].sock, (char*)users_list->users[i].username, "", "");
    }
}

void send_unicast(const struct connected_users* users_list, const char buffer[MSG_BUFFER], const char *uname_dest,
		const char* uname_src) {
    int i=0;
    char str[SIZE_BUFFER] = "";

    strcpy(str, "/msg ");
    strcat(str, uname_src);
    strcat(str, " ");
    strcat(str, buffer);

    for(i=0; i<CLIENTS_NB; i++)
    {
        // sends a message to all the connected users except to the one who sent it
        if( !strcmp(users_list->users[i].username, uname_dest) )
            send_msg(users_list->users[i].sock, (char*)users_list->users[i].username, str, "");
        else if( !strcmp(users_list->users[i].username, uname_src) )
            send_msg(users_list->users[i].sock, (char*)users_list->users[i].username, "", "");
    }
}

void send_multicast(struct connected_users* users_list, char buffer[SIZE_BUFFER], char *cname, char* uname_src) 
{
    int i=0;
    char str[SIZE_BUFFER] = "";
    int id_chan = find_channel_id(users_list, cname);

    strcpy(str, "/chan ");
    strcat(str, uname_src);
    strcat(str, " ");
    strcat(str, buffer);

    for(i=0; i<CLIENTS_NB; i++)
    {
        // sends a message to all the connected users except to the one who sent it
        if( users_list->users[i].channel == id_chan && strcmp(users_list->users[i].username, uname_src) && users_list->users[i].sock != -1)
            send_msg(users_list->users[i].sock, "", str, "");
        else if( !strcmp(users_list->users[i].username, uname_src) )
            send_msg(users_list->users[i].sock, users_list->users[i].username, "", "");
    }
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
        users_list->users[i].channel = -1;

        users_list->channels[i].id = -1;
        strcpy(users_list->channels[i].name, "");
        users_list->channels[i].nb_users = -1;
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
    struct user_t* user = &(users_list->users[id]);
    char name[USERNAME_LEN];
    char msg[MSG_BUFFER];
    char buffer[SIZE_BUFFER];
    cmd_t cmd;

    pthread_mutex_unlock( &(users_list->mutex) );

    user->t = time(NULL);
    user->tm = *localtime( &(user->t) );

    send_msg(user->sock, "new_client", "[Server] Please logon with /nick <your pseudo>\r\n", ANSI_COLOR_YELLOW);
    
    // Asks for a new username as long as the command entered is invalid
    do {
        do_read(user->sock, buffer, SIZE_BUFFER);
        cmd = regex_match(buffer, name, msg);
        if(cmd == NICK)
            cont = 0;
        else
            send_msg(user->sock, "new_client", "[Server] You have to login using the command /nick <your pseudo>\r\n", ANSI_COLOR_RED);
    } while(cont);

    nick(users_list, name, id);

    sprintf(buffer, "[Server] Welcome to our chat, %s !\r\n", name);
    send_msg(user->sock, name, buffer, ANSI_COLOR_YELLOW);

    cont = 1;
    while(cont)
    {
        memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
        memset(name, 0, sizeof(char)*USERNAME_LEN);
        memset(msg, 0, sizeof(char)*MSG_BUFFER);
        do_read(user->sock, buffer, SIZE_BUFFER);
	printf("raw: %s", buffer);
        cmd = regex_match(buffer, name, msg);

        switch(cmd)
        {
            case NICK:
                nick(users_list, name, id);
                break;
            case MSGALL:
                send_broadcast_by_user_name(users_list, msg, user->username);
                break;
            case MSG:
                send_unicast(users_list, msg, name, user->username);
                break;
            case WHOIS:
                whois(users_list, name, id);
                break;
            case WHO:
                who(users_list, id);
                break;
            case QUIT:
                quit(users_list, id);
                break;
            case CREATE:
                create(users_list, name, id);
                break;
            case JOIN:
                join(users_list, name, id);
                break;
            default:
                if(user->channel == -1)
                    send_msg(user->sock, user->username, "[Server] Invalid command\r\n", ANSI_COLOR_RED);
                else
                    send_multicast(users_list, buffer, users_list->channels[user->channel].name, user->username);
                break;
        }
    }

    return NULL;
}

int find_username_id(struct connected_users* users_list, char* name)
{
    int i=0;

    for(i=0; i<CLIENTS_NB; i++)
        if(!strcmp(users_list->users[i].username, name) )
            return i;

    return -1;
}

int find_channel_id(struct connected_users* users_list, char* name)
{
    int i=0;

    for(i=0; i<CLIENTS_NB; i++)
        if(!strcmp(users_list->channels[i].name, name) )
            return i;

    return -1;
}

void nick(struct connected_users* users_list, char pname[USERNAME_LEN], int id)
{
    int i=0;
    int cont = 1;
    int verif = 1;
    char msg[MSG_BUFFER];
    char buffer[SIZE_BUFFER];
    char name[USERNAME_LEN];
    cmd_t cmd;

    strcpy(name, pname);

    //If the new username is different from the old one
    if( strcmp(name, users_list->users[id].username) )
    {
        do {
            for(i=0; i<CLIENTS_NB; i++)
            {
                if(!strcmp(name, users_list->users[i].username))
                    verif = 0;
            }

            if(!verif)
            {
                if( !strcmp(users_list->users[id].username, "") )
                    strcpy(name, "new_client");
                else
                    strcpy(name, users_list->users[id].username);

                send_msg(users_list->users[id].sock, name, "[Server] This username is already taken. Please use /nick <your pseudo>\r\n", ANSI_COLOR_RED);
                memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
                memset(name, 0, sizeof(char)*USERNAME_LEN);
                do_read(users_list->users[id].sock, buffer, SIZE_BUFFER);
                cmd = regex_match(buffer, name, msg);
                if(cmd != NICK)
                    continue;
                verif = 1;
            }
            else 
            {
                memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
                pthread_mutex_lock( &(users_list->mutex) );
                sprintf(buffer, "/nick %s %s", name, inet_ntoa(users_list->users[id].info.sin_addr));
                send_msg(users_list->users[id].sock, name, buffer, "");
                strcpy(users_list->users[id].username, name);
                pthread_mutex_unlock( &(users_list->mutex) );
                cont = 0;
            }
        } while(cont);

        memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
        sprintf(buffer, "[Server] You changed your username to %s\r\n", name);

        send_msg(users_list->users[id].sock, users_list->users[id].username, "", ANSI_COLOR_YELLOW);
        send_msg(users_list->users[id].sock, users_list->users[id].username, buffer, ANSI_COLOR_YELLOW);
    }
    else
        send_msg(users_list->users[id].sock, users_list->users[id].username, "", ANSI_COLOR_YELLOW);
}

void whois(struct connected_users* users_list, char* name, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );
    int id_target = find_username_id(users_list, name);
    char buffer[SIZE_BUFFER] = "";

    struct tm tm;
    struct sockaddr_in info;

    if(id_target >= 0)
    {
        tm = users_list->users[id_target].tm;
        info = users_list->users[id_target].info;
        sprintf(buffer, "[Server] %s connected since %d/%d/%d@%d:%d:%d from %s:%d\r\n", 
                name, tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, inet_ntoa(info.sin_addr), info.sin_port);
    }
    else
    {
        sprintf(buffer, "[Server] Unknown user : %s\r\n", name);
    }
    
    send_msg(users_list->users[id].sock, users_list->users[id].username, buffer, ANSI_COLOR_YELLOW);
    pthread_mutex_unlock( &(users_list->mutex) );
}

void who(struct connected_users* users_list, int id)
{
    int i=0;
    char buffer[USERNAME_LEN*CLIENTS_NB+100] = "[Server] Online users :\r\n";

    pthread_mutex_lock( &(users_list->mutex) );
    for(i=0; i<CLIENTS_NB; i++)
    {
        if(users_list->users[i].sock != -1)
        {
            strcat(buffer, "\t- ");
            strcat(buffer, users_list->users[i].username);
            strcat(buffer, "\r\n");
        }
    }

    send_msg(users_list->users[id].sock, users_list->users[id].username, buffer, ANSI_COLOR_YELLOW);
    pthread_mutex_unlock( &(users_list->mutex) );
}

void quit(struct connected_users* users_list, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );
    send_msg(users_list->users[id].sock, users_list->users[id].username, "Goodbye.\r\n", ANSI_COLOR_YELLOW);
    close(users_list->users[id].sock);
    users_list->users[id].sock = -1;
    memset( &(users_list->users[id].username), '\0', sizeof(char)*USERNAME_LEN);
    pthread_mutex_unlock( &(users_list->mutex) );
    pthread_cancel(users_list->users[id].thread);
}

void create(struct connected_users* users_list, char* name, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );

    char buffer[SIZE_BUFFER] = "/join ";
    int i=0;

    for(i=0; i<CLIENTS_NB; i++)
    {
        if(users_list->channels[i].id == -1)
        {
            users_list->channels[i].id = i;
            strcpy(users_list->channels[i].name, name);            
            break;
        }
    }

    pthread_mutex_unlock( &(users_list->mutex) );
    join(users_list, name, id);
    pthread_mutex_lock( &(users_list->mutex) );

    strcat(buffer, name);
    send_msg(users_list->users[id].sock, users_list->users[id].username, buffer, "");
    pthread_mutex_unlock( &(users_list->mutex) );
}

void join(struct connected_users* users_list, char* name, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );

    int i=0;
    int id_chan = find_channel_id(users_list, name);

    users_list->users[id].channel = id_chan;
    users_list->channels[id_chan].nb_users++;

    //send_msg(users_list->users[id].sock, users_list->users[id].username, "Welcome\r\n", "");
    send_multicast(users_list, "HE LOGGED IIIIIIN", name, "[Server]");

    pthread_mutex_unlock( &(users_list->mutex) );
}

void send_msg(int sock, char* username, char* msg, char* color)
{
    char buffer[SIZE_BUFFER+10];
    strcpy(buffer, color);
    strcat(buffer, msg);
    strcat(buffer, ANSI_COLOR_RESET);
    strcat(buffer, username);
    strcat(buffer, "> ");
    do_write(sock, buffer);
}

// void command(cmd_t cmd, char* buffer, char* argv, ...)
// {
//     va_list ap;
//     char* arg;

//     va_start(ap, argv);

//     do {
//         printf("%s\n", arg);
//         if( strcpy(arg, va_arg(ap, char*)) == NULL )
//             break;
//     } while(arg != NULL);

//     va_end(ap);
// }
