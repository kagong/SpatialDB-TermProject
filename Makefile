CC = gcc
OBJS = main.o list.o bruteForce.o KDTree.o
TARGET = 20151575
 
.SUFFIXES : .c .o
	 
all : $(TARGET)
	 
clean :
	rm -f $(OBJS) $(TARGET)
	rm -f result
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

main.o: bruteForce.h KDTree.h define.h main.c
bruteForce.o : list.h define.h bruteForce.c
KDTree.o: list.h define.h KDTree.c
list.o: list.h list.c
