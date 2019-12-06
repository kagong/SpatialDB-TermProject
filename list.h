#ifndef LIST_H
#define LIST_H
typedef struct _node{
    void* data_node;
    double dist;
    struct _node *next;
}Node,*Nptr;
void insert_ordered(Nptr head,void* data_node ,double dist);
Nptr pop(Nptr head);
Nptr delete_tail(Nptr head);
double top_dist(Nptr head);
double tail_dist(Nptr head);
void free_list(Nptr head);
#endif
