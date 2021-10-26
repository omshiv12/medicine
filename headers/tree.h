#ifndef TREE_H 
#define TREE_H

#include"linkedlist.h"

// Levels in the tree.
typedef enum {
    MANUFACTURER,       // highest level
    STATE,              // below manufacturer
    DISTRIBUTOR,        // distributors under a given state
    SHOP               // shops under a given distributor
} Level;

// A single vertex of a tree.
// Contains an id, a level and a LinkedList of the following:
// Orders placed here.
// Shipments pending for verification.
// Receipts of succesfull shipments.
// Store of medicines.
// Childrens.
typedef struct {
    int id;
    Level lvl;
    int child_num;
    LinkedList *ords;
    LinkedList *pending;
    LinkedList *recs;
    LinkedList *store;
    LinkedList *children;
} Vertex;

// createVertex creates and returns an object of structure Vertex. Takes
// id, level, and LinkedList of the following:
// orders, pending, receipts, store and children as parameters.
Vertex *createVertex(Level lvl, LinkedList *ords, LinkedList *pending, LinkedList *recs, LinkedList *store, LinkedList *children);
// addVertex adds a vertex to a given parent in the tree. Takes the root 
// of the tree, parent vertex and the vertex to add as the parameters.
void addVertex(Vertex *root, Vertex *parent, Vertex *v);

Vertex *findVertex(Vertex *root, int id);

#endif
