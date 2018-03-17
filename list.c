#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#include "constants.h"

// init list with one element : value
TList* initList(int value) {
  TList *new_list = (TList *)malloc(sizeof(TList));
  if (new_list == NULL)
    exit(EXIT_STATUS);

  new_list->value = value;
  new_list->next = NULL;

  return new_list;
}

TList* nullTList() {
  return NULL;
}

// add new element to the front
void addFront(int value, TList **list) {
  TList *elem = initList(value);
  elem->next = (*list);
  // changing the pointer list in memory to new_front (=elem)
  *list = elem;

  return;
}

//externGetters
TList* getNext(TList *list) {
  return list->next;
}

int getValue(TList *list) {
  return list->value;
}

//externSetter
void setValue(TList *list, int value) {
  list->value = value;

  return;
}

bool isNull(TList *list) {
  return list == NULL;
}

// time complexity O(n), where n is number of elements in the list
bool addSorted(int value, TList **list) {
  TList *listSorted = *list;

  if (isNull(listSorted)) {
    *list = initList(value);
    return true;
  }

  if (listSorted->value < value) {
    addFront(value, list);
    return true;
  }
  // traversing to the point where we should add our value
  // listSorted->value >= value >= listSorted->next->value
  while(!isNull(listSorted->next) && listSorted->next->value > value) {
    listSorted = listSorted->next;
  }

  if (listSorted->value == value || (!isNull(listSorted->next)
    && listSorted->next->value == value))
    return false;

  TList *new_elem = initList(value);
  new_elem->next = listSorted->next;
  listSorted->next = new_elem;
  return true;
}

void connectLists(TList *endfirst, TList *frontsecond) {
  TList *headNext = getNext(endfirst);
  endfirst->next = frontsecond;
  frontsecond->next = headNext;

  return;
}

bool deleteElem(TList **list, int elem) {
  if ((*list)->value == elem) {
    //printf("here\n");
    TList *toFree = (*list);
    *list = (*list)->next;
    free(toFree);

    return true;
  }

  TList *temp = *list;

  while(!isNull(temp->next) && temp->next->value >= elem) {
    if (temp->next->value == elem) {
      TList *toFree = temp->next;
      temp->next = temp->next->next;
      free(toFree);
      return true;
    }
    else
      temp = temp->next;
  }

  return false;
}

void freeTList(TList *front) {
  if (isNull(front))
    return;

  TList *temp = (front)->next;

  while (!isNull(temp)) {
    free(front);
    (front) = temp;
    temp = temp->next;
  }

  free(front);
  front = NULL;

  return;
}

void traverseList(TList *list) {
  if(isNull(list)) {
    printf("[None]\n");
    return;
  }

  printf("[");

  while (!isNull(list)) {
    if(list->next == NULL)
      printf("%d]\n", list->value);
    else
      printf("%d, ",list->value);

    list = list->next;
  }

  return;
}
