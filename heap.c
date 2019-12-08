#include "heap.h"
#include<stdio.h>
#include<stdlib.h>
static unsigned int nid = 0;
static void insert_recul(HNODE** node,void* data_node,double dist,unsigned int id,unsigned int depth,unsigned int n);
void heap_insert(HNODE** head,void* data_node, double dist){
    HNODE* new = (HNODE*)malloc(sizeof(HNODE));
    unsigned int n,depth = 0;
    new -> data_node = data_node;
    new -> dist = dist;
    new -> left = new -> right = NULL;
    ++nid;
    if(*head == NULL){
        *head = new;
        return ;
    }
    //nid start at 1
    n= nid;
    for(;n ^ 1 != 0; n >>= 1)
        depth++;//top = 0
    
    n = 1 << (depth-1);
    insert_recul(head,data_node,dist,nid,depth,n);
}
static void swap(HNODE* a,HNODE* b){
    HNODE temp;
    temp.data_node = a -> data_node;
    temp.dist = a -> dist;
    a -> data_node = b -> data_node;
    a -> dist =b -> dist;
    b -> data_node = temp.data_node;
    b -> dist = temp.dist;
}
static void insert_recul(HNODE** node,void* data_node,double dist,unsigned int id,unsigned int depth,unsigned int n){
    if(*node == NULL || depth == 0){
        HNODE* new = NULL;
        new = (HNODE*)malloc(sizeof(HNODE));
        new -> data_node = data_node;
        new -> dist = dist;
        new -> left = new -> right = NULL;
        *node = new;
        return ;
    }
    if(id&n){
        insert_recul(&((*node)->right),data_node,dist,id,--depth,n >> 1);
        if((*node)->right->dist < (*node)->dist)
            swap(*node,(*node)->right);

    }
    else{
        insert_recul(&((*node)->left),data_node,dist,id,--depth,n >> 1);
        if((*node)->left->dist < (*node)->dist)
            swap(*node,(*node)->left);
    }

}
HNODE* heap_pop(HNODE** head){
    HNODE* retval = NULL,**temp = NULL,*prev=NULL;
    unsigned int n,depth = 0;
    if(*head == NULL)
        return NULL;
    if(!((*head) -> left ) && !((*head) -> right ) )
        return *head;
    //find last_node
    n=nid;
    printf("ret = %lf\n",retval->dist);
    for(;n ^ 1 != 0; n >>= 1)
        depth++;//top = 0
    n = 1 << (depth-1);
    temp = head;
    while(depth--){
        if(nid&n){//right
            temp = &((*temp) -> right);
        }
        else{
            temp = &((*temp) -> left);
        }
        n = n >> 1;
    }
    swap(*temp,*head);
    retval = *temp;
    *temp = NULL;
    //top down delete
    HNODE* node = *head;
    while(1){
        if(node->right){
            if(node -> left -> dist < node -> right -> dist){
                if(node -> dist > node -> left -> dist ){
                    swap(node,node->left);
                    node = node -> left;
                }
                else
                    break;
            }
            else{
                if(node -> dist > node -> right -> dist ){
                    swap(node,node->right);
                    node = node -> right;
                }
                else
                    break;
            }
        }
        else if(node ->left && node -> dist > node -> left -> dist )
            swap(node,node->left);
        
        else
            break;

    }
    --nid;
    return retval;
}
//example
/*
int main(){
    HNODE* head = NULL;
    int* arr = (int*)malloc(sizeof(int)*10);
    int i;
    arr[0] = 5;
    arr[1] = 2;
    arr[2] = 1;
    arr[3] = 22;
    arr[4] = 3;
    arr[5] = 111;
    arr[6] = 12;
    arr[7] = 0;
    arr[8] = -1;
    arr[9] = 21;
    for(i = 0 ; i < 10 ; i++)
        heap_insert(&head,NULL,arr[i]);

    for(i = 0 ; i < 10 ; i++){
        HNODE* temp = heap_pop(&head);
        printf("%lf\n",temp -> dist);
        free(temp);
    }
    free(arr);
    return 0;
}
*/
