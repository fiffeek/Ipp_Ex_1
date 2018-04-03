#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"
#include "doubleLinkedList.h"
#include "treeStruct.h"
#include "constants.h"

// first/lastChild are self explanatory
// so is MoviesArray = movies (it is sorted all the time)
// pointerOnParentsList is a pointer that points to the
// [firstChild, ... , lastChild] list in the parent's node
struct node{
  BList *firstChild;
  BList *lastChild;
  BList *pointerOnParentsList;
  TList *movies;
  TList *possibleValue;
};

typedef struct node Node;

// static array of pointers to make some functions run in a constant time
Node *pointers[MAX_SIZE] = {NULL};

// updates the specific array element to a given Node pointer
void updatePointer(int index, Node *ptr) {
  pointers[index] = ptr;

  return;
}

// simple setters and getters
Node* getPointer(int index) {
  return pointers[index];
}

// null check in order to shorten the functions
bool isNullNode(int index) {
  return pointers[index] == NULL;
}

void initNode(int number) {
  // new zero node
  Node *zero = (Node *)malloc(sizeof(Node));
  if (zero == NULL)
    exit(EXIT_STATUS);

  // [GUARDIAN] = NOT EXISTING NODES [GUARDIANS]
  // adds guardians at the front and at the end of the children list
  int notUsable = 0;

  BList *temp = initBList(GUARDIAN, &notUsable);
  if (!addFrontBList(GUARDIAN, &temp) || notUsable == 1) {
    // returned EXIT STATUS = 1
    freeTree(0);
    exit(EXIT_STATUS);
  }

  zero->possibleValue = nullTList();
  zero->firstChild = temp;
  zero->lastChild = getNextBList(temp);
  zero->movies = nullTList();
  zero->pointerOnParentsList = nullBList();


  updatePointer(number, zero);

  return;
}

// node number zero is special cause it does not have any parent
Node* getZeroPointer() {
  return getPointer(0);
}

bool addChild(int parent, int current) {
  // 0 <= parent <= MAX_SIZE - 1
  // 0 < curr <= MAX SIZE - 1
  if (parent < 0 || current <= 0 || parent >= MAX_SIZE || current >= MAX_SIZE)
    return false;

  // parent has not been introduced yet
  // current node is already in the tree
  if (isNullNode(parent) || !isNullNode(current))
    return false;

  initNode(current);
  Node *curr = getPointer(current);
  Node *par = getPointer(parent);

  // types castint and adding to children list after a front GUARDIAN
  unsigned short temp = (unsigned short) current;

  if (!addAfterFirstElemBList(temp, (par->firstChild))) {
    // malloc returned  EXIT_STATUS
    freeTree(0);
    exit(EXIT_STATUS);
  }

  curr->pointerOnParentsList = getNextBList(par->firstChild);

  return true;
}

bool deleteChild(int current) {
  if (current <= 0 || current >= MAX_SIZE)
    return false;

  if (isNullNode(current))
    return false;

  Node *curr = getPointer(current);

  if (curr->firstChild->next->value != GUARDIAN) {
    // deletes one element and connects lists
    deleteConnectBLists(curr->pointerOnParentsList,
      curr->firstChild->next, curr->lastChild->prev);
  } else {
    // there are no children of the node that is being deleted
    specificDeletionInsideList(curr->pointerOnParentsList);
    // free the 'alone' node
    free(curr->pointerOnParentsList);
  }

  // frees
  freeTList(curr->movies);
  free(curr->firstChild);
  free(curr->lastChild);
  free(curr);
  // deletes current from the pointers table
  updatePointer(current, NULL);
  // return success
  return true;
}

bool validBounds(int current, int rating) {
  // current is out of bounds
  if (current < 0 || current >= MAX_SIZE)
    return false;
  // rating is out of bounds
  if (rating < 0 || rating > MAX_INT)
    return false;
  // current node has not been inserted to the tree yet
  if (isNullNode(current))
    return false;

  return true;
}

bool addMovie(int current, int rating) {
  if (!validBounds(current, rating))
    return false;

  int notUsable = 0;

  if (!addSorted(rating, &(getPointer(current)->movies), &notUsable)) {
    if (notUsable == 1) {
      freeTree(0);
      exit(EXIT_STATUS);
    }

    return false;
  } else {
    if (notUsable == 1) {
      freeTree(0);
      exit(EXIT_STATUS);
    }

    return true;
  }
}

bool deleteMovie(int current, int rating) {
  if(!validBounds(current, rating))
    return false;

  if(getPointer(current)->movies == NULL)
    return false;

  if (!deleteElem(&(getPointer(current)->movies), rating))
    return false;
  else
    return true;
}

void traverseNode(Node *ptr) {
  printf("- child-first-list: ");
  traverseBList(ptr->firstChild);
  printf("- child-last-list: ");
  traverseBList(ptr->lastChild);

  if (!isNullBList(ptr->pointerOnParentsList))
    printf("- pointer on parent's list: [%d]\n",
      ptr->pointerOnParentsList->value);
  else
    printf("- pointer on parent's list: [#ERROR]\n");

  printf("- movies: ");
  traverseList(ptr->movies);

  printf("\n");
  BList *list = ptr->firstChild;
  while(!isNullBList(list)) {
    if(list->value == GUARDIAN) {
      list = list -> next;
      continue;
    }

    traverseNode(getPointer(list->value));
    list = list->next;
  }

  return;
}

// frees the used memory
void freeTree(unsigned short val) {
  int temp = (int) val;
  Node *ptr = getPointer(temp);

  if (ptr == NULL)
    return;

  BList *list = ptr->firstChild;
  while(!isNullBList(list)) {
    if(list->value == GUARDIAN) {
      list = list -> next;
      continue;
    }

    freeTree(list->value);
    list = list->next;
  }

  ptr->possibleValue = NULL;
  ptr->lastChild = NULL;
  freeBList(ptr->firstChild);
  freeTList(ptr->movies);
  free(ptr);
}

void traverseTree(Node *ptr) {
  printf("Traversing a tree.\n");
  traverseNode(ptr);

  return;
}

// memory complexity : O(stack [3*4*maxHeight bytes])
// time complexity : O(n), where n is
// a number of children of *current
int marathon(int curr, int maxVal, int previousMax) {
  Node *current = getPointer(curr);
  int answer = WORST_FILM;
  int val = maxVal;

  TList *list = current->movies;
  BList *children = current->firstChild;

  // max value to pass to another marathon instance
  if (!isNull(list) && val < getValue(list))
    val = getValue(list);

  while(!isNullBList(children)) {
    // if it is a [none node/guardian] we pass
    if(getValueBList(children) == GUARDIAN) {
      children = getNextBList(children);
      continue;
    }

    int temp = marathon(getValueBList(children), val, previousMax);
    if (temp > answer) answer = temp;

    children = getNextBList(children);
  }

  if (!isNull(current->possibleValue)
    && getValue(current->possibleValue) == previousMax)
    current->possibleValue = getNext(current->possibleValue);

  if (isNull(current->possibleValue))
    return answer;

  int temp = current->possibleValue->value;
  if (temp > maxVal && temp > answer)
    return temp;

  return answer;
}

// resets possibleValue pointer the the start of the movies list
void makePossbileValues(int curr) {
  Node *current = getPointer(curr);
  current->possibleValue = current->movies;
  BList *children = current->firstChild;

  while(!isNullBList(children)) {
    if (getValueBList(children) == GUARDIAN) {
      children = getNextBList(children);
      continue;
    }

    makePossbileValues(getValueBList(children));
    children = getNextBList(children);
  }

  return;
}

// returns the [k] best films from
// parent's movies list and (if M is the best film on parent's list)
// children movies list as long as every film in the answer array from
// a child list has better rating than M
bool bestMovies(int current, int k) {
  if (!validBounds(current, k))
    return false;
  // resetting the possibleValue pointer
  makePossbileValues(current);

  int val = WORST_FILM;
  int previousMax = WORST_FILM;

  for (int i = 0; i < k; i++) {
    previousMax = marathon(current, val, previousMax);

    // if there is no more possible value we end immediately
    if (previousMax == WORST_FILM) {
      if (i == 0)
        printf("NONE\n");
      else
        printf("\n");

      break;
    }

    if (i == 0 && k == 1)
      printf("%d\n", previousMax);
    else if(i == 0)
      printf("%d", previousMax);
    else if(i < k - 1)
      printf(" %d", previousMax);
    else
      printf(" %d\n", previousMax);
  }

  if (k == 0)
    printf("NONE\n");

  return true;
}
