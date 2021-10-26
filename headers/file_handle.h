#include "credentials.h"

#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

void writeCredentials(Credentials* info);
void writeInfo(Credentials* info);
void writeVertex(Vertex* v);
Vertex *readVertex( int id, FILE *fp);
void writeList(FILE* fp,LinkedList* this);
void writeReceipt(FILE* fp,Receipt* rec);
void writeDate(FILE* fp,Date* d);
void writeMedicine(FILE* fp,Medicine* med);
void writeContact(FILE* fp,Contact_Details* cd);
void writeOrders(LinkedList *orders);
LinkedList *readOrders(int id);
void writeReceipts(LinkedList *receipts);
LinkedList *readReceipts(int id);
void writePending(LinkedList *pending);
LinkedList *readPending(int id);
void writeStore(LinkedList *store);
LinkedList *readStore(int id);
void update(Vertex *root);
Vertex *refresh();
void details_from_id(Contact_Details* cd,Level type,int id);

#endif