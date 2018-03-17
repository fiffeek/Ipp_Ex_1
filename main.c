#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "treeStruct.h"
#include "constants.h"

int main() {
  char *input = (char *)malloc(sizeof(char) * MAX_INPUT_SIZE);

  if (input == NULL)
    exit(EXIT_STATUS);

  initNode(0);

  while(scanf("%s", input) != EOF) {
    bool err = false;
    int parentID, userID, movieRating,k;

    if (strcmp(input, "\n") == 0)
      continue;
    else if (strncmp(input, "#", 1) == 0) {
      // get and ignore one line
      while(fgetc(stdin) != '\n'){};
    } else if (strcmp(input, "addUser") == 0) {
      if (!scanf("%d %d",&parentID, &userID))
          err = true;

      if (!addChild(parentID, userID) || err) {
        // prompt about failure to stderr
        fprintf(stderr, "%s\n", "ERROR");
      } else {
        // adds the node
        fprintf(stdout, "%s\n", "OK");
      }
    } else if (strcmp(input, "delUser") == 0) {
      if (!scanf("%d", &userID))
          err = true;

      if (!deleteChild(userID) || err) {
        fprintf(stderr, "%s\n", "ERROR");
      } else {
        printf("OK\n");
      }
    } else if (strcmp(input, "addMovie") == 0) {
      if (!scanf("%d %d",&userID, &movieRating))
          err = true;

      if (!addMovie(userID, movieRating) || err) {
        fprintf(stderr, "%s\n", "ERROR");
      } else {
        printf("OK\n");
      }
    } else if (strcmp(input, "delMovie") == 0) {
      if (!scanf("%d %d",&userID, &movieRating))
          err = true;

      if (!deleteMovie(userID, movieRating) || err) {
        fprintf(stderr, "%s\n", "ERROR");
      } else {
        printf("OK\n");
      }
    } else if (strcmp(input, "marathon") == 0) {
      if (!scanf("%d %d",&userID, &k))
          err = true;

      if (!bestMovies(userID, k) || err) {
        fprintf(stderr, "%s\n", "ERROR");
      }
    } else {
      // input is invalid
      // get and ignore one line
      while(fgetc(stdin) != '\n'){};
      fprintf(stderr, "%s\n", "ERROR");
    }
  }

  freeTree(getZeroPointer());
  free(input);
  return 0;
}
