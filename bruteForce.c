#include<stdio.h>
#include<time.h>

#include "dist.h"
#define FileNum 3
#define FileName_1 "input.txt"
#define FileName_2 "input.txt"
#define FileName_3 "input.txt"
double x_r = 0, y_r = 0, r = 1;
double x_k = 0, y_k = 0;
int k = 3;
typedef struct _node {
    double x,y;
    struct _node *link;
}node,*nptr;

clock_t start_point, end_point;
int rQuery(nptr head,double x,double y, double r);
int knnQuery(nptr head,double x,double y, int k);
nptr bruteForceBuild(char* filename);
void listFree(nptr head){
    while(head -> link != NULL){
        nptr temp = head -> link -> link;
        free(head -> link);
        head -> link = temp;
    }
    free(head);
}
int main(){
    char* filename[3] = {FileName_1,FileName_2,FileName_3};
    for(int i = 0 ; i < FileNum ; i++){
        int obj_ref_count;
        list = bruteForceBuild(filename[i]);

        start_point = clock();
        ref_cnt = rQuery(list,x_r,y_r,r);
        end_point = clock();
        printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("reference count : %d\n",obj_ref_count);

        start_point = clock();
        ref_cnt = knnQuery(list,x_k,y_k,k);
        end_point = clock();
        printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("reference count : %d\n",obj_ref_count);
        listFree(list);
    }

    return 0;
}
nptr makeNode(double x,double y){
    nptr = (nptr)malloc(sizeof(node));
    nptr -> x = x;
    nptr -> y = y;
    nptr -> link = NULL;
    return nptr;
}
nptr bruteForceBuild(char* filename){
    FILE* fp = NULL;
    double x,y;
    nptr head = NULL;
    fp = fopen(filename,"r");
    if(fp == NULL){
        printf("file open error\n");
        return -1;
    }
    head = (nptr)malloc(sizeof(node));
    while(fscanf(fp,"%lf, %lf",&x,&y) != -1){
        nptr temp = makeNode(x,y);
        temp ->link = head ->link;
        head ->link = temp;
    }
    if(fclose(fp) != 0){
        printf("file open error\n");
        return -1;
    }
    return head;
}
int rQuery(nptr head,double x,double y, double r){
    int ref_cnt = 0;
// nptr result = (nptr)malloc(sizeof(node));
    nptr temp = head ->link;
    while(temp != NULL){
        ++ref_cnt;
        if(dist(temp->x,temp->y,x,y) <= r){
//push result
        }
        temp = temp -> link;   
    }
    return ref_cnt;
}
int knnQuery(nptr head,double x,double y, int k){
    struct _knode{
        dobule x,y,dist;
    }*k_nodes;
    k_nodes = (struct _knode*)malloc(sizeof(struct _knode*)*k);
    nptr temp = head -> link;
    int ref_cnt = 0;

    while(temp != NULL){
        ++ref_cnt;
        double dis = dist(temp->,x,dist->y,x,y);
        for(int i = 0 ; i < k ; i++){
            if(k_nodes[i].dist <)
        }
        temp = temp -> link;
    }
    return ref_cnt;
}
