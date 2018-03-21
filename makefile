CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -std=c11 -O2
DEPS=constants.h
OBJS=list.o doubleLinkedList.o treeStruct.o main.o
EXE=main

.PHONY: clean all

all: $(OBJS) $(EXE)

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.c treeStruct.h $(DEPS)
	$(CC) $(CFLAGS) -c main.c

treeStruct.o: treeStruct.c treeStruct.h list.h doubleLinkedList.h $(DEPS)
	$(CC) $(CFLAGS) -c treeStruct.c

%.o: %.c %.h $(DEPS)
	$(CC) $(CFLAGS) -c $<

brute: brute.cpp
	$(CXX) -o brute brute.cpp

clean:
	rm -f *.o *.gch main *.err *.in *.out brute
