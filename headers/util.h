#ifndef UTIL_H
#define UTIL_H

#include "tree.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

// Contact_Details stores the contact details of the owner of
// the curren vertex.
typedef struct { 
    char name[30]; 
    long int phone;
    char email[50];
    char address[100];
} Contact_Details;

// Date is used for storing and printing dates in an orderly fashion.
typedef struct {
	int year;
	int month;
	int day;
} Date;

// Medicine is used for storing information for a single medicine.
// It stores its name, price, manufacturing date and expiry date.
typedef struct {
    char name[30];
    float price;
    Date *mfg;
    Date *exp;
} Medicine;

// Crate is a structure used for transportation of various medicines
// between the manufacturers and distributors
typedef struct {
    Medicine *med;
    int quantity;
} Crate;

// Receipt has been used in two ways:
// 1. Placing orders: When used for placing orders, receipt stores the 
//    information related to the order.
// 2. Sending Shipments: When used for sending shipments receipt stores
//    a summary of the transaction that took place.
typedef struct {
    int id;
    Medicine *med;
    int quantity;
    Date *date;
    Contact_Details *cd;
    int id_from, id_to;
} Receipt;

// Function used for creating date, takes day, month and year as parameters 
// and returns a Date structure.
Date *createDate(int d, int m, int y);
// Used for printing dates
void printDate(Date *d);

// createMedicine returns a Medicine structure, takes name, price, and
// manufacturing and expiry date as parameters
Medicine *createMedicine(char n[30], float p, Date *m, Date *e);
// Used for printing information of the medicine
void printMedicine(Medicine *med);

// createContact creates a Contact_Details structure and returns it. Takes name
// phone no, email address and residential address as parameters
Contact_Details *createContact(char n[30], long int pno, char e[50], char a[100]);
// printContact prints the passed Contact_Details structure
void printContact(Contact_Details *cd);

// createReceipt creates and returns a Receipt structure. Takes id, medicine, date, quantity
// contact details and source and destination as parameters.
Receipt *createReceipt(int id, Medicine *med, Date *date, int quantity, Contact_Details *cd, int from, int to);
// printReceipt takes a Receipt structure as an argument and prints its details.
void printReceipt(Receipt *rec);

// placeOrder places an order according to the order receipt passed, it adds
// the order to the ords LinkedList of the destination vertex
void placeOrder(Vertex *root, Receipt *ord);

// createCrate creates and returns a Crate structure as specified in 
// the receipt
Crate *createCrate(Receipt *rec);
// addCrate adds the crate to the current store of the vertex
void addCrate(Vertex *v, Crate *c);

// sendShipment checks if a shipment is possible and
// sends the shipment to the destination of the receipt. It adds
// the receipts to the receipt records of the vertex and the crate to its store
void sendShipment(Vertex *root, Receipt *rec, Crate *c);

// printVertex prints a single vertex of the tree
void printVertex(Vertex *v);
// printTree prints the entire tree using recursion
void printTree(Vertex *v);

// listPending lists pending orders at a given vertex
void listPending(Vertex *v);
// listOrders lists the orders to be shipped at a given vertex
void listOrders(Vertex *v);
// listShipments lists the succesful shipments to the vertex
void listShipments(Vertex *v);

// verify asks the user about the quantity of medicine they received and
// checks if it matches with the one mentioned in the receipt. If it does
// the transaction is considered succesful and the user is asked to make payments
// The order receipt is added to the recs LinkedList of the vertex and is 
// removed from the pending orders, the store is updated.
// If the given quantity doesn't match the transaction is considered failed and 
// it is left upon the user to inquire about the case. Store is not updated.
void verify(Vertex *v);
#endif
