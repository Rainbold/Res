/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

/*
 * colors.h
 *
 *  Created on: Sep 24, 2014
 *      Author: nicolas
 */

#ifndef COLORS_H_
#define COLORS_H_

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define COLOR_PM		36
#define COLOR_CHANNEL	32
#define COLOR_ALL		35
#define COLOR_SERVER	33
#define COLOR_ERROR		31

#define colour(param) printf("\x1b[%dm",param)

#endif /* COLORS_H_ */
