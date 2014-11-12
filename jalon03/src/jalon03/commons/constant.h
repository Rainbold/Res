/*
 * constant.h
 *
 *  Created on: 6 oct. 2014
 *      Author: root
 */


/* This file contains all the headers needed as well as the definition of different
   structures used by the server and the client */

#ifndef CONSTANT_H_
#define CONSTANT_H_


#include <regex.h>
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
#include <pthread.h>
#include <poll.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>


#include "colors.h"
#include "network.h"

// Max client (+ 1 spot used to notify users that the server is full)
#define CLIENTS_NB 5

// Size buffer server
#define SIZE_BUFFER 512

// Size msg buffer
#define MSG_BUFFER 256

// Username length same as channel length
#define USERNAME_LEN 32

// Read buffer length in clients
#define READ_BUFFER 1024

#define REGEX_CMD_NB 12

typedef enum {
  // cmds sent to server
  NICK, 		// 0
  WHOIS,		// 1
  WHO,		// 2
  QUIT,		// 3
  MSGALL,		// 4
  MSG,		// 5
  CREATE,		// 6
  JOIN,		// 7
  SEND,		// 8
  FILERE,		// 9
  
  // cmds sent to client
  CMSGALL,	// 10		/cmsgall username msg
  CHAN,		// 11		/chan user msg
  
  // error in cmds
  ERRNICK,	// 12
  ERRWHOIS,	// 13
  ERRMSGALL,	// 14
  ERRMSG,		// 15
  ERRCREATE,	// 16
  ERRJOIN,	// 17
  ERRSEND, 	// 18
  ERRFILERE,	// 19
  ERRCHAN,	// 20
  
  // Global error
  ERROR,		// 21
  
  // other
  MSGCHANNEL, // 22
  QUITCHANNEL// 23
} cmd_t;

struct user_t {
    int sock;
    char username[USERNAME_LEN];
    struct sockaddr_in info;
    socklen_t info_len;
    int channel;
    pthread_mutex_t mutex;
    pthread_t thread;
    time_t t;
    struct tm tm;
};

struct connected_users {
    int sock_serv;
    int current_user;
    int nb_users;
    pthread_mutex_t mutex;
    struct user_t users[CLIENTS_NB];
};

#endif /* CONSTANT_H_ */
