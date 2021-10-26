#include<string.h>
#include<stdio.h>
#include"credentials.h"
#include"login.h"
#include"display.h"
#include"file_handle.h"



void getSignup(Credentials* info){
    int type_choice;
    header();
    signupMenu();
    printf("\t|    SELECT TYPE                                                                |\n");
    printf("\t|_______________________________________________________________________________|\n");
    
    do{
        printf("\t|                                                                               |\n");
        printf("\t|  1.Manufacturer              2.Distributor                3.Shop              |\n");
        type_choice=inputBox();
    }while(type_choice!=1 && type_choice!=2 && type_choice!=3);

    switch (type_choice) {
        
        case (1):
            /* MANUFACTURER */
            info->type = MANUFACTURER;        
            break;
        case (2):
            /* DISTRIBUTER */
            info->type = DISTRIBUTOR;
            break;
        
        case (3):
            /* SHOP */
            info->type = SHOP;
            break;
        
        default:
            printf("\nEnter valid option\n");
            break;
    }

    printf("\t|_______________________________________________________________________________|\n");
    printf("\t|  NAME  : ");
    scanf(" %[^\n]%*c", info->contactDetails.name);
    

    printf("\t|_______________________________________________________________________________|\n");
    printf("\t|  Phone No.  : ");
    scanf(" %ld", &info->contactDetails.phone);


    printf("\t|_______________________________________________________________________________|\n");
    printf("\t|  E-Mail ID  : ");
    getchar();
    scanf(" %[^\n]%*c", info->contactDetails.email);


    printf("\t|_______________________________________________________________________________|\n");
    printf("\t|  Address  : ");
    scanf(" %[^\n]%*c", info->contactDetails.address);

    printf("\t|_______________________________________________________________________________|\n");
    printf("\t|  PASSWORD  : ");
    scanf(" %[^\n]%*c", info->password);

    printf("\t|_______________________________________________________________________________|\n");
    printf("\t|  Confirm Password  : ");
    scanf(" %[^\n]%*c", info->confirmPassword);
    printf("\t|_______________________________________________________________________________|\n");

}

void getLogin(Level* type ,int* id,char* pwd){
    header();
    loginMenu();
    int type_choice;
    printf("\t|    SELECT TYPE                                                                |\n");
    printf("\t|_______________________________________________________________________________|\n");
    
    do{
        printf("\t|                                                                               |\n");
        printf("\t|  1.Manufacturer              2.Distributor                3.Shop              |\n");
        type_choice=inputBox();
    }while(type_choice!=1 && type_choice!=2 && type_choice!=3);
    *type = type_choice;

    printf("\t|_______________________________________________________________________________|\n");
    printf("\t|  ID  : ");
    scanf("%d", id);


    printf("\t|_______________________________________________________________________________|\n");
    printf("\t|  PASSWORD  : ");
    scanf(" %[^\n]%*c",pwd);
    printf("\t|_______________________________________________________________________________|\n");
}

int validate(Credentials* info){
    if(info->contactDetails.name[0]=='\0'|| info->password[0]=='\0' || info->contactDetails.email[0]=='\0' || info->confirmPassword[0]=='\0' || info->contactDetails.address[0]=='\0'  ) return FEILD_EMPTY;
    if(strcmp(info->password,info->confirmPassword)) return UNMATCHED;
    
    return SUCCESS;
}

//Test for validate and getCredetials functions


// P R O B L E M ---> Jab phone no. me character daalne ki koshish karte hai to email id ka input skip ho jaata hai


// int main(){
//     printf("hello\n");
//     char uname[50],pwd[50];
//     Level type;
//     Credentials info;
//     getLogin(&type,uname,pwd);
//     int status = login(type,uname,pwd);
//     printf("\n\n %d\n\n",status);
//     // if(validate(&info)){ 
//     //     writeCredentials(&info);
//     //     writeInfo(&info);
//     // }
//     return 0;
// }
