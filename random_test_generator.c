#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

const char *tab[10] ={ "addUser", "delUser", "addMovie",
                "delMovie", "marathon", "# dsaads4w3 1337 2137e",
              "", "line", "line 6 9", "l i n e 9 9" };

int main() {
  int A,B,C;
  long D;
  scanf("%d %d %d %ld", &A, &B, &C, &D);
  srand(time(&D));
  A++;
  B++;
  C++;

  int numberOfOperations = (rand() % A) + 1;
  while (numberOfOperations--) {
    int operation = (rand() % 5);
    int firstInt = (rand() % B);
    int secondInt = (rand() % C);

    if (strcmp(tab[operation], "delUser") == 0) {
      printf("%s %d\n", tab[operation], firstInt);
    } else if (strcmp(tab[operation], "addUser") == 0 ||
        strcmp(tab[operation], "addMovie") == 0 ||
        strcmp(tab[operation], "delMovie") == 0 ||
        strcmp(tab[operation], "marathon") == 0){
      printf("%s %d %d\n", tab[operation], firstInt, secondInt);
    } else {
      printf("%s\n", tab[operation]);
    }
  }

  return 0;
}
