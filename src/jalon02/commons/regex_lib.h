/*
 * regex.h
 *
 *  Created on: 12 oct. 2014
 *      Author: root
 */

#ifndef REGEX_H_
#define REGEX_H_

typedef enum
{
	// cmds
	NICK, 		// 0
	WHOIS,		// 1
	WHO,		// 2
	QUIT,		// 3
	MSGALL,		// 4
	MSG,		// 5
	CREATE,		// 6
	JOIN,		// 7
	FILEREQ,	// 8
	FILERES,	// 9

	// error in cmds
	ERRNICK,	// 10
	ERRWHOIS,	// 11
	ERRMSGALL,	// 12
	ERRMSG,		// 13
	ERRCREATE,	// 14
	ERRJOIN,	// 15
	ERRFILEREQ, // 16
	ERRFILERES, // 17

	// Global error
	ERROR,		// 18

	// other
	MSGCHANNEL, // 19
	QUITCHANNEL,// 20
} cmd_t;

#define REGEX_CMD_NB 10

// Compile regex
void regex_init();

// Return the cmd enum
cmd_t regex_cmd(const char* buf);

// Return the cmd enum and write argument in the two buffers
cmd_t regex_match(const char* buf, char userorchannel[], char message[]);

// Free memory
void regex_free();

#endif /* REGEX_H_ */
