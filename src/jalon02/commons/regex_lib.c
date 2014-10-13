/*
 * regex.c
 *
 *  Created on: 12 oct. 2014
 *      Author: root
 */

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regex_lib.h"

regex_t regex_cmds[REGEX_CMD_NB];
regex_t regex_match_cmd;

void regex_init()
{
	int err[REGEX_CMD_NB + 1], i;
	char buf[128];

	memset(buf, 0, 128);

	err[NICK]		= regcomp (&regex_cmds[NICK],	"^/nick",	REG_NOSUB);
	err[WHOIS]		= regcomp (&regex_cmds[WHOIS],	"^/whois",	REG_NOSUB);
	err[WHO]		= regcomp (&regex_cmds[WHO],	"^/who",	REG_NOSUB);
	err[QUIT]		= regcomp (&regex_cmds[QUIT],	"^/quit",	REG_NOSUB);
	err[MSGALL]		= regcomp (&regex_cmds[MSGALL],	"^/msgall",	REG_NOSUB);
	err[MSG]		= regcomp (&regex_cmds[MSG],	"^/msg",	REG_NOSUB);
	err[CREATE]		= regcomp (&regex_cmds[CREATE],	"^/create",	REG_NOSUB);
	err[JOIN]		= regcomp (&regex_cmds[JOIN],	"^/join",	REG_NOSUB);
	err[FILEREQ]	= regcomp (&regex_cmds[FILEREQ],"^/filereq",REG_NOSUB);
	err[FILERES]	= regcomp (&regex_cmds[FILERES],"^/fileres",REG_NOSUB);

	sprintf(buf, "(^/[a-z]{1,6}) ([a-zA-Z0-9]{1,%d}) ?(.{0,%d})", USERNAME_LEN, BUFFER_LEN);
	err[REGEX_CMD_NB]	= regcomp (&regex_match_cmd, buf, REG_EXTENDED);

	memset(buf, 0, 128);

	for(i = 0; i < REGEX_CMD_NB; i++)
	{
		if(err[i] != 0)
		{
			regerror(err[i], &regex_cmds[i], buf, 128);
			printf("Error in regex.c : regcomp %d : %s\n", i, buf);
			memset(buf, 0, 100);
		}
	}
}

cmd_t regex_cmd(const char* buf)
{
	int i, m;

	if(!buf)
		return -1;

	for(i = 0; i < REGEX_CMD_NB; i++) {
		m = regexec (&regex_cmds[i], buf, 0, NULL, 0);
		if(m == 0)
			return i;
	}
	return MSGCHANNEL;
}

cmd_t regex_match(const char* buf, char userorchannel[], char message[])
{
	regmatch_t pmatch[4];
	int len, match;
	cmd_t cmd;

	if(!buf || !userorchannel || !message)
		return ERROR;

	memset(userorchannel, 0, USERNAME_LEN);
	memset(message, 0, BUFFER_LEN);

	cmd = regex_cmd(buf);

	switch(cmd)
	{
	case MSGALL:
		memcpy(message, buf + 8, strlen(buf) - 8);
		if(strlen(message) <= 1) return ERRMSGALL;
		/* no break */
	case WHO:
	case MSGCHANNEL:
		return cmd;
	}

	match = regexec(&regex_match_cmd, buf, 4, pmatch, 0);

	if(cmd == QUIT)
	{
		if(match)
			return cmd;
		else
			cmd = QUITCHANNEL;
	}

	// TODO GESTION ERREUR SI MATCH!=0

	if(match != 0)
	{
		switch(cmd)
		{
		case NICK:
			return ERRNICK;
		case WHOIS:
			return ERRWHOIS;
		case MSG:
			return ERRMSG;
		case CREATE:
			return ERRCREATE;
		case JOIN:
			return ERRJOIN;
		case FILEREQ:
			return ERRFILEREQ;
		case FILERES:
			return ERRFILERES;
		default:
			return ERROR;
		}
	}

	// Assuming there is a match

	len = pmatch[2].rm_eo - pmatch[2].rm_so;
	memcpy(userorchannel, buf + pmatch[2].rm_so, len);
	userorchannel[len] = 0;

	len = pmatch[3].rm_eo - pmatch[3].rm_so;
	memcpy(message, buf + pmatch[3].rm_so, len);
	message[len] = 0;

	if(cmd == MSG && strlen(message) <= 1) return ERRMSG;

	return cmd;
}

void regex_free()
{
	int i;

	for(i = 0; i <= REGEX_CMD_NB; i++)
		regfree (&regex_cmds[i]);
}
