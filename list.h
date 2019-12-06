#ifndef LIST_H
#define LIST_H
typedef struct _node{
    void* node_ptr;
    double dist;
    struct _node *next;
}Node,*Nptr;
Nptr make_list();
void insert_ordered(void*);
void push(void*);
Nptr pop();
#endif
