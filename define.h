#ifndef DEFINE_H
#define DEFINE_H
#define FileNum 3
#define MAX 500
#define RNUM 6
#define KNUM 11
#define MAX_DIM 2
#define FileName_1 "dataset/gaussian_dataset.txt"
#define FileName_2 "dataset/clustered_dataset.txt"
#define FileName_3 "dataset/uniformed_dataset.txt"
typedef struct _queryNode{
    double range[RNUM];
    int k[KNUM];
    double x_r,y_r;
    double x_k,y_k;
}QNODE;
typedef struct data_node {
    double x,y;
    struct data_node *link;
}DATA;
#define make_query(query)do{\
    query = (QNODE*)malloc(sizeof(QNODE));\
    query->range[0] = MAX*0.01;\
    for(j = 1 ; j < RNUM ; j++)\
        query->range[j] = MAX*0.02*j;\
    query->k[0] = 1;\
    for(j = 1 ; j < KNUM ; j++)\
        query->k[j] = j*10;\
    query -> x_r = (rand()%(MAX*100))/100.0;\
    query -> y_r = (rand()%(MAX*100))/100.0;\
    query -> x_k = (rand()%(MAX*100))/100.0;\
    query -> x_k = (rand()%(MAX*100))/100.0;\
}while(0)
#define dist(x1,y1,x2,y2) (((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))
#endif
