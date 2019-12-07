#include "bruteForce.h"
#include<stdio.h>
#include<time.h>
#include "list.h"
//extern double dist(double,double,double,double);
clock_t start_point, end_point;
static int rQuery(const DATA* head,double x,double y, double r);
static int knnQuery(const DATA* head,double x,double y, int k);
Nptr result = NULL;
void bruteForce(const DATA* data,QNODE* query){
    int obj_ref_count;

    int i ;
    for(i = 0 ; i < RNUM ; i++){
        result = make_list();
        printf("brute_force %lf range query\n",query->range[i]);
        start_point = clock();
        obj_ref_count = rQuery(data,query->x_r,query->y_r,query->range[i]);
        end_point = clock();
        printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("reference count : %d\n\n\n",obj_ref_count);
//        print_list(result);
        free_list(result);
    }
    for(i = 0 ; i < KNUM ; i++){
        result = make_list();
        printf("brute_force %dnn query\n",query->k[i]);
        start_point = clock();
        obj_ref_count = knnQuery(data,query->x_k,query->y_k,query->k[i]);
        end_point = clock();
        printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("reference count : %d\n\n\n",obj_ref_count);
        free_list(result);
    }
}
static int rQuery(const DATA* head,double x,double y, double r){
    int ref_cnt = 0;
    // nptr result = (nptr)malloc(sizeof(node));
    DATA* temp = head ->link;
    while(temp != NULL){
        ++ref_cnt;
        if(dist(temp->x,temp->y,x,y) <= r){
            push(result,temp,-1);
        }
        temp = temp -> link;   
    }
    return ref_cnt;
}
static int knnQuery(const DATA* head,double x,double y, int k){
    DATA* temp = head -> link;
    int ref_cnt = 0;
    int i;
    while(temp != NULL){
        ++ref_cnt;
        double dis = dist(temp -> x,temp->y,x,y);
        if(list_len(result) < k)
            insert_ordered(result,temp,dis);
        else if(tail_dist(result) > dis){
            delete_tail(result);
            insert_ordered(result,temp,dis);
        }
        temp = temp -> link;
        printf("%d\n",ref_cnt);
    }
    return ref_cnt;
}
