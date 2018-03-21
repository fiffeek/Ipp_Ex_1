#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "doubleLinkedList.h"
#include "constants.h"

BList* nullBList() {
  return NULL;
}

BList* initBList(int value) {
  BList *new_blist = (BList *)malloc(sizeof(BList));
  if (new_blist == NULL)
    exit(EXIT_STATUS);

  new_blist->next = NULL;
  new_blist->prev = NULL;
  new_blist->value = value;

  return new_blist;
}

// adding the element to two-way linked list
void addFrontBList(int value, BList **list) {
  BList *elem = initBList(value);

  if(!isNullBList(*list)) {
    (*list)->prev = elem;
    elem->next = (*list);
  }
  
  (*list) = elem;

  return;
}

void addAfterFirstElemBList(int value, BList *list) {
  BList *elem = initBList(value);

  elem->next = list->next;
  list->next->prev = elem;
  list->next = elem;
  elem->prev = list;

  return;
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

BList* getNextBList(BList *list) {
  return list->next;
}

BList* getPrevBList(BList *list) {
  return list->prev;
}

int getValueBList(BList *list) {
  return list->value;
}

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
