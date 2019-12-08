/**
   rtree lib usage example app.
*/

#include <stdio.h>
#include <math.h>
#include<assert.h>
#include "rtree.h"

RTREEMBR rects[] = {
    { {0, 0, 0, 0, 0, 0} },  /* xmin, ymin, zmin, xmax, ymax, zmax (for 3 dimensional RTree) */
    { {1, 1, 0, 1, 1, 0} },
    { {2, 2, 0, 2, 2, 0} },
    { {3, 3, 0, 3, 3, 0} }
};


int nrects = sizeof(rects) / sizeof(rects[0]);
RTREEMBR search_rect = {
    {0, 0, 0, 7, 7, 0}   /* search will find above rects that this one overlaps */
};
RTREEMBR search_cir = {
    {0, 0, 2, 0, 0, 0}   /* search will find above rects that this one overlaps */

};
int MySearchCallback(int id, void* arg) 
{
    /* Note: -1 to make up for the +1 when data was inserted */
    fprintf (stdout, "Hit data mbr %d \n", id-1);
    return 1; /* keep going */
}

static int NODECARD = MAXCARD;
static int LEAFCARD = MAXCARD;
static int RTreeRangeSearch( RTREENODE *node, RTREEMBR *rc, pfnSearchHitCallback pfnSHCB, void* pfnParam)
{
    /* Fix not yet tested. */
    int hitCount = 0;
    int i,j;

    assert(node && rc);
    assert(node->level >= 0);
    
    if (node->level > 0) /* this is an internal node in the tree */
    {
        for (i=0; i<NODECARD; i++){
            if (node->branch[i].child ){
                double x_r = rc -> bound[0],y_r = rc -> bound[1],r = rc -> bound[2];
                double min_x = fabs(node -> branch[i].mbr.bound[0]-x_r) < fabs(node -> branch[i].mbr.bound[3] - x_r) ?
                    node -> branch[i].mbr.bound[0] : node -> branch[i].mbr.bound[3] ;
                double min_y = fabs(node -> branch[i].mbr.bound[1]-y_r) < fabs(node -> branch[i].mbr.bound[4] - y_r) ?
                    node -> branch[i].mbr.bound[1] : node -> branch[i].mbr.bound[4] ;
                double dist = 0;

                dist = sqrt(pow(min_x - x_r,2) + pow(min_y-y_r,2) );
                if(dist <= r)
                    hitCount += RTreeRangeSearch(node->branch[i].child, rc, pfnSHCB, pfnParam);
                
            }
        }
    }
    else /* this is a leaf node */
    {
#pragma warning(push)    /* C4311 */
#pragma warning( disable : 4311 )
        for (i=0; i<LEAFCARD; i++)
        {
            if (node->branch[i].child ){
                double dist = sqrt(pow(node->branch[i].mbr.bound[0] - rc -> bound[0],2) + pow( node->branch[i].mbr.bound[1] - rc -> bound[1],2)); 
                if(dist <= rc -> bound[2]){
                     hitCount++;


                /* call the user-provided callback and return if callback wants to terminate search early */
                    if(pfnSHCB && ! pfnSHCB((int)node->branch[i].child, pfnParam) )
                        return hitCount; 

                }
            }
        }
#pragma warning(pop)
    }
    return hitCount;
}
static int RTreeKnnSearch( RTREENODE *node, RTREEMBR *rc, pfnSearchHitCallback pfnSHCB, void* pfnParam)
{
    
    while(pop(nodeQ) == NULL){
        if(list_len(resultQ) <= k){
        }
        else{
        }
        //pruning 1 : knn 후보의 가장큰 실제거리 < queue 안의 MBR들min값,점의 거리   mbr,점 pruning
        //pruning 2 : 후보 mbr's minmax < queue 안의 mbr들 min 값 ) mbr pruning
        //pruning 3 : 후보 mbr's minmax < queue 안의 점과의 거리 point pruning
    }
}

int main()
{
    RTREENODE* root = RTreeCreate();
    
    int i, nhits;
    
    fprintf (stdout, "nrects = %d\n ", nrects);
    
    /* Insert all the testing data rects */
    for(i=0; i<nrects; i++){
        RTreeInsertRect(&rects[i],  /* the mbr being inserted */
                        i+1,        /* i+1 is mbr ID. ID MUST NEVER BE ZERO */
                        &root,        /* the address of rtree's root since root can change undernieth*/
                        0            /* always zero which means to add from the root */
            );
    }

    //nhits = RTreeSearch(root,&search_rect , MySearchCallback, 0);
    nhits = RTreeRangeSearch(root,&search_cir , MySearchCallback, 0);
    
    fprintf (stdout, "Search resulted in %d hits \n", nhits);

    RTreeDestroy (root);

    return 0;
}
