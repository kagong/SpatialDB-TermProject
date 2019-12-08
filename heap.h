#ifndef HEAP_H
#define HEAP_H
typedef struct _hnode{
    void* data_node;
    double dist;
    struct _hnode* left,*right;
}HNODE;

void heap_insert(HNODE** head,void* data_node, double dist);
HNODE* heap_pop(HNODE** head);
#endif
