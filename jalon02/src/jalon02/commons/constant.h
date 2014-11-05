/*
 * constant.h
 *
 *  Created on: 6 oct. 2014
 *      Author: root
 */


/* This file contains all the headers needed as well as the definitions of different
   structures used by the server and the client */

#ifndef CONSTANT_H_
#define CONSTANT_H_


#include <resolv.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <poll.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "colors.h"
#include "network.h"

/* Max client */
#define CLIENTS_NB 4

/* Size buffer server */
#define SIZE_BUFFER 512

/* Size msg buffer */
#define MSG_BUFFER 256

/* Username length same as channel length */
#define USERNAME_LEN 32

/* Read buffer length in clients */
#define READ_BUFFER 1024

struct user_t {
    int sock;
    struct sockaddr_in info;
    socklen_t info_len;
    pthread_mutex_t mutex;
    pthread_t thread;
};

struct connected_users {
    int sock_serv;
    int current_user;
    int nb_users;
    pthread_mutex_t mutex;
    struct user_t users[CLIENTS_NB];
};

#endif /* CONSTANT_H_ */
