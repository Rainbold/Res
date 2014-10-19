/*
 * constant.h
 *
 *  Created on: 6 oct. 2014
 *      Author: root
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_


#include <regex.h>
#include <resolv.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

//#include "../server/server.h"
//#include "../server/user.h"
#include "regex_lib.h"
#include "colors.h"
#include "contrib.h"
#include "network.h"

// Max client
#define CLIENTS_NB 3

// Size buffer server
#define SIZE_BUFFER 512

// Size msg buffer
#define MSG_BUFFER 256

// Username length same as channel length
#define USERNAME_LEN 32

// Read buffer length in clients
#define READ_BUFFER 1024

struct user_t {
    int sock;
    char username[USERNAME_LEN];
    struct sockaddr_in info;
    socklen_t info_len;
    int connection_time;
    float timer;
    int channel;
    pthread_mutex_t mutex;
    pthread_t thread;
    time_t t;
    struct tm tm;
};

struct channel_t {
    int id;
    char name[USERNAME_LEN];
    int nb_users;
};

struct connected_users {
	int sock_serv;
    int current_user;
    pthread_mutex_t mutex; // mutex de protection de users[]
    struct user_t users[CLIENTS_NB];
    struct channel_t channels[CLIENTS_NB];
};

#endif /* CONSTANT_H_ */
