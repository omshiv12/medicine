#ifndef LOGIN_H
#define LOGIN_H

#include "util.h"
#ifndef SUCCESS
#define SUCCESS 1;
#endif

#define PASSWORD_WRONG -1;
#define NOT_FOUND 0;


int login(Level type,int id,char*pwd);

#endif
