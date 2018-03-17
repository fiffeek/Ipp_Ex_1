CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -std=c11 -O2

all: main

list.o: list.c list.h constants.h
	$(CC) $(CFLAGS) -c list.c

doubleLinkedList.o: doubleLinkedList.c doubleLinkedList.h constants.h
	$(CC) $(CFLAGS) -c doubleLinkedList.c

treeStruct.o: treeStruct.c treeStruct.h list.h doubleLinkedList.h constants.h
	$(CC) $(CFLAGS) -c treeStruct.c

main.o: main.c treeStruct.h constants.h
	$(CC) $(CFLAGS) -c main.c

main: list.o main.o treeStruct.o doubleLinkedList.o
	$(CC) $(CFLAGS) -o main main.o treeStruct.o list.o doubleLinkedList.o

brute: brute.cpp
	$(CXX) -o brute brute.cpp

clean:
	rm -f *.o main *.err *.in *.out brute
