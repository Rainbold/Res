/*
 * regex.c
 *
 *  Created on: 12 oct. 2014
 *      Author: root
 */

#include "constant.h"

regex_t regex_cmds[REGEX_CMD_NB];
regex_t regex_match_cmd;
regex_t regex_file_cmd;
regex_t regex_filename;

void regex_init()
{
	int err[REGEX_CMD_NB + 3], i;
	char buf[256];

	memset(buf, 0, 256);

	err[NICK]		= regcomp (&regex_cmds[NICK],	"^/nick",	REG_NOSUB);
	err[WHOIS]		= regcomp (&regex_cmds[WHOIS],	"^/whois",	REG_NOSUB);
	err[WHO]		= regcomp (&regex_cmds[WHO],	"^/who",	REG_NOSUB);
	err[QUIT]		= regcomp (&regex_cmds[QUIT],	"^/quit",	REG_NOSUB);
	err[MSGALL]		= regcomp (&regex_cmds[MSGALL],	"^/msgall",	REG_NOSUB);
	err[MSG]		= regcomp (&regex_cmds[MSG],	"^/msg",	REG_NOSUB);
	err[CREATE]		= regcomp (&regex_cmds[CREATE],	"^/create",	REG_NOSUB);
	err[JOIN]		= regcomp (&regex_cmds[JOIN],	"^/join",	REG_NOSUB);
	err[SEND]		= regcomp (&regex_cmds[SEND],	"^/send",	REG_NOSUB);
	err[FILERE]		= regcomp (&regex_cmds[FILERE],	"^/filere",	REG_NOSUB);

	err[CMSGALL]	= regcomp (&regex_cmds[CMSGALL],"^/cmsgall",REG_NOSUB);
	err[CHAN]		= regcomp (&regex_cmds[CHAN],	"^/chan",	REG_NOSUB);

	sprintf(buf, "(^/[a-z]{1,7}) ([a-zA-Z0-9]{1,%d}) ?(.{0,%d})", USERNAME_LEN, MSG_BUFFER);
	err[REGEX_CMD_NB]	= regcomp (&regex_match_cmd, buf, REG_EXTENDED);
	sprintf(buf, "([0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}) ([0-9]{1,5}) ?(.{0,%d})", MSG_BUFFER);
	err[REGEX_CMD_NB+1]	= regcomp (&regex_file_cmd, buf, REG_EXTENDED);
	err[REGEX_CMD_NB+2] = regcomp (&regex_filename, "/?([a-z0-9A-Z.]+)$", REG_EXTENDED);

	memset(buf, 0, 256);

	for(i = 0; i < REGEX_CMD_NB+2; i++)
	{
		if(err[i] != 0)
		{
			regerror(err[i], &regex_cmds[i], buf, 256);
			printf("Error in regex.c : regcomp %d : %s\n", i, buf);
			memset(buf, 0, 256);
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
	memset(message, 0, MSG_BUFFER);

	cmd = regex_cmd(buf);

	switch(cmd)
	{
	case MSGALL:
		memcpy(message, buf + 8, strlen(buf) - 8);
		if(strlen(message) <= 1)
			return ERRMSGALL;
		/* no break */
	case WHO:
	case MSGCHANNEL:
		return cmd;
	default:
		break;
	}

	match = regexec(&regex_match_cmd, buf, 4, pmatch, 0);

	if(cmd == QUIT)
	{
		if(match)
			return cmd;
		else
			cmd = QUITCHANNEL;
	}

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
		case CMSGALL:
			return ERRMSGALL;
		case CREATE:
			return ERRCREATE;
		case JOIN:
			return ERRJOIN;
		case SEND:
			return ERRSEND;
		case FILERE:
			return ERRFILERE;
		case CHAN:
			return ERRCHAN;
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

void regex_get_filename(char* buf, char filename[])
{
	regmatch_t pmatch[2];
	int l, len, match;
	memset(filename, 0, MSG_BUFFER);

	match = regexec(&regex_filename, buf, 2, pmatch, 0);

	if(match == 0)
	{
		len = pmatch[1].rm_eo - pmatch[1].rm_so;
		memcpy(filename, buf + pmatch[1].rm_so, len);
		filename[len] = 0;
	}
}

void regex_get_filere(char* buf, char ip[], char port[], char filepath[])
{
	regmatch_t pmatch[4];
	int len, match;
	memset(ip, 0, 16);
	memset(port, 0, 6);
	memset(filepath, 0, MSG_BUFFER);

	match = regexec(&regex_file_cmd, buf, 4, pmatch, 0);

	if(match == 0)
	{
		len = pmatch[1].rm_eo - pmatch[1].rm_so;
		memcpy(ip, buf + pmatch[1].rm_so, len);
		ip[len] = 0;

		len = pmatch[2].rm_eo - pmatch[2].rm_so;
		memcpy(port, buf + pmatch[2].rm_so, len);
		port[len] = 0;

		len = pmatch[3].rm_eo - pmatch[3].rm_so;
		memcpy(filepath, buf + pmatch[3].rm_so, len);
		filepath[len] = 0;
		if(len >= 1) filepath[len-1] = 0;
	}
}

void regex_free()
{
	int i;

	for(i = 0; i <= REGEX_CMD_NB; i++)
		regfree (&regex_cmds[i]);
	regfree (&regex_match_cmd);
	regfree (&regex_file_cmd);
	regfree (&regex_filename);
}
