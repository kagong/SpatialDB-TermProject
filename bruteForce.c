#include "bruteForce.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "list.h"
//extern double dist(double,double,double,double);
static clock_t start_point, end_point;
static int rQuery(const DATA* head,double x,double y, double r);
static int knnQuery(const DATA* head,double x,double y, int k);
void print_data(void* data_node);
static Nptr result = NULL;
void bruteForce(const DATA* data,QNODE* query){
    int obj_ref_count;
    int i ;
    for(i = 0 ; i < RNUM ; i++){
        result = make_list();
        printf("\tbrute_force %lf range query\n",query->range[i]);
        printf("\t\tpoint = (%lf, %lf)\n",query->x_r,query->y_r);
        start_point = clock();
        obj_ref_count = rQuery(data,query->x_r,query->y_r,query->range[i]);
        end_point = clock();
        print_list(result,print_data);
        printf("\t\tExe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("\t\treference count : %d\n\n\n",obj_ref_count);
        free_list(result);
    }
    for(i = 0 ; i < KNUM ; i++){
        result = make_list();
        printf("\tbrute_force %dnn query\n",query->k[i]);
        printf("\t\tpoint = (%lf, %lf)\n",query->x_k,query->y_k);
        start_point = clock();
        obj_ref_count = knnQuery(data,query->x_k,query->y_k,query->k[i]);
        end_point = clock();
        print_list(result,print_data);
        printf("\t\tExe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("\t\treference count : %d\n\n\n",obj_ref_count);
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
            free(delete_tail(result));
            insert_ordered(result,temp,dis);
        }
        temp = temp -> link;
    }
    return ref_cnt;
}
void print_data(void* data_node){
    DATA* temp = (DATA*)data_node;
    printf("(%lf,%lf) ",temp->x,temp->y);
}
