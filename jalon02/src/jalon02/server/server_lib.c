/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

#include "server.h"

/* init_users will initialize the whole connected_users structure called users_list */
void init_users(int sock, struct connected_users* users_list) {
    int i=0;

    users_list->current_user = -1;
    users_list->sock_serv = sock;
    users_list->nb_users = 0;
    pthread_mutex_init( &(users_list->mutex), NULL );

    for (i=0; i<CLIENTS_NB; i++)
    {
        users_list->users[i].sock = -1;
        memset(&(users_list->users[i].info), 0, sizeof(struct sockaddr_in));
        users_list->users[i].info_len = sizeof(struct sockaddr_in);
    }

}

/* server_accepting is called and executed by a thread. Its main purpose is to accept connection
   and to call a thread handling the connection and management of this particular user */
void* server_accepting(void* p_data)
{
    struct connected_users* users_list = p_data;
    int i = 0;

    struct user_t tmpUser;

    for (;;)
    {
        /* accept connection from client */
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

            /* If the maximal number of connected users has been reached, a connection is open
               to inform him that there are no spot available at the moment */
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
    char buffer[SIZE_BUFFER];
    char buffer2[SIZE_BUFFER];

    /* The aformentionned mutex lock in the server_accepting function is unlocked here */
    pthread_mutex_unlock( &(users_list->mutex) );

    cont = 1;
    while(cont)
    {
        memset(buffer, 0, sizeof(char)*SIZE_BUFFER);

        /* The buffer is read and its content is sent back to the user */
        if(do_read(user->sock, buffer, SIZE_BUFFER) != 0)
        {
            if( strncmp(buffer, "/quit", 5) )
            {
                sprintf(buffer2, "[Server] %s", buffer);
                do_write(user->sock, buffer2);
            }
            else
            {
                quit(users_list, id);
                cont = 0;
            }
        }
        /* If do_read returns 0, which means the remote connection has been closed by the user.
           His information are cleaned up and all the memory associated is freed. */
        else
        {
            quit(users_list, id);
            cont = 0;
        }
    }

    return NULL;
}

/* quit closes the client socket and frees all the memory used by this user */
void quit(struct connected_users* users_list, int id)
{
    pthread_mutex_lock( &(users_list->mutex) );

    do_write(users_list->users[id].sock, "[Server] You will now be terminated.\n");

    /* The user socket is closed */    
    close(users_list->users[id].sock);

    users_list->nb_users--;
    users_list->users[id].sock = -1;

    /* The thread associated to this user is terminated */
    pthread_cancel(users_list->users[id].thread);

    pthread_mutex_unlock( &(users_list->mutex) );
}