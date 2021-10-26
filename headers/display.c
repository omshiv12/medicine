#include "display.h"
#include <stdio.h>
#include <stdlib.h>

void header(){
    printf("\t _______________________________________________________________________________\n");
    printf("\t|                                                                               |\n");
    printf("\t|       M E D I C A L   S T O R E    M A N A G E M E N T    S Y S T E M         |\n");
    printf("\t|                                                                               |\n");
    printf("\t|_______________________________________________________________________________|\n");
}

void welcome(){
    printf("\t|                                                                               |\n");
    printf("\t|              Welcome to our Medical Store Management System !                 |\n");
    printf("\t|                   If you have signed up please Login                          |\n");
    printf("\t|                        If not then  please SignUp                             |\n");
    printf("\t|_______________________________________________________________________________|\n");
}
void mainMenu(){
    printf("\t|                                                                               |\n");
    printf("\t|  1.    SIGNUP                                                                 |\n");
    printf("\t|  2.    LOGIN                                                                  |\n");
    printf("\t|_______________________________________________________________________________|\n");
}

int inputBox(){
    int choice;
    printf("\t|                                                                               |\n");
    printf("\t|   ENTER YOUR CHOICE  :   ");
    scanf("%1d",&choice);
    
    return choice;
}
void signupMenu(){
    printf("\t|                                                                               |\n");
    printf("\t|                             S I G N U P                                       |\n");
    printf("\t|_______________________________________________________________________________|\n");
}
void loginMenu(){
    printf("\t|                                                                               |\n");
    printf("\t|                             L O G I N                                         |\n");
    printf("\t|_______________________________________________________________________________|\n");
}

void press_to_continue(){
    printf("\t|                                                                               |\n");
    printf("\t|                         PRESS ENTER TO COTINUE                                |\n");
    printf("\t|_______________________________________________________________________________|\n");
    getchar();
}

void errorMessageL(int status){
    if(status == 0){
        printf("\t|                                                                               |\n");
        printf("\t|     Usesrname not found in database.Please try siging in.                     |\n");
        printf("\t|_______________________________________________________________________________|\n");
    }
    else if(status == -1){
        printf("\t|                                                                               |\n");
        printf("\t|                      Wrong Password. Try again !                              |\n");
        printf("\t|_______________________________________________________________________________|\n");
        
    }
}
void errorMessageS(int status){
    if(status == 0){
        printf("\t|                                                                               |\n");
        printf("\t|                 Passwords didn't Match. Signin again.                         |\n");
        printf("\t|_______________________________________________________________________________|\n");
    }
    else if(status == -1){
        printf("\t|                                                                               |\n");
        printf("\t|                    You Left some field empty !                                |\n");
        printf("\t|_______________________________________________________________________________|\n");
        
    }
}

void PendingTitle(){
    printf("\t|           Here are Your Orders Pending For Verification.                      |\n");
    printf("\t|_______________________________________________________________________________|\n");
}
void StoreTitle(){
    printf("\t|                              S T O R E                                        |\n");
    printf("\t|_______________________________________________________________________________|\n");
}
void OrderTitle(){
    printf("\t|                              O R D E R S                                      |\n");
    printf("\t|_______________________________________________________________________________|\n");
}
void Home(Vertex* root,Level type,Vertex* this){
    int type_choice;
    Medicine med ;
    med.mfg=createDate(10,12,2015);
    med.exp=createDate(16,11,2020);
    med.price=55.36;
    Receipt r;
    // if(type == MANUFACTURER){
    //     //MANUFACTURER HOME
    // }
    // else if(type == DISTRIBUTOR){
        //DISTRIBUTOR HOME
        header();
        StoreTitle();
        printMedicineList(this->store);
            
            
            do{
                 printf("\t_______________________________________________________________________________\n");
                printf("\t|    O P T I O N S :                                                            |\n");
                printf("\t|_______________________________________________________________________________|\n");
                printf("\t|                                                                               |\n");
                printf("\t|  1.Purchase Medicines                 2.View Past Purchases                   |\n");
                printf("\t|                                                                               |\n");
                printf("\t|  3.Verify Pending Orders              4.Logout                                |\n");
                type_choice=inputBox();

                switch (type_choice) {
                    case 1:
                        /* Place orders  */
                        printf("\t|    P U R C H A S E :                                                          |\n");
                        printf("\t|_______________________________________________________________________________|\n");
                        printf("\t| Medicine Name : ");
                        getchar();
                        scanf("%[^\n]",med.name);

                        r.med=&med;
                        printf("\t| Quantity : ");
                        scanf("%d",&r.quantity);
                        details_from_id(&r.cd,DISTRIBUTOR, this->id);
                        placeOrder(root,&r);
                        printf("\t|                                                                               |\n");
                        printf("\t|    Order Placed !                                                             |\n");
                        printf("\t|_______________________________________________________________________________|\n");
                        
                        
                        break;
                
                    case 2:
                        /* Show Receipts  */
                        OrderTitle();
                        printReceiptList(this->ords);

                        break;
                
                    case 3:
                        /* Verify  */
                        // printf("length %d",this->pending->length);
                        // printReceiptList(this->pending);
                        verify(this);
                        break;
                
                    case 4:
                        /* Logout  */
                        printf("\n");
                        return;

                        break;
                
                    default:
                        break;
                }

            }while(type_choice!=4);
            
        
        
    // }
    // else if(type == SHOP){
    //     //SHOP HOME
    // }

}

void displayId(int id){
    printf("\t|                                                                               |\n");
    printf("\t|                   CONGRATULATIONS! Your ID is  %d.                            \n",id);
    printf("\t|                 Remember this ID for future reference !                       |\n");
    printf("\t|_______________________________________________________________________________|\n");
}
// int main(){
//     header();
//     welcome();
//     mainMenu();
//     int status = inputBox();
//     system("clear");
//     header();
//     welcome();
//     if(status != 1){
//         errorMessaage(status);
//     }
    
    
// }
