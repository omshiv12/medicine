#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "headers/credentials.h"
#include "headers/display.h"
#include "headers/file_handle.h"
#include "headers/linkedlist.h"
#include "headers/tree.h"
#include "headers/util.h"
#include "headers/login.h"

#define CLEAR system("clear");

int main(){
    Vertex *root = createVertex(MANUFACTURER, createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList());
    // displayId(root->id);
    // press_to_continue();

    // Vertex *dist1 = createVertex(DISTRIBUTOR, createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList());
    // addVertex(root,root,dist1);
    // displayId(dist1->id);
    // press_to_continue();
    // Vertex *dist2 = createVertex(DISTRIBUTOR, createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList());
    // addVertex(root,root,dist2);
    // displayId(dist2->id);
    // press_to_continue();
    
    // Vertex *shop1 = createVertex(SHOP, createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList());
    // addVertex(root,dist1,shop1);
    // displayId(shop1->id);
    // press_to_continue();
    // Vertex *shop2 = createVertex(SHOP, createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList());
    // addVertex(root,dist1,shop2);
    // displayId(shop2->id);
    // press_to_continue();
    

//     Vertex *root2 = createVertex(MANUFACTURER, createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList());
//  displayId(root->id);

//     press_to_continue();
Date* d1=createDate(12,10,2013);
Date* mfg=createDate(21,10,2017);
Date* exp=createDate(10,10,2019);
Contact_Details* cd = createContact("Ramlal",9821455745,"ramlal@gmail.com","Street 7 colony 21 Sector 5 Preetampur");
Medicine* pmol = createMedicine("Paracetamol",10.23,mfg,exp);
Medicine* cflam = createMedicine("Combiflam",55.42,mfg,exp);
Medicine* pkill = createMedicine("PainKiller",30.00,mfg,exp);
Receipt *r1 = createReceipt(101001,pmol,d1,1000,cd,0,1);
Receipt *r2 = createReceipt(10092,cflam,d1,1000,cd,0,1);
Receipt *r3 = createReceipt(104,pkill,d1,1000,cd,0,1);
Node* n = createNode(pmol);
Node* n1 = createNode(cflam);
Node* n2 = createNode(pkill);
Node* n3 = createNode(r2);
    int choice,status,id;
    Vertex* newVertex;
   
    Level type;
    Credentials info;
    char upwd[50];
    int uid;
    
do{
    CLEAR;
    header();
    welcome();
    mainMenu();
    choice = inputBox();
    if(choice == 1){
        //Signup
        while(true){
            CLEAR;
            getSignup(&info);
            status = validate(&info);
            if(status == SUCCESS){           
                
                if(info.type == MANUFACTURER){
                    root=createVertex(MANUFACTURER,createLinkedList(),createLinkedList(),createLinkedList(),createLinkedList(),createLinkedList());
                    displayId(root->id);
                    info.id=newVertex->id;
                    writeCredentials(&info);
                    writeInfo(&info);
                    press_to_continue();
                    CLEAR;
                    Home(root,MANUFACTURER,root);
                    break;
                }
                else if(info.type == DISTRIBUTOR){
                    newVertex = createVertex(DISTRIBUTOR,createLinkedList(),createLinkedList(),createLinkedList(),createLinkedList(),createLinkedList());
                    addVertex(root,root,newVertex);
                    // Vertex* parent = findVertex(root,(newVertex->id)/100) ;
                    
                    displayId((newVertex->id));
                    info.id=newVertex->id;
                    writeCredentials(&info);
                    writeInfo(&info);
                    press_to_continue();

                    addNode(newVertex->store,n);
                    addNode(newVertex->store,n1);

                    addNode(newVertex->pending,n3);
                    

                    addNode(newVertex->ords,n3);

                    CLEAR;
                    Home(root,DISTRIBUTOR,newVertex);
                }
                else if(info.type == SHOP){
                    newVertex = createVertex(SHOP,createLinkedList(),createLinkedList(),createLinkedList(),createLinkedList(),createLinkedList());
                    Vertex* parent = findVertex(root,(newVertex->id)/100) ;
                    addVertex(root,parent,newVertex);
                    displayId((newVertex->id));
                    info.id=newVertex->id;
                    writeCredentials(&info);
                    writeInfo(&info);
                    press_to_continue();
                    
                    CLEAR;
                    Home(root,SHOP,newVertex);

                }
                
                
                // CLEAR;
                
                //yaha pe login ke baad  wala page aaega
                // printVertex(root);
                break;
            }
            else{
                errorMessageS(status);
                press_to_continue();
            }
        }
        
        
        
    }
    // printf("id :%d\n\n",((Vertex*)(root->children->head->data))->id);
    if(choice == 2){
        //Login
        while(true){
            CLEAR;
            getLogin(&type,&uid,upwd);
            status=login(type,uid,upwd);
            if(status == SUCCESS){
                Home(root,MANUFACTURER,findVertex(root,id));
                break;
            }
            else{
                errorMessageL(status);
                press_to_continue();
            }

        }
    }
}while(1);


    return 0;
}

