#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "bruteForce.h"
#include "define.h"

DATA* data[FileNum];
static DATA* makeNode(double x,double y);
static void listFree(DATA* head);
int main(){
    int i,j;
    char* filename[3] = {FileName_1,FileName_2,FileName_3};
    QNODE* query = NULL;
    srand(time(NULL));
    for(i = 0 ; i < FileNum ; i++){
        double x,y;
        FILE* fp = NULL;
        fp = fopen(filename[i],"r");
        if(fp == NULL){
            printf("%s file open error\n",filename[i]);
            return -1;
        }
        data[i] = (DATA*)malloc(sizeof(DATA));
        while(fscanf(fp,"%lf, %lf",&x,&y) != -1){
            DATA* temp = NULL;
            temp = makeNode(x,y);
            temp ->link = data[i] ->link;
            data[i] ->link = temp;
        }
        if(fclose(fp) != 0){
            printf("file open error\n");
            return -1;
        }
    }
    make_query(query);
    for(i = 0 ; i < FileNum ; i++){
        printf("###%s###\n",filename[i]+8);
        bruteForce((const DATA*)data[i],query);
        //KDtree(data[i],query);
        //Rtree(data[i],query);
    }
    for(i = 0 ; i < FileNum ; i++)
        listFree(data[i]);
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
    while(head -> link != NULL){
        DATA* temp = head -> link -> link;
        free(head -> link);
        head -> link = temp;
    }
    free(head);
}
