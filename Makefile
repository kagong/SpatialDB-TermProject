CC = gcc
OBJS = main.o list.o bruteForce.o
TARGET = 20151575
 
.SUFFIXES : .c .o
	 
all : $(TARGET)
	 
clean :
	rm -f $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: bruteForce.h define.h
bruteForce.o : list.h define.h
list.o: list.h
