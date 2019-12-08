#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "bruteForce.h"
#include "define.h"
#include "KDTree.h"
DATA* data[FileNum];
static DATA* makeNode(double x,double y);
static void listFree(DATA* head);
int main(){
    int i,j,n=0;
    char* filename[3] = {FileName_1,FileName_2,FileName_3};
    QNODE* query = NULL;
    srand(time(NULL));
    make_query(query);
    for(i = 0 ; i < FileNum ; i++){
        double x,y;
        FILE* fp = NULL;
        fp = fopen(filename[i],"r");
        if(fp == NULL){
            printf("%s file open error\n",filename[i]);
            return -1;
        }
        data[i] = (DATA*)malloc(sizeof(DATA));
        n=0;
        while(fscanf(fp,"%lf, %lf",&x,&y) != -1){
            n++;
            DATA* temp = NULL;
            temp = makeNode(x,y);
            temp ->link = data[i] ->link;
            data[i] ->link = temp;
        }
        if(fclose(fp) != 0){
            printf("file open error\n");
            return -1;
        }
        printf("###%s###\n",filename[i]+8);
        #if EMode > 0
        bruteForce((const DATA*)data[i],query);
            #if EMode > 1
            KDtree(data[i],query,n);
                #if EMode > 2
                Rtree(data[i],query);
                #endif 
            #endif 
        #endif 
        listFree(data[i]);

    }
    free(query);
    return 0;
}
static DATA* makeNode(double x,double y){
    DATA* temp = (DATA*)malloc(sizeof(DATA));
    temp -> x = x;
    temp -> y = y;
    temp -> link = NULL;
    return temp;
}
static void listFree(DATA* head){
    int i = 0;
    while(head -> link != NULL){
        DATA* temp = head -> link -> link;
        free(head -> link);
        head -> link = temp;
    }
    free(head);
}
