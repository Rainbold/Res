/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

#include "server.h"

/* send_broadcast_by_user_name sends a message to all the users */
void send_broadcast_by_user_name(const struct connected_users* users_list, const char buffer[MSG_BUFFER], const char uname_src[USERNAME_LEN]) {
    int i=0;
    char str[SIZE_BUFFER] = "";

    /* /cmsgall username_source msg */
    sprintf(str, "/cmsgall %s %s", uname_src, buffer);

    for(i=0; i<CLIENTS_NB; i++)
    {
        /* sends a message to all the connected users except to the one who sent it */
        if(users_list->users[i].sock > -1 && strcmp(users_list->users[i].username, uname_src) )
            send_msg(users_list->users[i].sock, str, "");
        if(users_list->users[i].sock > -1 && !strcmp(users_list->users[i].username, uname_src) )
            send_msg(users_list->users[i].sock, "", "");
    }
}

/* send_unicast sends a message to a specific user */
void send_unicast(const struct connected_users* users_list, const char buffer[MSG_BUFFER], const char *uname_dest,
        const char* uname_src) {
    int i=0;
    char str[SIZE_BUFFER] = "";

    /* /msg username_source msg */
    sprintf(str, "/msg %s %s", uname_src, buffer);

    if( strcmp(uname_src, uname_dest) )
        for(i=0; i<CLIENTS_NB; i++)
        {
            if( !strcmp(users_list->users[i].username, uname_dest) )
                send_msg(users_list->users[i].sock, str, "");
            if( !strcmp(users_list->users[i].username, uname_src) )
                send_msg(users_list->users[i].sock, "", "");
        }
    else
        send_msg(users_list->users[find_username_id((struct connected_users*)users_list, (char*)uname_src)].sock, "", "");
}

/* send_multicast sends a message to all the users connected to the channel cname */
void send_multicast(struct connected_users* users_list, char buffer[SIZE_BUFFER], char *cname, char* uname_src) 
{
    int i=0;
    char str[SIZE_BUFFER] = "";
    int id_chan = find_channel_id(users_list, cname);

    /* /chan username_source msg */
    sprintf(str, "/chan %s %s", uname_src, buffer);

    for(i=0; i<CLIENTS_NB; i++)
    {
        /* sends a message to all the connected users except to the one who sent it */
        if( users_list->users[i].channel == id_chan && strcmp(users_list->users[i].username, uname_src) && users_list->users[i].sock > -1)
            send_msg(users_list->users[i].sock, str, "");
        if( users_list->users[i].sock > -1 && !strcmp(users_list->users[i].username, uname_src) )
            send_msg(users_list->users[i].sock, "", "");
    }
}

/* init_users will initialize the whole connected_users structure called users_list */
void init_users(int sock, struct connected_users* users_list) {
    int i=0;

    users_list->current_user = -1;
    users_list->sock_serv = sock;
    users_list->nb_users = 1;
    pthread_mutex_init( &(users_list->mutex), NULL );

    for (i=1; i<CLIENTS_NB; i++)
    {
        users_list->users[i].sock = -1;
        strcpy(users_list->users[i].username, "");
        memset(&(users_list->users[i].info), 0, sizeof(struct sockaddr_in));
        users_list->users[i].info_len = sizeof(struct sockaddr_in);
        users_list->users[i].channel = -1;

        users_list->channels[i].id = -1;
        strcpy(users_list->channels[i].name, "");
        users_list->channels[i].nb_users = 0;
    }

    /* The server counts as an user to prevent other users to use [Server] as their name */
    users_list->users[0].sock = -2;
    strcpy(users_list->users[0].username, "[Server]");
}

/* server_accepting is called and executed by a thread. Its main purpose is to accept connection
   and to call a thread handling the connection and management of this particular user */
void* server_accepting(void* p_data)
{
    struct connected_users* users_list = p_data;
    int i = 0;

    for (;;)
    {
        /* accepts connection from client */
        for(i=0; i<CLIENTS_NB; i++)
        {
            /* looks for an empty spot in the array to store the connection data */
            if(users_list->users[i].sock == -1)
            {
                pthread_mutex_lock( &(users_list->mutex) );
                users_list->nb_users++;
                pthread_mutex_unlock( &(users_list->mutex) );
                
                do_accept(users_list->sock_serv, &(users_list->users[i].sock), &(users_list->users[i].info), users_list->users[i].info_len );
                
                if(users_list->nb_users >= CLIENTS_NB)
                {
                    pthread_mutex_lock( &(users_list->mutex) );
                    users_list->nb_users--;
                    pthread_mutex_unlock( &(users_list->mutex) );
            
                    do_write(users_list->users[i].sock, "[Server] There are too many users connected at the moment, please try again later.\r\n");
                    close(users_list->users[i].sock);
                    users_list->users[i].sock = -1;
                }
                else
                {
                    /* The mutex on users_list is locked to prevent another connection to change the current_user variable.
                       This mutex will be unlocked in the function client_handling. */
                    pthread_mutex_lock( &(users_list->mutex) );
                    users_list->current_user = i;
                    pthread_create(  &(users_list->users[i].thread), NULL, client_handling, users_list );
                }
            }
        }
    }
}

/* client_handling is called and executed by a thread. This function is in charge of handling the different
   user inputs and to respond accordingly. */
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

    /* The aformentionned mutex lock in the server_accepting function is unlocked here */
    pthread_mutex_unlock( &(users_list->mutex) );

    user->t = time(NULL);
    user->tm = *localtime( &(user->t) );

    send_msg(user->sock, "[Server] Please logon with /nick <your pseudo>\r\n", ANSI_COLOR_YELLOW);
    
    /* Asks for a new username as long as the command entered is not a valid /nick command */
    do {
        /* If the connection ends, the user is disconnected and its socket and thread closed */
        if( do_read(user->sock, buffer, SIZE_BUFFER) == 0 )
            quit(users_list, id);

        cmd = regex_match(buffer, name, msg);

        if(cmd == NICK)
        {
            /* The new username will be stored into the users_list structure */
            nick(users_list, name, id);
            
            /* If the command is a valid /nick then the users is considered as connected to the server
               and can now issue commands */
            if(strcmp(user->username, ""))
                cont = 0;
        }
        else
            send_msg(user->sock, "[Server] You have to login using the command /nick <your pseudo>\r\n", ANSI_COLOR_RED);
    } while(cont);

    sprintf(buffer, "[Server] Welcome to our chat, %s !\r\n", name);
    send_msg(user->sock, buffer, ANSI_COLOR_YELLOW);

    cont = 1;
    while(cont)
    {
        /* Initialization of different variables */
        memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
        memset(name, 0, sizeof(char)*USERNAME_LEN);
        memset(msg, 0, sizeof(char)*MSG_BUFFER);

        if(do_read(user->sock, buffer, SIZE_BUFFER) != 0)
        {
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
                case CREATE:
                    create(users_list, name, id);
                    break;
                case JOIN:
                    join(users_list, name, id);
                    break;
                case SEND:
                    send_file(users_list, name, msg, id);
                    break;
                case FILERE:
                    sprintf(buffer, "/filere %s %s", user->username, msg);
                    printf("%s\n", buffer);
                    do_write(users_list->users[find_username_id(users_list, name)].sock, buffer);
                    break;
                case QUITCHANNEL:
                    quit_chan(users_list, name, id);
                    break;
                case QUIT:
                    quit(users_list, id);
                    break;
                default:
                    /* If the user is not connected to the channel, if a the text entered is not a valid command,
                       an error message is sent */
                    if(user->channel == -1)
                        send_msg(user->sock, "[Server] Invalid command\r\n", ANSI_COLOR_RED);
                    /* Otherwise, the text entered is considered as a message and is sent to the users connected to the same channel */
                    else
                        send_multicast(users_list, buffer, users_list->channels[user->channel].name, user->username);
                    break;
            }
        }
        /* If the connection is lost, the user socket is closed and his thread terminated */
        else
        {
            quit(users_list, id);
            cont = 0;
        }
    }

    return NULL;
}

/* find_username_id returns the id associated to the username name, if none is found, -1 is returned */
int find_username_id(struct connected_users* users_list, char* name)
{
    int i=0;

    for(i=0; i<CLIENTS_NB; i++)
        if(!strcmp(users_list->users[i].username, name) )
            return i;

    return -1;
}

/* find_username_id returns the id associated to the channel name, if none is found, -1 is returned */
int find_channel_id(struct connected_users* users_list, char* name)
{
    int i=0;

    for(i=0; i<CLIENTS_NB; i++)
        if(!strcmp(users_list->channels[i].name, name) )
            return i;

    return -1;
}

/* nick checks if a username is already in use and stores it in the users_list structure, if that is not the case,
   while informing the user of the sucessful nam change */
void nick(struct connected_users* users_list, char pname[USERNAME_LEN], int id)
{
    int i=0;
    int verif = 1;
    char msg[MSG_BUFFER];
    char buffer[SIZE_BUFFER];
    char name[USERNAME_LEN];
    cmd_t cmd;

    strcpy(name, pname);

    /* If the new username is different from the old one */
    if( strcmp(name, users_list->users[id].username) )
    {

        /* checks if the username name is already in use */
        verif = (find_username_id(users_list, name) == -1) ? 1 : 0;
        
        /* If it is already in use */
        if(!verif)
        {
            send_msg(users_list->users[id].sock, "[Server] This username is already taken.\r\n", ANSI_COLOR_RED);
            
            memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
            memset(name, 0, sizeof(char)*USERNAME_LEN);
        }
        /* If it is not already in use the new username is stored into the users_list structure
           A "/nick username ip" command, which tells the client the command was a success, is sent back to the user
           It contains his username and IP address */
        else 
        {
            memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
            pthread_mutex_lock( &(users_list->mutex) );
        
            sprintf(buffer, "/nick %s %s", name, inet_ntoa(users_list->users[id].info.sin_addr));
            do_write(users_list->users[id].sock, buffer);
        
            strcpy(users_list->users[id].username, name);
        
            /* The successful /nick command is notified to the user */
            memset(buffer, 0, sizeof(char)*SIZE_BUFFER);
            sprintf(buffer, "[Server] You changed your username to %s\r\n", name);

            send_msg(users_list->users[id].sock, buffer, ANSI_COLOR_YELLOW);
            
            pthread_mutex_unlock( &(users_list->mutex) );
        }
    }
    else
        send_msg(users_list->users[id].sock, "", "");

}

/* whois sends to the requesting user information on a connected user such as his ip/port tuple and his connection date */
void whois(struct connected_users* users_list, char* name, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );
    int id_target = find_username_id(users_list, name);
    char buffer[SIZE_BUFFER] = "";

    struct tm tm;
    struct sockaddr_in info;

    if(id_target >= 0 && users_list->users[id_target].sock > -1)
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
    
    send_msg(users_list->users[id].sock, buffer, ANSI_COLOR_YELLOW);
    pthread_mutex_unlock( &(users_list->mutex) );
}

/* who sends to the requesting user the list of the current connected users */
void who(struct connected_users* users_list, int id)
{
    int i=0;
    char buffer[USERNAME_LEN*CLIENTS_NB+100] = "[Server] Online users :\r\n";

    pthread_mutex_lock( &(users_list->mutex) );
    for(i=0; i<CLIENTS_NB; i++)
    {
        if(users_list->users[i].sock > -1)
        {
            strcat(buffer, "\t- ");
            strcat(buffer, users_list->users[i].username);
            strcat(buffer, "\r\n");
        }
    }

    send_msg(users_list->users[id].sock, buffer, ANSI_COLOR_YELLOW);
    pthread_mutex_unlock( &(users_list->mutex) );
}

/* quit removes and cleans up information on a user from the users_list structure,
   disconnects him from a channel if he was connected to one,
   closes his socket and cancels his associated thread */
void quit(struct connected_users* users_list, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );
   
    /* The user is disconnected from his channel if he was connected to one */ 
    if(users_list->users[id].channel != -1)
        quit_chan(users_list, users_list->channels[users_list->users[id].channel].name, id);

    do_write(users_list->users[id].sock, "[Server] You will now be terminated.\n");
    
    /* The user socket is closed */
    close(users_list->users[id].sock);

    users_list->nb_users--;
    users_list->users[id].sock = -1;

    memset( &(users_list->users[id].username), 0, sizeof(char)*USERNAME_LEN);

    pthread_mutex_unlock( &(users_list->mutex) );
    pthread_cancel(users_list->users[id].thread);
}

/* create creates a new channel and connect its creator to it */
void create(struct connected_users* users_list, char* name, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );

    int i=0;

    /* If the channel name is not already in use */
    if( find_channel_id(users_list, name) == -1 )
    {
        /* Finds an empty spot in the channel array to store the new one */
        for(i=0; i<CLIENTS_NB; i++)
        {
            if(users_list->channels[i].id == -1)
            {
                users_list->channels[i].id = i;
                strcpy(users_list->channels[i].name, name);            
                break;
            }
        }

        /* The mutex on users_list must be unlocked before calling join, 
           because join will lock this mutex */
        pthread_mutex_unlock( &(users_list->mutex) );
        /* The users is connected to the channel he just created */
        join(users_list, name, id);
        /* The mutex on users_list is then locked again */
        pthread_mutex_lock( &(users_list->mutex) );
    }
    /* If the channel name is already in use, the user is notified */
    else
        send_msg(users_list->users[id].sock, "[Server] This channel name already exists\r\n", ANSI_COLOR_RED);

    pthread_mutex_unlock( &(users_list->mutex) );
}

/* join connects a user to the channel name */
void join(struct connected_users* users_list, char* name, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );

    int i=0;
    int id_chan = find_channel_id(users_list, name);
    char buffer[SIZE_BUFFER];
    char buffer2[SIZE_BUFFER] = "/join ";

    /* If the channel actually exists */
    if(id_chan != -1) 
    {
        /* If the user is not already connected to that channel */
        if(users_list->users[id].channel != id_chan)
        {
            /* If the user is already connected to a channel then he is kicked from that channel */
            if(users_list->users[id].channel > -1)
            {
                pthread_mutex_unlock( &(users_list->mutex) );
                quit_chan(users_list, users_list->channels[users_list->users[id].channel].name, id);
                pthread_mutex_lock( &(users_list->mutex) );
            }

            users_list->users[id].channel = id_chan;
            users_list->channels[id_chan].nb_users++;

            /* The command "/join channel" is sent to notify the user of his successful connection to the channel */
            strcat(buffer2, name);
            send_msg(users_list->users[id].sock, buffer2, "");

            /* The users already connected to the channel are notified of the current user's connection */
            sprintf(buffer, "%s has joined %s\r\n", users_list->users[id].username, name);
            send_multicast(users_list, buffer, name, "[Server]");
        }
        else
            send_msg(users_list->users[id].sock, "[Server] You are already connected to that channel\r\n", ANSI_COLOR_RED);
    }
    /* If the channel does not exist */
    else
        send_msg(users_list->users[id].sock, "[Server] This channel does not exist\r\n", ANSI_COLOR_RED);
        
    pthread_mutex_unlock( &(users_list->mutex) );
}

/* quit_chan disconnects a user from the channel name */
void quit_chan(struct connected_users* users_list, char* name, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );

    int id_chan = find_channel_id(users_list, name);
    char buffer[SIZE_BUFFER];

    /* If the channel exists */
    if(id_chan != -1) 
    {
        /* If the user requesting a deconnection is actually connected to a channel */
        if(users_list->users[id].channel != -1)
        {
            users_list->users[id].channel = -1;
            users_list->channels[id_chan].nb_users--;

            /* The command "/quit channel" is sent to the user to confirm his deconnection from the channel */
            sprintf(buffer, "/quit %s", name);
            send_msg(users_list->users[id].sock, buffer, "");

            /* If after the previous operations, the channel does not have at least one user connected to it, it is removed */
            if(users_list->channels[id_chan].nb_users <= 0)
            {
                users_list->channels[id_chan].id = -1;
                strcpy(users_list->channels[id_chan].name, "");
                users_list->channels[id_chan].nb_users = 0;
            }
            else
            {
                /* The other users connected to the channel are notified of his deconnection */
                sprintf(buffer, "%s has disconnected from the channel\r\n", users_list->users[id].username);
                send_multicast(users_list, buffer, name, "[Server]");
            }

        }
     }
    /* If the channel does not exists */
    else
        send_msg(users_list->users[id].sock, "[Server] This channel does not exist\r\n", ANSI_COLOR_RED);

    pthread_mutex_unlock( &(users_list->mutex) );
}

/* send_msg can send a colored message through the specified socket */
void send_file(struct connected_users* users_list, char* name, char* msg, int id_src)
{
    char buffer[SIZE_BUFFER] = "";
    pthread_mutex_lock( &(users_list->mutex) );

    int id_dest = find_username_id(users_list, name);

    if(id_dest != -1) 
    {
        sprintf(buffer, "/send %s %s", users_list->users[id_src].username, msg);

        do_write(users_list->users[id_dest].sock, buffer);
    }
    else
        send_msg(users_list->users[id_src].sock, "[Server] This user does not exist\r\n", ANSI_COLOR_RED);

    pthread_mutex_unlock( &(users_list->mutex) );
}

/* send_msg can send a colored message through the specified socket */
void send_msg(int sock, char* msg, char* color)
{
    /* +10 is added to the default buffer size because each color (and the color reset) takes 5 characters */
    char buffer[SIZE_BUFFER+10] = "";
    
    sprintf(buffer, "%s%s%s", color, msg, ANSI_COLOR_RESET);

    do_write(sock, buffer);
}