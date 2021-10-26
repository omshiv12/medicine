#include "file_handle.h"
#include <stdio.h>
#include <stdlib.h>

void writeCredentials(Credentials* info){
    FILE *db;
    
    if(info->type == MANUFACTURER) db=fopen("../files/credentials/Manufacturer.txt","a");
    else if(info->type == DISTRIBUTOR) db=fopen("../files/credentials/Distributor.txt","a");
    else if(info->type == SHOP) db=fopen("../files/credentials/Shop.txt","a");

    fprintf(db,"%d~%s\n",info->id,info->password);
}

void writeInfo(Credentials* info){
    FILE *db;
    
    if(info->type == MANUFACTURER) db=fopen("../files/info/Manufacturer.txt","a");
    else if(info->type == DISTRIBUTOR) db=fopen("../files/info/Distributor.txt","a");
    else if(info->type == SHOP) db=fopen("../files/info/Shop.txt","a");

    fprintf(db,"%d~%s~%ld~%s~%s\n",info->id,info->contactDetails.name,info->contactDetails.phone,info->contactDetails.email,info->contactDetails.address);
    // printf("wrote it");
}

void writeOrders(LinkedList *orders) {
    if(orders->length == 0) return;
    FILE *fp = fopen("../files/orders.bin", "ab");
    Node *curr = orders->head;
    fwrite(orders, sizeof(LinkedList), 1,  fp);
    while(curr != NULL) {
        fwrite(((Receipt *)(curr->data)), sizeof(Receipt), 1, fp);
        curr = curr->next;
    }
    fclose(fp);
}

LinkedList *readOrders(int id) {
    FILE *fp;
    fp = fopen("../files/orders.bin", "rb");
    LinkedList *temp = createLinkedList();
    fread(temp, sizeof(LinkedList), 1, fp);
    while(temp->id != id && !feof(fp)) {
        fseek(fp, sizeof(Receipt) * temp->length, SEEK_CUR);
        fread(temp, sizeof(LinkedList), 1, fp);
    }
    if(temp->id != id) {
        fclose(fp);
        return createLinkedList();
    }
    int l = temp->length;
    Receipt *order =  (Receipt *)malloc(sizeof(Receipt) * l);
    for(int i = 0; i < l; i++) {
        fread(&order[i], sizeof(Receipt), 1, fp);
        addNode(temp, createNode(&order[i]));
    }
    fclose(fp);
    return temp;
}

void writeReceipts(LinkedList *receipts) {
    if(receipts->length == 0) return;
    FILE *fp = fopen("../files/receipts.bin", "ab");
    Node *curr = receipts->head;
    fwrite(receipts, sizeof(LinkedList), 1, fp);
    while(curr != NULL) {
        fwrite(((Receipt *)(curr->data)), sizeof(Receipt), 1, fp);
        curr = curr->next;
    }
    fclose(fp);
}

LinkedList *readReceipts(int id) {
    FILE *fp;
    fp = fopen("../files/receipts.bin", "rb");
    LinkedList *temp = createLinkedList();
    fread(temp, sizeof(LinkedList), 1, fp);
    while(temp->id != id && !feof(fp)) {
        fseek(fp, sizeof(Receipt) * temp->length, SEEK_CUR);
        fread(temp, sizeof(LinkedList), 1, fp);
    }
    if(temp->id != id) {
        fclose(fp);
        return createLinkedList();
    }
    int l = temp->length;
    Receipt *receipt =  (Receipt *)malloc(sizeof(Receipt) * l);
    for(int i = 0; i < l; i++) {
        fread(&receipt[i], sizeof(Receipt), 1, fp);
        addNode(temp, createNode(&receipt[i]));
    }
    return temp;
    fclose(fp);
}

void writeStore(LinkedList *store) {
    if(store->length == 0) return;
    FILE *fp = fopen("../files/store.bin", "ab");
    Node *curr = store->head;
    fwrite(store, 1, sizeof(LinkedList), fp);
    while(curr != NULL) {
        fwrite(((Crate *)(curr->data)), sizeof(Crate), 1, fp);
        curr = curr->next;
    }
    fclose(fp);
}

LinkedList *readStore(int id) {
    FILE *fp;
    fp = fopen("../files/store.bin", "rb");
    LinkedList *temp = createLinkedList();
    fread(temp, sizeof(LinkedList), 1, fp);
    while(temp->id != id && !feof(fp)) {
        fseek(fp, sizeof(Crate) * temp->length, SEEK_CUR);
        fread(temp, sizeof(LinkedList), 1, fp);
    }
    if(temp->id != id) {
        fclose(fp);
        return createLinkedList();
    }
    int l = temp->length;
    Crate *store =  (Crate *)malloc(sizeof(Receipt) * l);
    for(int i = 0; i < l; i++) {
        fread(&store[i], sizeof(Crate), 1, fp);
        addNode(temp, createNode(&store[i]));
    }
    return temp;
    fclose(fp);
}

void writePending(LinkedList *pending) {
    if(pending->length == 0) return;
    FILE *fp = fopen("../files/pending.bin", "ab");
    Node *curr = pending->head;
    fwrite(pending, sizeof(LinkedList), 1, fp);
    while(curr != NULL) {
        fwrite(((Receipt *)(curr->data)), sizeof(Receipt), 1, fp);
        curr = curr->next;
    }
    fclose(fp);
}

LinkedList *readPending(int id) {
    FILE *fp;
    fp = fopen("../files/pending.bin", "rb");
    LinkedList *temp = createLinkedList();
    fread(temp, sizeof(LinkedList), 1, fp);
    while(temp->id != id && !feof(fp)) {
        fseek(fp, sizeof(Receipt) * temp->length, SEEK_CUR);
        fread(temp, sizeof(LinkedList), 1, fp);
    }
    if(temp->id != id) {
        fclose(fp);
        return createLinkedList();
    }
    int l = temp->length;
    Receipt *pending =  (Receipt *)malloc(sizeof(Receipt) * l);
    for(int i = 0; i < l; i++) {
        fread(&pending[i], sizeof(Receipt), 1, fp);
        addNode(temp, createNode(&pending[i]));
    }
    return temp;
    fclose(fp);
}

void writeVertex(Vertex *v) {
    FILE *fp = fopen("../files/tree.bin", "ab");
    fwrite(v, sizeof(Vertex), 1, fp);
    fclose(fp);
    writeOrders(v->ords);
    writePending(v->pending);
    writeReceipts(v->recs);
}

Vertex *readVertex(int id, FILE *fp) {
    Vertex *temp = (Vertex *)malloc(sizeof(Vertex));
    fread(temp, sizeof(Vertex), 1, fp);
    while(temp->id != id && !feof(fp)) {
        fread(temp, sizeof(Vertex), 1, fp);
    }
    if(temp->id != id) return NULL;
    temp->ords = readOrders(temp->id);
    temp->recs = readReceipts(temp->id);
    temp->pending = readPending(temp->id);

    return temp;
}

void writeTree(Vertex *root) {
    if(root == NULL) return;
    writeVertex(root);
    Node *child = root->children->head;
    while(child != NULL) {
        writeTree(child->data);
        child = child->next;
    }
}


void update(Vertex *root) {
    remove("../files/tree.bin");
    remove("../files/orders.bin");
    remove("../files/receipts.bin");
    remove("../files/pending.bin");
    writeTree(root);
}

Vertex *readTree(int id) {
    FILE *fp = fopen("../files/tree.bin", "rb");
    Vertex *v = readVertex(id, fp);
    if(v == NULL) {
        fclose(fp);
        return NULL;
    }
    int n = v->child_num;
    v->children = createLinkedList();
    for(int i = 1; i <= n; i++) {
        Vertex *child = readTree(id * 100 + i);
        if(child != NULL)
            addNode(v->children, createNode(child));
    }
    fclose(fp);
    return v;
}

Vertex *refresh() {
    Vertex *root = (Vertex *)malloc(sizeof(Vertex));
    root = readTree(MANUFACTURER);
    return root;
}

void details_from_id(Contact_Details* cd,Level type,int id){
    FILE *db;
    int dbid;
    if(type == MANUFACTURER) db=fopen("../files/info/Manufacturer.txt","r");
    else if(type == DISTRIBUTOR) db=fopen("../files/info/Distributor.txt","r");
    else if(type == SHOP) db=fopen("../files/info/Shop.txt","r");

    while( !feof(db)){
        fscanf(db,"%d",&dbid );
        fgetc(db);
        
        // printf("id : %d ~ " ,dbid);
        // printf("password : %s \n", dbpwd);
        if(dbid == id){
            // printf("id is %d",id);
            fscanf(db,"%[^~]",cd->name);
            fgetc(db);
            fscanf(db,"%ld",&cd->phone);
            fgetc(db);
            fscanf(db,"%[^~]",cd->email);
            fgetc(db);
            fscanf(db,"%[^\n]",cd->address);
            fgetc(db);
            
            // printf("name: %s  phone :%ld email:%s  address : %s\n",cd->name,cd->phone,cd->email,cd->address);
        }
    }  
}
