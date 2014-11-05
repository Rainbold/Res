/*
 * regex.h
 *
 *  Created on: 12 oct. 2014
 *      Author: root
 */

#ifndef REGEX_H_
#define REGEX_H_

#include "constant.h"

// Compile regex
void regex_init();

// Return the cmd enum
cmd_t regex_cmd(const char* buf);

// Return the cmd enum and write argument in the two buffers
cmd_t regex_match(const char* buf, char userorchannel[], char message[]);

void regex_get_filename(char* buf, char filename[]);

void regex_get_filere(char* buf, char ip[], char port[], char filepath[]);

// Free memory
void regex_free();

#endif /* REGEX_H_ */
