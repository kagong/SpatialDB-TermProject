사용자 메뉴얼
1: make
2: ./20151575
3: print results


there is user parameter in ./define.h
after you adjust under value, please recompile (make clean - make - ./20151575)
#define ResultPrint 0       //0 = number of result print, 1 = result print
#define EMode 3             //0 1 2 3 (0 no execute,1 brute,2 brute - KDTree ,3 brute - KDTree - Rtree)
#define FileNum 3           //number of input file 
#define MAX 500             //data's each axis size
#define RNUM 6              //default 6 , range query number
#define KNUM 11             //default 11, knn query number
#define MAX_DIM 2           //max dimension

if you want to execute only KDTree 
then Modify main.c like under
        #if EMode > 0
#bruteForce((const DATA*)data[i],query);    -> comment
            #if EMode > 1
            KDtree(data[i],query,n);
                #if EMode > 2
#Rtree(data[i],query,n);                    -> comment
                #endif 
            #endif 
        #endif 
