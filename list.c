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
void push(Nptr head, void* data_node,double dist){
    if(dist != -1){
        printf("this function(list push) do not use dist please pass -1 , now : %lf\n",dist);
        return ;
    }
    Nptr new = (Nptr)malloc(sizeof(Node));
    new -> data_node = data_node;
    new -> dist = dist;
    new -> next = NULL;
    new -> next = head -> next ;
    head ->next = new;
}
void insert_ordered(Nptr head,void* data_node ,double dist){
    Nptr temp = head;
    Nptr new = (Nptr)malloc(sizeof(Node));
    new -> data_node = NULL;
    new -> dist = dist;
    new -> next = NULL;
    while(temp -> next != NULL){
        if(temp ->next ->dist > dist){
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
    Nptr temp = NULL,temp2=NULL;
    if(head -> next == NULL){
        printf("error! head empty -delete\n");
        return NULL;
    }
    temp = head ;
    while(temp ->next ->next != NULL){
        temp = temp -> next;
    }
    temp2 = temp->next;
    temp -> next = NULL;
    return temp2;
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
int list_len(Nptr head){
    int i = 0;
    while(head -> next){
        i++;
        head = head -> next;
    }
    return i;
}
