#include<stdio.h>
#include<stdlib.h>
#include "list.h"
Nptr make_list(){
    Nptr new = (Nptr)malloc(sizeof(Node));
    new -> data_node = NULL;
    new -> dist = 0;
    new -> next = NULL;
    return new;
}
void insert_ordered(Nptr head,void* data_node ,double dist){
    Nptr temp = head;
    Nptr new = (Nptr)malloc(sizeof(Node));
    new -> data_node = NULL;
    new -> dist = dist;
    new -> next = NULL;
    while(temp -> next != NULL){
        if(temp -> dist > dist){
            new -> next = temp -> next;
            temp -> next = new;
            return ;
        }
        temp = temp->next;
    }
    temp -> next = new;
}
Nptr pop(Nptr head){
    Nptr temp = NULL;
    if(head -> next == NULL){
        printf("error! head empty -pop\n");
        return NULL;
    }
    temp = head -> next;
    head -> next = head -> next -> next;
    return temp;
    
}
Nptr delete_tail(Nptr head){
    Nptr temp = NULL;
    if(head -> next == NULL){
        printf("error! head empty -delete\n");
        return NULL;
    }
    temp = head ;
    while(temp -> next != NULL){
        temp = temp -> next;
    }
    return temp;
}
double top_dist(Nptr head){
    Nptr temp = NULL;
    if(head -> next == NULL){
        printf("error! head empty -pop\n");
        return 0;
    }
    temp = head -> next;
    head -> next = head -> next -> next;
    return temp -> dist;

}
double tail_dist(Nptr head){
    Nptr temp = NULL;
    if(head -> next == NULL){
        printf("error! head empty -delete\n");
        return 0;
    }
    temp = head;
    while(temp -> next != NULL){
        temp = temp -> next;
    }
    return temp -> dist;
}
void free_list(Nptr head){
    Nptr temp = NULL;
    if(!head)
        return ;
    temp = head -> next;
    while(temp){
        Nptr temp2 = temp -> next;
        free(temp);
        temp = temp2;
    }
    free(head);
}

