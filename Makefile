SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
CC = gcc

TARGET = 20151575
 
	 
all : $(TARGET)
	 
clean :
	rm -f $(OBJS) $(TARGET)
	rm -f result
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

main.o: bruteForce.h KDTree.h rtreeQuery.h define.h main.c
rtreeQuery.o : list.h define.h heap.h rtree.h rtreeQuery.c
rtree.o: rtree.c
bruteForce.o : list.h define.h bruteForce.c
KDTree.o: list.h define.h KDTree.c
list.o: list.c
heap.o: heap.c
