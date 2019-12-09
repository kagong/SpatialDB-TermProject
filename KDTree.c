//
//  kdtree.c
//  
//
//  Created by Bigdata LAB on 2019/11/05.
//
#include "KDTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "list.h"
#define COMPARE(a, b) ((a > b) ? a : b)

static Nptr result = NULL,nodeQ = NULL;
// kdtree의 node 자료구조 정의.
struct kd_node_t
{
    double x[MAX_DIM];
    int dim;
    struct kd_node_t *left, *right;
}*head;

// 거리함수 정의.
// swap 함수 정의.
inline void swap(struct kd_node_t *x, struct kd_node_t *y)
{
    double tmp[MAX_DIM];
    memcpy(tmp, x->x, sizeof(tmp));
    memcpy(x->x, y->x, sizeof(tmp));
    memcpy(y->x, tmp, sizeof(tmp));
}

void print_data_kd(void* data_node);
// 중앙값 찾는 함수 정의. 중앙값은 kdtree의 node split point를 찾을 때 사용된다.
struct kd_node_t* find_median(struct kd_node_t *start, struct kd_node_t *end, int idx)
{
    if (end <= start) return NULL;
    if (end == start + 1)
        return start;
    
    struct kd_node_t *p, *store, *med;
    med = start + (end - start) / 2;
    double pivot;
    
    while (1)
    {
        pivot = med->x[idx];
        
        swap(med, end-1);
        for(store = p = start; p < end; p++)
            if(p->x[idx] < pivot)
            {
                if(p != store)
                    swap(p, store);
                store++;
            }
        swap(store, end - 1);
        return store;
        if(store->x[idx] == med->x[idx])
            return med;
        if (store > med) end = store;
        else start = store;
    }
}

// recursion으로 kdtree를 build하는 함수.
struct kd_node_t* make_kdtree(struct kd_node_t *t, int len, int i, int dim)
{
    struct kd_node_t *n;
    
    if(!len) return NULL;
    
    if((n = find_median(t, t+len, i)))
    {
        n -> dim = i;
        i = (i + 1) % dim;
        n->left = make_kdtree(t, n-t, i, dim);
        n->right = make_kdtree(n+1, t+len-(n+1), i, dim);
    }
    return n;
}

static int rQuery(struct kd_node_t* root,double x_r,double y_r, double r){
    int obj_ref = 0;
    int dim = 0;
    double x[MAX_DIM] = {x_r,y_r};
    Nptr temp;
    push(nodeQ,root,-1);
    while(temp = pop(nodeQ)){
        double dis;
        ++obj_ref;
        struct kd_node_t* kdnode = (struct kd_node_t*)(temp -> data_node);
        dim = kdnode -> dim;
        if(dist(kdnode -> x[0],kdnode -> x[1],x[0],x[1]) <= r){

            push(result,temp->data_node,-1);
        }
        if(kdnode -> left){
            if(x[dim] <= kdnode ->x[dim])
                push(nodeQ,kdnode->left,-1);
            else if((x[dim] - kdnode -> x[dim]) <= r)
                push(nodeQ,kdnode->left,-1);

        }
        if(kdnode -> right){
            if(x[dim] >= kdnode ->x[dim])
                push(nodeQ,kdnode->right,-1);
            else if( (kdnode -> x[dim] - x[dim]) <= r)
                push(nodeQ,kdnode->right,-1);

        }
        free(temp);
    }
    return obj_ref;
}
static int knnQuery(struct kd_node_t* root,double x_k,double y_k, int k){
    int obj_ref = 0;  
    int dim = 0;
    double x[MAX_DIM] = {x_k,y_k};
    Nptr temp;
    insert_ordered(nodeQ,root,0);
    while(temp = pop(nodeQ)){
        double dis,dis_1dim;
        ++obj_ref;
        struct kd_node_t* kdnode = (struct kd_node_t*)(temp -> data_node);
        dim = kdnode -> dim;
        dis_1dim = temp -> dist;
        if(list_len(result) < k){
            dis = dist(kdnode -> x[0],kdnode -> x[1],x[0],x[1]);

            insert_ordered(result,kdnode,dis);
        }
        else if(tail_dist(result)<=dis_1dim){//pruning
            free(temp);
            continue;
        }
        else {
            dis = dist(kdnode -> x[0],kdnode -> x[1],x[0],x[1]);
            if(tail_dist(result)>dis){
                Nptr temp = delete_tail(result);
                free(temp);
                insert_ordered(result,kdnode,dis);
            }
        }
        if(kdnode -> left){
            if(kdnode->x[dim] < x[dim])
                insert_ordered(nodeQ,kdnode->left,x[dim] - kdnode ->x[dim]);
            else
                insert_ordered(nodeQ,kdnode->left,0);
        }
        if(kdnode -> right){
            if(kdnode->x[dim] > x[dim])
               insert_ordered(nodeQ,kdnode->right,kdnode ->x[dim] - x[dim]);
            else
                insert_ordered(nodeQ,kdnode->right,0);
        }
        free(temp);
    }
    return obj_ref;
}
struct kd_node_t* KDtreebuild(const DATA* data,int n){
    struct kd_node_t* node_list = (struct kd_node_t*) malloc(sizeof(struct kd_node_t)*n);
    DATA* temp = data -> link;
    int i = 0;
    while(temp){
        node_list[i].x[0] = temp -> x;
        node_list[i++].x[1] = temp -> y;
        temp = temp -> link;
    }
    head =node_list;
    return make_kdtree(node_list,n,0,2);
}


void KDtree(const DATA* data,QNODE* query,int n){
    int obj_ref_count;
    int i ;
    clock_t start_point, end_point;
    struct kd_node_t* root = NULL;
    head = NULL;
    root = KDtreebuild(data,n);
    for(i = 0 ; i < RNUM ; i++){
        result = make_list();
        nodeQ = make_list();
        printf("\tKDtree %lf range query\n",query->range[i]);
        printf("\t\tpoint = (%lf, %lf)\n",query->x_r,query->y_r);
        start_point = clock();
        obj_ref_count = rQuery(root,query->x_r,query->y_r,query->range[i]);
        end_point = clock();
        print_list(result,print_data_kd);
        printf("\t\tExe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("\t\treference count : %d\n\n\n",obj_ref_count);
        
        free_list(nodeQ);
        free_list(result);
    }
    for(i = 0 ; i < KNUM ; i++){
        result = make_list();
        nodeQ = make_list();
        printf("\tKDtree %dnn query\n",query->k[i]);
        printf("\t\tpoint = (%lf, %lf)\n",query->x_k,query->y_k);
        start_point = clock();
        obj_ref_count = knnQuery(root,query->x_k,query->y_k,query->k[i]);
        end_point = clock();
        print_list(result,print_data_kd);
        printf("\t\tExe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("\t\treference count : %d\n\n\n",obj_ref_count);
        free_list(nodeQ);
        free_list(result);
    }
    free(head);
}
void print_data_kd(void* data_node){
    DATA* temp = (DATA*)data_node;
    printf("(%lf,%lf) ",temp->x,temp->y);
}
