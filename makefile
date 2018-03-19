CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -std=c11 -O2
DEPS=constants.h
OBJS=list.o doubleLinkedList.o treeStruct.o main.o
EXE=main

.PHONY: clean all

all: $(OBJS) $(EXE)

%.o: %.c %.h $(DEPS)
	$(CC) $(CFLAGS) -c $<

treeStruct.o: treeStruct.c treeStruct.h list.h doubleLinkedList.h $(DEPS)
	$(CC) $(CFLAGS) -c treeStruct.c

main.o: main.c treeStruct.h $(DEPS)
	$(CC) $(CFLAGS) -c main.c

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

brute: brute.cpp
	$(CXX) -o brute brute.cpp

clean:
	rm -f *.o main *.err *.in *.out brute
