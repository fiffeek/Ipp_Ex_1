#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "doubleLinkedList.h"
#include "constants.h"

// new null pointer
BList* nullBList() {
  return NULL;
}

// list initialisation with a given value
BList* initBList(unsigned short value, int *ret) {
  BList *new_blist = (BList *)malloc(sizeof(BList));

  if (new_blist == NULL) {
    // malloc was unsuccessfull
    *ret = EXIT_STATUS;
    return NULL;
  }

  new_blist->next = NULL;
  new_blist->prev = NULL;
  new_blist->value = value;

  return new_blist;
}

// adding the element to two-way linked list (at the front)
bool addFrontBList(unsigned short value, BList **list) {
  int notUsable = 0;
  BList *elem = initBList(value, &notUsable);

  // malloc was unsuccessfull
  if (notUsable == 1)
    return false;

  if(!isNullBList(*list)) {
    (*list)->prev = elem;
    elem->next = (*list);
  }

  (*list) = elem;

  return true;
}

// adds given element after the first element in a given list
bool addAfterFirstElemBList(unsigned short value, BList *list) {
  int notUsable = 0;
  BList *elem = initBList(value, &notUsable);

  if (notUsable == 1)
    return false;

  elem->next = list->next;
  list->next->prev = elem;
  list->next = elem;
  elem->prev = list;

  return true;;
}

bool isNullBList(BList *list) {
  return list == NULL;
}

void traverseBList(BList *list) {
  if(list == NULL) {
    printf("[None]\n");
    return;
  }

  printf("[");

  while (!isNullBList(list)) {
    if(list->next == NULL)
      printf("%d]\n", list->value);
    else
      printf("%d, ",list->value);

    list = list->next;
  }

  return;
}

// deletes the element toDelte in the *list1 and replaces it with
// elements startList2 -> ... [some elements] -> endList2
// implies that if startList == NULL then endList == NULL [or GUARDIAN]
void deleteConnectBLists(BList *toDelete, BList *startList2, BList *endList2) {
  endList2->next = toDelete->next;
  startList2->prev = toDelete->prev;
  toDelete->prev->next = startList2;
  toDelete->next->prev = endList2;

  free(toDelete);

  return;
}

// deletes the element inside the list and there is nothing to be inserted
// just another instance of deleteConnectBLists
void specificDeletionInsideList(BList *firstList) {
  firstList->prev->next = firstList->next;
  firstList->next->prev = firstList->prev;

  return;
}

// simple setters and getters
BList* getNextBList(BList *list) {
  return list->next;
}

BList* getPrevBList(BList *list) {
  return list->prev;
}

unsigned short getValueBList(BList *list) {
  return list->value;
}

// frees the used memory
void freeBList(BList *front) {
  if (isNullBList(front))
    return;

  BList *temp = front->next;

  while (!isNullBList(temp)) {
    free(front);
    front = temp;
    temp = temp->next;
  }

  free(front);
  front = NULL;

  return;
}
