#include"linkedlist.h"
#include"tree.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

Vertex *createVertex(Level l, LinkedList *ord, LinkedList *pend, LinkedList *rec, LinkedList *st, LinkedList *children) {
    Vertex *vert = (Vertex *)malloc(sizeof(Vertex));
    vert->lvl = l;
    vert->ords = ord;
    vert->pending = pend;
    vert->recs = rec;
    vert->store = st;
    vert->children = children;
    vert->child_num = vert->children->length;
    if(l == MANUFACTURER) {
        vert->id == (int)MANUFACTURER;
        vert->ords->id = vert->id;
        vert->recs->id = vert->id;
        vert->pending->id = vert->id;
        vert->store->id = vert->id;
    }
    return vert;
}

void addVertex(Vertex *root, Vertex *parent, Vertex *child) {
    if(root == NULL) return;
    if(root->id == parent->id) {
        child->id = root->id * 100 + parent->children->length + 1;
        child->ords->id = child->id;
        child->recs->id = child->id;
        child->pending->id = child->id;
        child->store->id = child->id;
        addNode(root->children, createNode(child));
        parent->child_num++;
        return;
    }
    Node *curr = root->children->head;
    while(curr != NULL) {
        addVertex(curr->data, parent, child);
        curr = curr->next;
    }
}

Vertex *findVertex(Vertex* root, int id){
    if(root == NULL) return NULL;
    if(root->id == id) {
        return root;
    }
    Vertex *v = NULL;
    Node *child = root->children->head;
    while(child != NULL) {
        v = findVertex(child->data, id);
        child = child->next;
        if(v != NULL)
            return v;
    }
    return NULL;
}
