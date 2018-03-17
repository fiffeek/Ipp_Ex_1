# Individual Programming Exercise num 1

Dependencies visible in makefile.

***

Useful files:
- list.c [list.h]
- doubleLinkedlist.c [doubleLinkedList.h]
- treeStruct.c [treestruct.h]
- main.c
- constants.h

Trash files [to generate random input]:
- random_test_generator.c
- randomTestCheck.sh

Bruteforce solution:
- brute.cpp [written in cpp because of vectors library]

***

Usage:
- note that only main.c is executable

Commands:
- addUser <parent> <userID> [adds user to the tree (both id's must be >0 && <65536, parent's id can be 0 tho)
- delUser <userID> [deletes user in the tree]
- addMovie <userID> <movieRating> [adds a movieRating to the user's preferences]
- delMovie <userID> <movieRating> [deletes a movieRAting from the user's preferences]
- marathon <userID> <k> [returns the k best films from the preferences of userID and recursively, from the preferences of its children]
