/////////////////////////////////////////////////////////////////////////////////////////
//BORDEAUX INP ENSEIRB-MATMECA
//DEPARTEMENT TELECOM
//RE216 PROGRAMMATION RESEAUX
//{daniel.negru,joachim.bruneau_-_queyreix,nicolas.herbaut}@ipb.fr
////////////////////////////////////////////////////////////////////////////////////////

#ifndef USER_H_
#define USER_H_

#include "../commons/constant.h"

//typedef struct user* puser;

//you may want to implements those functions to retreive users
struct user_t* get_user_by_fd(const int fd);
struct user_t* get_user_by_uname(const char name[USERNAME_LEN]);
void add_user(const struct user_t auser);
void remove_user_by_fd(const int fd);
void remove_user_by_uname(const char name[USERNAME_LEN]);

#endif /* USER_H_ */
