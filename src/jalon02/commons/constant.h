/*
 * constant.h
 *
 *  Created on: 6 oct. 2014
 *      Author: root
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_


#include <resolv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "../commons/network.h"


// Max client
#define CLIENTS_NB 3

// Size buffer server
#define SIZE_BUFFER 512

// Username length
#define USERNAME_LEN 32

#endif /* CONSTANT_H_ */
