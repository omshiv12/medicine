#include "util.h"

#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#ifndef SUCCESS 
#define SUCCESS 1
#endif
#define UNMATCHED 0
#define FEILD_EMPTY -1

typedef struct {
	Level type;
	int id;
	Contact_Details contactDetails;
	char password[20];
	char confirmPassword[20];

} Credentials;

void getSignup(Credentials*);
void getLogin(Level* type,int *id,char*pwd);
int validate(Credentials*);

#endif
