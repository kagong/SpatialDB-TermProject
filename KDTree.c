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

// kdtree의 node 자료구조 정의.
struct kd_node_t
{
    double x[MAX_DIM];
    struct kd_node_t *left, *right;
};

// 거리함수 정의.
// swap 함수 정의.
inline void swap(struct kd_node_t *x, struct kd_node_t *y)
{
    double tmp[MAX_DIM];
    memcpy(tmp, x->x, sizeof(tmp));
    memcpy(x->x, y->x, sizeof(tmp));
    memcpy(y->x, tmp, sizeof(tmp));
}

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
        
        if(store->x[idx] == med->x[idx])
            return med;
        if (store > med) end = store;
        else start = store;
    }
}

// recursion으로 kdtree를 build하는 함수.
struct kd_node_t make_kdtree(struct kd_node_t *t, int len, int i, int dim)
{
    struct kd_node_t *n;
    
    if(!len) return NULL;
    
    if((n = find_median(t, t+len, i)))
    {
        i = (i + 1) % dim;
        n->left = make_kdtree(t, n-t, i, dim);
        n->right = make_kdtree(n+1, t+len-(n+1), i, dim);
    }
    
    return n;
}

static int rQuery(double x,double y, double r){
}
static int knnQuery(double x,double y, int k){
}

void KDtree(const DATA* data,QNODE* query){
    int obj_ref_count;
    int i ;
    for(i = 0 ; i < RNUM ; i++){
        result = make_list();
        printf("\tKDtree %lf range query\n",query->range[i]);
        printf("\t\tpoint = (%lf, %lf)\n",query->x_r,query->y_r);
        start_point = clock();
        obj_ref_count = rQuery(query->x_r,query->y_r,query->range[i]);
        end_point = clock();
#if ResultPrint == 1
        print_list(result,print_data);
#endif
        printf("\t\tExe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("\t\treference count : %d\n\n\n",obj_ref_count);
        free_list(result);
    }
    for(i = 0 ; i < KNUM ; i++){
        result = make_list();
        printf("\tKDtree %dnn query\n",query->k[i]);
        printf("\t\tpoint = (%lf, %lf)\n",query->x_k,query->y_k);
        start_point = clock();
        obj_ref_count = knnQuery(query->x_k,query->y_k,query->k[i]);
        end_point = clock();
#if ResultPrint == 1
        print_list(result,print_data);
#endif
        printf("\t\tExe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("\t\treference count : %d\n\n\n",obj_ref_count);
        free_list(result);
    }
}
