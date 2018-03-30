#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#include "constants.h"

// init list with one element : value
TList* initList(int value, int *returned) {
  TList *new_list = (TList *)malloc(sizeof(TList));

  if (new_list == NULL) {
    *returned = 1;
    return NULL;
  }

  new_list->value = value;
  new_list->next = NULL;

  return new_list;
}

TList* nullTList() {
  return NULL;
}

// add new element to the front
bool addFront(int value, TList **list) {
  int notUsable = 0;
  TList *elem = initList(value, &notUsable);

  // mallock was unsuccessfull
  if (notUsable == 1)
    return false;

  elem->next = (*list);
  // changing the pointer list in memory to new_front (=elem)
  *list = elem;

  return true;
}

// externGetters
TList* getNext(TList *list) {
  return list->next;
}

int getValue(TList *list) {
  return list->value;
}

// externSetter
void setValue(TList *list, int value) {
  list->value = value;

  return;
}

bool isNull(TList *list) {
  return list == NULL;
}

// time complexity O(n), where n is number of elements in the list
bool addSorted(int value, TList **list, int *returned) {
  TList *listSorted = *list;
  // given list is a null, it inserts at the front
  if (isNull(listSorted)) {
    *list = initList(value, returned);
    return true;
  }
  // first elem in a given list is smaller than [value]
  if (listSorted->value < value) {
    addFront(value, list);
    return true;
  }
  // traversing to the point where we should add our value
  // listSorted->value >= value >= listSorted->next->value
  while(!isNull(listSorted->next) && listSorted->next->value > value) {
    listSorted = listSorted->next;
  }

  // the element was already inserted to the list and it returns false
  if (listSorted->value == value || (!isNull(listSorted->next)
    && listSorted->next->value == value))
    return false;

  // new elem inicialisation
  TList *new_elem = initList(value, returned);

  // malloc was unsuccessfull
  if (*returned == 1)
    return false; // does not matter what we return at all
    // pointers exchange (easy to draw on paper)
  new_elem->next = listSorted->next;
  listSorted->next = new_elem;

  return true;
}

// connect two lists, self-explanatory
void connectLists(TList *endfirst, TList *frontsecond) {
  TList *headNext = getNext(endfirst);
  endfirst->next = frontsecond;
  frontsecond->next = headNext;

  return;
}

// deletes the given element from the list
bool deleteElem(TList **list, int elem) {
  // checking if it is the head
  if ((*list)->value == elem) {
    TList *toFree = (*list);
    *list = (*list)->next;
    free(toFree);

    return true;
  }

  TList *temp = *list;
  // looking for the element in the list
  while(!isNull(temp->next) && temp->next->value >= elem) {
    if (temp->next->value == elem) {
      TList *toFree = temp->next;
      temp->next = temp->next->next;

      free(toFree);
      // we successfully deleted the given element
      return true;
    }
    else
      temp = temp->next;
  }
  // there is no such element
  return false;
}

// frees the used memory
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
