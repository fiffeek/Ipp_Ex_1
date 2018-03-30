#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

const char *tab[1] ={ "addUser"};

int main() {

  srand(time(NULL));


  int A = 65000;
  for (int i = 0; i < A; i++) {
    printf("addUser 0 %d\n", i);
  }

  int B = 10000;
  for (int i = 0; i < A; i++) {
    for (int j = 0; j < B; j++) {
      printf("addMovie %d %d\n", i, j);
    }
  }

  return 0;
}
