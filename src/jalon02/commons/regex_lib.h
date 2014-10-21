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

	// user1 envoie au serveur /send user2 chemin
	// serveur envoie à user2 /send user1 chemin
	// si user2 accepte, il décide d'un port, il créer un serveur
	// et envoie au serveur /fileres ip port chemin
	// le serveur envoie à user1 /fileres user2 ip port chemin
	// user1 se connect à ip port et envoie le fichier chemin

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
	QUITCHANNEL,// 23
} cmd_t;

#define REGEX_CMD_NB 12

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
