#include"util.h"
Date *createDate(int y, int m, int d) {
	Date *date = (Date *)malloc(sizeof(Date));
	date->year = y;
	date->month = m;
	date->day = d;
	return date;
}

Medicine *createMedicine(char n[30], float p, Date *m, Date *e) {
    Medicine *med = (Medicine *)malloc(sizeof(Medicine));
    strcpy(med->name, n);
    med->price = p;
    med->mfg = m;
    med->exp = e;
}

void printMedicine(Medicine *med) {
    printf("\t| N A M E :   %s                                                       \n",med->name);
    printf("\t|_______________________________________________________________________________|\n");
    printf("\t| P R I C E :   %f                                                       \n",med->price);
    printf("\t|_______________________________________________________________________________|\n");

    printf("\t|  M F G  .  D A T E    : ");
    printDate(med->mfg);
    printf("                                          |\n");
    printf("\t|_______________________________________________________________________________|\n");

    printf("\t|  E X P  .  D A T E    : ");
    printDate(med->exp);
    printf("                                          |\n");
    printf("\t|_______________________________________________________________________________|\n");

}

void printDate(Date *d) {
	printf("%2d/%2d/%4d",d->day, d->month, d->year);
}

Contact_Details *createContact(char n[30], long int pno, char e[50], char a[100]) {
    Contact_Details *cd = (Contact_Details *)malloc(sizeof(Contact_Details));
    strcpy(cd->name, n);
    cd->phone = pno;
    strcpy(cd->email, e);
    strcpy(cd->address, a);
    return cd;
}

void printContact(Contact_Details *cd) {
    // printf("Name:\t%s\n", cd->name);
    printf("\t|  N A M E :            %s                                               \n",cd->name);
    printf("\t|_______________________________________________________________________________|\n");
    
    printf("\t|  P H O N E  :         %ld                                              |\n",cd->phone);
    printf("\t|_______________________________________________________________________________|\n");
    
    printf("\t| E - M A I L :         %s                              \n",cd->email);
    printf("\t|_______________________________________________________________________________|\n");

    printf("\t| A D D R E S S :       %s                              \n",cd->address);
    printf("\t|_______________________________________________________________________________|\n");
    
}

Receipt *createReceipt(int i, Medicine *m, Date *d, int q,  Contact_Details *cd, int f, int t) {
    Receipt *r = (Receipt *)malloc(sizeof(Receipt));
    r->id = i;
    r->med = m;
    r->quantity = q;
    r->date = d;
    r->cd = cd;
    r->id_from = f;
    r->id_to = t;
    return r;
}

void printReceipt(Receipt *rec) {
    printf("\t|                                                                               |\n");
    printf("\t|                               R E C E I P T                                   |\n");
    printf("\t|_______________________________________________________________________________|\n");

    printf("\t|  I D :             %d                                                        |\n",rec->id);
    printf("\t|_______________________________________________________________________________|\n");
    
    printf("\t|  D A T E :    ");
    printDate(rec->date);     
                       printf("                                                    |\n");
    printf("\t|_______________________________________________________________________________|\n");
    
    printf("\t|                     M E D I C I N E   D E T A I L S                           |\n");
    printf("\t|_______________________________________________________________________________|\n");
    printMedicine(rec->med);


    printf("\t|  Q U A N T I T Y :             %d                                           |\n",rec->quantity);
    printf("\t|_______________________________________________________________________________|\n");


    printf("\t|                     B U Y E R   D E T A I L S                                 |\n");
    printf("\t|_______________________________________________________________________________|\n");
    printContact(rec->cd);
    printf("\t| F R O M  :  %d                          T O : %d                                |\n",rec->id_from,rec->id_to);
    printf("\t|_______________________________________________________________________________|\n");
    printf("\t                                                                                 \n");
    printf("\t                                                                                 \n");


}

void printVertex(Vertex *v) {
    printf("\n\nVertex ID:\t%d\n\n", v->id);
    if(v->recs->length == 0) {
        printf("No receipts.\n");
    } else {
        printf("List of the receipts here:\n");
        printf("------------------------------------------------------\n");
        Node *curr = v->recs->head;
        while(curr != NULL) {
            printReceipt(curr->data);
            curr = curr->next;
        }
        printf("------------------------------------------------------\n");
    }
    listOrders(v);
    listPending(v);
}

void printTree(Vertex *root) {
    if(root == NULL) {
        return;
    }
    printVertex(root);
    Node *child = root->children->head;
    while(child != NULL) {
        printTree(child->data);
        child = child->next;
    }
}

void listPending(Vertex *v) {
    printf("%d", v->pending->id);
    if(v->pending->length == 0) {
        printf("No orders to verify.\n");
        return;
    }
    Node *curr = v->pending->head;
    while(curr != NULL) {
        printReceipt(curr->data);
        curr = curr->next;
    }
}

void listOrders(Vertex *v) {
    printf("%d", v->ords->id);
    if(v->ords->length == 0) {
        printf("No Orders.\n");
    } else {
        printf("Pending Orders:\n");
        printf("------------------------------------------------------\n");
        Node *curr = v->ords->head;
        while(curr != NULL) {
            printReceipt(curr->data);
            curr = curr->next;
        }
        printf("------------------------------------------------------\n");
    }
}

void listShipments(Vertex *v) {
    printf("Past successful shipments:\n");
    printf("------------------------------------------------------\n");
    Node *curr = v->recs->head;
    while(curr != NULL) {
        printReceipt(curr->data);
        curr = curr->next;
    }
    printf("------------------------------------------------------\n");
}

void placeOrder(Vertex *root, Receipt *ord) {
    
    if(root == NULL) return;
    if(root->id == ord->id_to) {
        addNode(root->ords, createNode(ord));
        return;
    }
    Node *child = root->children->head;
    while(child != NULL) {
        placeOrder(child->data, ord);
        child = child->next;
    }
}

Crate *createCrate(Receipt *rec) {
    Crate *c = (Crate *)malloc(sizeof(Crate));
    c->med = rec->med;
    c->quantity = rec->quantity;
    return c;
}

int getQuantity(Vertex *v, Medicine *med) {
    Node *crate = v->store->head;
    int q = 0;
    while(crate != NULL) {
        if(strcmp(((Crate *)(crate->data))->med->name, med->name) == 0) {
            q = ((Crate *)(crate->data))->quantity;
            break;
        }
    }
    return q;
}

void addCrate(Vertex *v, Crate *c) {
    Node *crate = v->store->head;
    while(crate != NULL) {
        if(strcmp(((Crate *)(crate->data))->med->name, c->med->name) == 0) {
            ((Crate *)(crate->data))->quantity += c->quantity;
            break;
        }
        crate = crate->next;
    }
    if(crate == NULL) 
        addNode(v->store, createNode(c));
}

void sendShipment(Vertex *root, Receipt *rec, Crate *c) {
    if(root == NULL) return;
    if(root->id == rec->id_to) {
        addNode(root->pending, createNode(rec));
        return;
    }
    Node *child = root->children->head;
    while(child != NULL) {
        sendShipment(child->data, rec, c);
        child = child->next;
    }
}

void verify(Vertex *v) {
    int n;
    char ch = 'y';
    Node *curr = v->pending->head;
    printf("Starting verification of pending receipts, when asked, press n to quit.\n");
    while(v->pending->length !=0 && ch != 'n') {
        printf("Verifying for shipment of %s on date ", ((Receipt *)(curr->data))->med->name);
        printDate(((Receipt *)(curr->data))->date);
        printf("What quantity of the above did you receive?\n");
        scanf("%d", &n);
        printf("yous entered %d\n",n);
        if(n == ((Receipt *)(curr->data))->quantity) {
           
            addNode(v->recs, curr);
            removeLastNode(v->pending);
        }
        else
            printf("There has been some problem, please signify the concerned authorities,\n");

        printf("Continue verification?");
        // printf("kuch ni %d\n",n);
        getchar();
        scanf("%c", &ch);
    }
}

