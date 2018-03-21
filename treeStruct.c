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
};

typedef struct node Node;

Node *pointers[MAX_SIZE] = {NULL};

void updatePointer(int index, Node *ptr) {
  pointers[index] = ptr;

  return;
}

Node* getPointer(int index) {
  return pointers[index];
}

bool isNullNode(int index) {
  return pointers[index] == NULL;
}

void initNode(int number) {
  // new zero node
  Node *zero = (Node *)malloc(sizeof(Node));
  if (zero == NULL)
    exit(EXIT_STATUS);

  BList *temp = initBList(GUARDIAN); // [GUARDIAN] = NOT EXISTING NODES [GUARDIANS]
  addFrontBList(GUARDIAN, &temp);

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

  addAfterFirstElemBList(current, (par->firstChild));
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
    // we have to change the linked list by 'hand'
    curr->pointerOnParentsList->prev->next = curr->pointerOnParentsList->next;
    curr->pointerOnParentsList->next->prev = curr->pointerOnParentsList->prev;

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

  if (!addSorted(rating, &(getPointer(current)->movies)))
    return false;
  else
    return true;
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
void freeTree(Node *ptr) {
  if (ptr == NULL)
    return;

  BList *list = ptr->firstChild;
  while(!isNullBList(list)) {
    if(list->value == GUARDIAN) {
      list = list -> next;
      continue;
    }

    freeTree(getPointer(list->value));
    list = list->next;
  }

  freeBList(ptr->firstChild);
  freeTList(ptr->movies);
  free(ptr);
}

void traverseTree(Node *ptr) {
  printf("Traversing a tree.\n");
  traverseNode(ptr);

  return;
}

// memory complexity : O(2k + stack [prob log m])
// time complexity : O(k * n), where n is
// a number of children of *current
void marathon(Node *current, TList *moviesArray,
  int maxVal, int k, TList *tempArray) {
  bool stop = false;
  // check = temparray actual place pointer
  TList *check = tempArray;
  TList *moviescheck = moviesArray;

  // cleaning temp array
  for(int i = 0; i < k; i++) {
    setValue(check, NULL_FILM);
    check = getNext(check);
  }

  // pointer back to head
  check = tempArray;

  TList *list = current->movies;
  BList *children = current->firstChild;
  int val = WORST_FILM;

  // max value to pass to another marathon instance
  if (!isNull(list))
    val = getValue(list);

  while(!isNullBList(children)) {
    // if it is a [none node/guardian] we pass
    if(getValueBList(children) == GUARDIAN) {
      children = getNextBList(children);
      continue;
    }

    marathon(getPointer(getValueBList(children)),
      moviesArray, val, k, tempArray);

    children = getNextBList(children);
  }

  // something like merge sort
  // traversing two list by two pointers to get k max values from both of them
  while (!isNull(moviescheck) && !isNull(check) && !isNull(list)) {
    if (getValue(moviescheck) > getValue(list) && getValue(list) > maxVal) {
        setValue(check, getValue(moviescheck));
        check = getNext(check);
        moviescheck = getNext(moviescheck);
    } else if (getValue(moviescheck) < getValue(list)
      && getValue(list) > maxVal) {
        setValue(check, getValue(list));
        check = getNext(check);
        list = getNext(list);
    } else if (getValue(list) > maxVal){
        // they are equal
        setValue(check, getValue(list));
        check = getNext(check);
        moviescheck = getNext(moviescheck);
        list = getNext(list);
    } else {
      stop = true;
      break;
    }
  }

  // we re finished but there are still elements in list or array
  // it is possible but not neccessary to be the case
  if (isNull(list) || stop) {
    // there are some elements in the array
    while (!isNull(moviescheck) && !isNull(check)) {
      setValue(check, getValue(moviescheck));
      check = getNext(check);
      moviescheck = getNext(moviescheck);
    }
  }

  if (isNull(moviescheck)) {
    // there are some elements in the list
    while (!isNull(list) && !isNull(check) && getValue(list) > maxVal) {
      setValue(check, getValue(list));
      check = getNext(check);
      list = getNext(list);
    }
  }

  // we finished builing tempArray
  // time to change moviesArray
  check = tempArray;
  moviescheck = moviesArray;

  while(!isNull(check) && !isNull(moviescheck)) {
    setValue(moviescheck, getValue(check));
    check = getNext(check);
    moviescheck = getNext(moviescheck);
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

  TList *moviesArray = NULL;
  TList *tempArray = initList(NULL_FILM);
  TList *lastMovie = moviesArray;
  TList *list = getPointer(current)->movies;
  int i = 0;

  // no movies
  if (isNull(list)) {
    while(i < k) {
      if (i == 0) {
        moviesArray = initList(NULL_FILM);
      } else {
        addFront(NULL_FILM, &moviesArray);
        addFront(NULL_FILM, &tempArray);
      }

      i++;
    }
  } else {
    // moviesArray = answerArray = Movies[1::k]
    while (!isNull(list) && i < k) {
      if (i == 0) {
        moviesArray = initList(getValue(list));
        lastMovie = moviesArray;
      }
      else {
        connectLists(lastMovie, initList(getValue(list)));
        lastMovie = getNext(lastMovie);
        addFront(NULL_FILM, &tempArray);
      }

      list = getNext(list);
      i++;
    }
  }

  // moviesArray = moviesArray + [(-1), ..., (-1)] (k - moviesArraylength elem)
  while (i < k) {
    connectLists(lastMovie, initList(NULL_FILM));
    lastMovie = getNext(lastMovie);
    addFront(NULL_FILM, &tempArray);
    
    i++;
  }

  // if movies are not empty we set val to max rating from a movies list
  int val = WORST_FILM;
  if (!isNull(list))
    val = getPointer(current)->movies->value;

  marathon(getPointer(current), moviesArray, val, k, tempArray);
  // simple output
  if (isNull(moviesArray) || getValue(moviesArray) == NULL_FILM)
    printf("NONE\n");
  else {
    TList *temp = moviesArray;

    while (!isNull(temp) && getValue(temp) != NULL_FILM) {
      if ((!isNull(getNext(temp)) && getValue(getNext(temp)) == NULL_FILM)
          || isNull(getNext(temp))) {
        printf("%d\n", getValue(temp));
      } else {
        printf("%d ", getValue(temp));
      }

      temp = getNext(temp);
    }
  }

  // free the used memory
  freeTList(moviesArray);
  freeTList(tempArray);

  return true;
}
