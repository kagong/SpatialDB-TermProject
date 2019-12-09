/**
  rtree lib usage example app.
  */
#include "rtreeQuery.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<assert.h>
#include<time.h>
#include "rtree.h"
#include "heap.h"
#include "list.h"
static Nptr result = NULL;

static RTREEMBR *rects ;
static int NODECARD = MAXCARD;
static int LEAFCARD = MAXCARD;
static double mid3(double x1,double x2, double x3){
    double min1 = x1 < x2 ? x1 : x2;
    if(x1 <= x2 )
        if(x2 <= x3)
            return x2;
        else if(x1 <= x3)//x3 < x2
            return x3;
        else //x3<x1
            return x1;
    else//x1>x2
        if(x1 <= x3)
            return x1;
        else if(x2 < x3)//x3 < x1
            return x3;
        else //x3<x1
            return x2;


}
static int RTreeRangeSearch( RTREENODE *node, const double x_r, const double y_r, const double r)
{
    /* Fix not yet tested. */
    int obj_ref = 0;
    int i,j;

    assert(node );
    assert(node->level >= 0);

    if (node->level > 0) /* this is an internal node in the tree */
    {
        for (i=0; i<NODECARD; i++){
            if (node->branch[i].child ){
                ++obj_ref;
                double min_x = mid3(node -> branch[i].mbr.bound[0],node -> branch[i].mbr.bound[3],x_r) ;
                double min_y = mid3(node -> branch[i].mbr.bound[1],node -> branch[i].mbr.bound[4],y_r) ;
                double dist = 0;

                dist = sqrt(pow(min_x - x_r,2) + pow(min_y-y_r,2) );
                if(dist <= r)
                    obj_ref += RTreeRangeSearch(node->branch[i].child,x_r,y_r,r);

            }
        }
    }
    else /* this is a leaf node */
    {
        for (i=0; i<LEAFCARD; i++)
        {
            if (node->branch[i].child ){
                ++obj_ref;
                double dist = sqrt(pow(node->branch[i].mbr.bound[0] - x_r,2) + pow( node->branch[i].mbr.bound[1] - y_r,2)); 
                if(dist <= r){
                    push(result,&(node->branch[i].mbr),-1);
                }
            }
        }
    }
    return obj_ref;
}

static int RTreeKnnSearch( RTREENODE *node, const double x_k, const double y_k, const int k)
{
    int obj_ref = 0;
    HNODE* nodeQ = NULL,*temp = NULL;
    RTREENODE * tempN = NULL;
    int i;
    heap_insert(&nodeQ,node,0);
    while((temp = heap_pop(&nodeQ)) != NULL){
        tempN = (RTREENODE*)temp->data_node;
        if(list_len(result) > k ){
            if( tail_dist(result) < temp -> dist){
                free(temp);
                continue;
            }
        }
        if (tempN->level > 0) /* this is an internal node in the tree */
        {
            for (i=0; i<NODECARD; i++){
                if (tempN->branch[i].child ){
                    ++obj_ref;
                    double min_x = mid3(tempN -> branch[i].mbr.bound[0],tempN -> branch[i].mbr.bound[3],x_k) ;
                    double min_y = mid3(tempN -> branch[i].mbr.bound[1],tempN -> branch[i].mbr.bound[4],y_k) ;
                    double mindist = 0;

                    mindist = sqrt(pow(min_x - x_k,2) + pow(min_y-y_k,2) );
                    if(list_len(result) < k) 
                        heap_insert(&nodeQ,tempN->branch[i].child,mindist);
                    else if(mindist < tail_dist(result)) // upward, pruning
                        heap_insert(&nodeQ,tempN->branch[i].child,mindist);

                }
            }
        }
        else /* this is a leaf node */
        {
            for (i=0; i<LEAFCARD; i++)
            {
                if (tempN->branch[i].child ){
                    ++obj_ref;
                    double dist = sqrt(pow(tempN->branch[i].mbr.bound[0] - x_k,2) + pow( tempN->branch[i].mbr.bound[1] - y_k,2));
                    if(list_len(result) < k )
                        insert_ordered(result,&(tempN->branch[i].mbr),dist);
                    else if(tail_dist(result) > dist){
                        free(delete_tail(result));
                        insert_ordered(result,&(tempN->branch[i].mbr),dist);
                    }
                    
                }
            }
        }
        free(temp);
    }
    return obj_ref;
}

static void RtreeBuild(const DATA* data,RTREENODE** root,int n){ 
    RTREEMBR *rects = (RTREEMBR*)malloc(sizeof(RTREEMBR)*n);
    DATA* temp = data -> link;
    int i = 0;
    while(temp){
        rects[i].bound[0] = rects[i].bound[3] = temp -> x;
        rects[i].bound[1] = rects[i].bound[4] = temp -> y;
        rects[i].bound[2] = rects[i++].bound[5] = 0;
        temp = temp -> link;
    }
    for(i=0; i<n; i++){
       RTreeInsertRect(&rects[i],i+1,root,0);
    }

}
void print_data_rtree(void* data_node){
    RTREEMBR* temp = (RTREEMBR*)data_node;
    printf("(%lf,%lf) ",temp->bound[0],temp->bound[1]);
}
int Rtree(const DATA* data,QNODE* query,int n){
    int obj_ref_count;
    int i ;
    clock_t start_point, end_point;



    RTREENODE* root = RTreeCreate();
    RtreeBuild(data,&root,n);
    for(i = 0 ; i < RNUM ; i++){
        result = make_list();
        printf("\tRtree %lf range query\n",query->range[i]);
        printf("\t\tpoint = (%lf, %lf)\n",query->x_r,query->y_r);
        start_point = clock();
        obj_ref_count = RTreeRangeSearch(root,query->x_r,query->y_r,query->range[i]);
        end_point = clock();
        print_list(result,print_data_rtree);
        printf("\t\tExe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("\t\treference count : %d\n\n\n",obj_ref_count);
        
        free_list(result);
    }    
    for(i = 0 ; i < KNUM ; i++){
        result = make_list();
        printf("\tRtree %dnn query\n",query->k[i]);
        printf("\t\tpoint = (%lf, %lf)\n",query->x_k,query->y_k);
        start_point = clock();
        obj_ref_count = RTreeKnnSearch(root,query->x_k,query->y_k,query->k[i]);
        
        end_point = clock();
        print_list(result,print_data_rtree);
        printf("\t\tExe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("\t\treference count : %d\n\n\n",obj_ref_count);
        free_list(result);
    } 
    RTreeDestroy (root);
    free(rects);
    return 0;

}

