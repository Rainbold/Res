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
#include <stdarg.h>
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
//#include "regex_lib.h"
#include "colors.h"
#include "contrib.h"
#include "network.h"

// Max client
#define CLIENTS_NB 4

// Size buffer server
#define SIZE_BUFFER 512

// Size msg buffer
#define MSG_BUFFER 256

// Username length same as channel length
#define USERNAME_LEN 32

// Read buffer length in clients
#define READ_BUFFER 1024

// Buffer for read and write binary file
#define RW_BUFFER 1024

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
    pthread_mutex_t mutex;
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
