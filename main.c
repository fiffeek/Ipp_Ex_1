#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "treeStruct.h"
#include "constants.h"

// reads file until the EOF or '\n' is available
bool toTheEndOfTheLine(char *input) {
  int k = strlen(input);

  if (input[k - 1] != '\n') {
    while(fgetc(stdin) != '\n'){
      if (feof(stdin)){
        break;
      }
    }
  }

  fprintf(stderr, "%s\n", "ERROR");

  return false;
}

// check if the patters is correct
// string number number\n
bool checkTwoInts(char *input, int k) {
  int i = 0, int1Size = 0, int2Size = 0;

  while (i < k && input[i] != ' ') {
    if (!((input[i] >= 'a' && input[i] <= 'z')
      || (input[i] >= 'A' || input[i] <= 'Z'))) {
      return toTheEndOfTheLine(input);
    }

    i++;
  }

  if (input[i] != ' ') {
    return toTheEndOfTheLine(input);
  }
  i++;

  while (i < k && input[i] != ' ') {
    if (input[i] < '0' || input[i] > '9' || (int1Size == 1 && input[i-1] == '0')) {
      return toTheEndOfTheLine(input);
    }

    int1Size++;
    i++;
  }

  if (int1Size >= 6) {
    return toTheEndOfTheLine(input);
  }

  if (input[i] != ' ') {
    return toTheEndOfTheLine(input);
  }
  i++;

  while (i < k && input[i] != '\n') {

    if (input[i] < '0' || input[i] > '9' || (int2Size == 1 && input[i-1] == '0')) {
      return toTheEndOfTheLine(input);
    }

    int2Size++;
    i++;
  }

  if (int2Size >= 11) {
    return toTheEndOfTheLine(input);
  }

  if (input[i] != '\n') {
    return toTheEndOfTheLine(input);
  }

  return true;
}

// the same as above but another pattern
// string number\n
bool checkOneInt(char *input, int k) {
  int i = 0;

  while (i < k && input[i] != ' ') {
    if (!((input[i] >= 'a' && input[i] <= 'z')
      || (input[i] >= 'A' || input[i] <= 'Z'))) {
      return toTheEndOfTheLine(input);
    }

    i++;
  }

  if (input[i] != ' ') {
    return toTheEndOfTheLine(input);
  }
  i++;

  int intSize = 0;

  while (i < k && input[i] != '\n') {
    if (input[i] < '0' || input[i] > '9' || (intSize == 1 && input[i-1] == '0')) {
      return toTheEndOfTheLine(input);
    }

    intSize++;
    i++;
  }

  if (intSize >= 6) {
    return toTheEndOfTheLine(input);
  }

  if (input[i] != '\n') {
    return toTheEndOfTheLine(input);
  }
  i++;

  return true;
}

// checks what pattern to search for
bool checkLine(char *input) {
  int k = strlen(input);

  if (k == 0 || input[0] == '\n')
    return false;

  if (input[0] == '#') {
    if (input[k - 1] != '\n') {
      while(fgetc(stdin) != '\n'){
        if (feof(stdin)){
          break;
        }
      }
    }

    return false;
  }

  if (input[0] == 'a') {
    return checkTwoInts(input, k);
  } else if (input[0] == 'd') {
    if (k < 4) {
      return toTheEndOfTheLine(input);
    }

    if (input[3] == 'M') {
      return checkTwoInts(input, k);
    } else if (input[3] == 'U') {
      return checkOneInt(input, k);
    } else {
      return toTheEndOfTheLine(input);
    }
  } else if (input[0] == 'm') {
    return checkTwoInts(input, k);
  } else {
    return toTheEndOfTheLine(input);
  }
}

// copies string to the same string but
// for all k : string[0] = string[start + k]
void copyStrings(char *input, int start) {
  int k = strlen(input);

  for (int i = 0; (i + start) < k; i++) {
    // copying with /n char
    input[i] = input[i + start];
  }

  return;
}

int main() {
  char *input = (char *)malloc(sizeof(char) * MAX_INPUT_SIZE);

  if (input == NULL)
    exit(EXIT_STATUS);

  initNode(0);

  while (fgets(input, MAX_INPUT_SIZE, stdin) != NULL) {
    if (!checkLine(input)) {
      continue;
    } else {
      bool err = false;
      int parentID, userID;
      long long movieRating,k;

      if (strncmp(input, "addUser ", ADD_USER_SIZE + 1) == 0) {
        copyStrings(input, ADD_USER_SIZE + 1);

        if (!sscanf(input, "%d %d", &parentID, &userID))
            err = true;

        if (err || !addChild(parentID, userID)) {
          // prompt about failure to stderr
          fprintf(stderr, "%s\n", "ERROR");
        } else {
          // adds the node
          fprintf(stdout, "%s\n", "OK");
        }
      } else if (strncmp(input, "delUser ", ADD_USER_SIZE + 1) == 0) {
        copyStrings(input, ADD_USER_SIZE + 1);

        if (!sscanf(input, "%d", &userID))
            err = true;

        if (err || !deleteChild(userID)) {
          fprintf(stderr, "%s\n", "ERROR");
        } else {
          printf("OK\n");
        }
      } else if (strncmp(input, "addMovie ", ADD_MOVIE_SIZE + 1) == 0) {
        copyStrings(input, ADD_MOVIE_SIZE + 1);

        if (!sscanf(input, "%d %lli", &userID, &movieRating))
            err = true;

        if (err || !addMovie(userID, movieRating)) {
          fprintf(stderr, "%s\n", "ERROR");
        } else {
          printf("OK\n");
        }
      } else if (strncmp(input, "delMovie ", ADD_MOVIE_SIZE + 1) == 0) {
        copyStrings(input, ADD_MOVIE_SIZE + 1);

        if (!sscanf(input, "%d %lli", &userID, &movieRating))
            err = true;

        if (err || !deleteMovie(userID, movieRating)) {
          fprintf(stderr, "%s\n", "ERROR");
        } else {
          printf("OK\n");
        }
      } else if (strncmp(input, "marathon ", ADD_MOVIE_SIZE + 1) == 0) {
        copyStrings(input, ADD_MOVIE_SIZE + 1);

        if (!sscanf(input, "%d %lli", &userID, &k))
            err = true;

        if (err || !bestMovies(userID, k)) {
          fprintf(stderr, "%s\n", "ERROR");
        }
      } else {
        if (input[strlen(input) - 1] != '\n')
          while(fgetc(stdin) != '\n'){
            if (feof(stdin)){
              break;
            }
          };

        fprintf(stderr, "%s\n", "ERROR");
      }
    }
  }

  // frees the momory used
  freeTree(0);
  free(input);

  return 0;
}
