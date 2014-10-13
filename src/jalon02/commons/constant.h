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

// Max client
#define CLIENTS_NB 3

// Size buffer server
#define SIZE_BUFFER 512

// Size msg buffer
#define MSG_BUFFER 256

// Username length
#define USERNAME_LEN 32


#ifndef SERVER_H_SDFGEQHAEHZEGFR
 	#include "network.h"
#endif

struct user_t {
    int sock;
    char username[USERNAME_LEN];
    struct sockaddr_in info;
    socklen_t info_len;
    int connection_time;
    float timer;
    pthread_mutex_t mutex;
    pthread_t thread;
};

struct connected_users {
	int sock_serv;
    int current_user;
    pthread_mutex_t mutex; // mutex de protection de users[]
    struct user_t users[CLIENTS_NB];
};

#ifndef SERVER_H_QSGPNSGPOQNSPGOSNDFG
 	#include "../server/server.h"
#endif

#ifndef USER_H_
    #include "../server/user.h"
#endif

#ifndef REGEX_H_
    #include "regex_lib.h"
#endif

#ifndef COLORS_H_
 	#include "colors.h"
#endif


#endif /* CONSTANT_H_ */
