#include<stdio.h>
#include<time.h>

//#include "dist.h"
#define FileNum 3
#define FileName_1 "input.txt"
#define FileName_2 "input.txt"
#define FileName_3 "input.txt"

typedef struct _node {
    double x,y;
    struct _node *link
}node,*nptr;
int bruteForceBuild(char* filename);
int main(){
    clock_t start_point, end_point;
    char* filename[3] = {FileName_1,FileName_2,FileName_3};
    for(int i = 0 ; i < FileNum ; i++){
        int obj_ref_count;
        list = bruteForceBuild(filename[i]);

        start_point = clock();
        ref_cnt=rQuery(list);
        end_point = clock();
        printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("reference count : %d\n",obj_ref_count);

        start_point = clock();
        ref_cntknnQuery(list);
        end_point = clock();
        printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
        printf("reference count : %d\n",obj_ref_count);
    }

    return 0;
}
int bruteForceBuild(char* filename){
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
