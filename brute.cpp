#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_SIZE 65536
#define MAX_INT 2147483647
#define MAX_INPUT_SIZE 30
#define EXIT_STATUS 1

struct Node{
  int parent;
  bool intree;
  vector <int> childList;
  vector <int> filmList;
};

Node tab[65536];

bool validBounds(int current, int rating) {
  // current is out of bounds
  if (current < 0 || current >= MAX_SIZE)
    return false;
  // rating is out of bounds
  if (rating < 0 || rating > MAX_INT)
    return false;

  if (tab[current].intree == false)
  return false;

  return true;
}

bool userAdd(int parent, int userID) {
  if (tab[parent].intree == false || tab[userID].intree == true)
    return false;

  if (parent < 0 || userID <= 0 || parent >= MAX_SIZE || userID >= MAX_SIZE)
      return false;

  tab[parent].childList.push_back(userID);
  tab[userID].intree = true;
  tab[userID].parent = parent;
  return true;
}

bool delUser(int userID) {
  if (tab[userID].intree == false)
    return false;

  if (userID <= 0 || userID >= MAX_SIZE)
      return false;

  vector <int> temp;
  temp.clear();
  int parent = tab[userID].parent;
  int pSize = tab[parent].childList.size();
  int vSize = tab[userID].childList.size();

  for (int i = 0; i < pSize; i++) {
    if (tab[parent].childList[i] != userID) {
      temp.push_back(tab[parent].childList[i]);
    }
  }

  for (int i = 0; i < vSize; i++) {
    temp.push_back(tab[userID].childList[i]);
    tab[tab[userID].childList[i]].parent = parent;
  }

  tab[parent].childList = temp;
  tab[userID].intree = false;
  tab[userID].parent = -1;
  tab[userID].childList.clear();
  tab[userID].filmList.clear();

  return true;
}

bool addMovie(int userID, int rating) {
  if (!validBounds(userID, rating))
    return false;

  bool check = false;
  int vSize = tab[userID].filmList.size();
  for (int i = 0; i < vSize; i++) {
    if (tab[userID].filmList[i] == rating)
      check = true;
  }

  if (!check) {
    tab[userID].filmList.push_back(rating);
    return true;
  }

  return false;
}

bool delMovie(int userID, int rating) {
  if (!validBounds(userID, rating))
    return false;

  vector <int> temp;
  temp.clear();

  bool check = false;
  int vSize = tab[userID].filmList.size();
  for (int i = 0; i < vSize; i++) {
    if (tab[userID].filmList[i] != rating) {
      temp.push_back(tab[userID].filmList[i]);
    } else {
      check = true;
    }

  }

  if (check) {
    tab[userID].filmList = temp;
    return true;
  }

  return false;
}

vector <int> ans;

void marathon_pom(int max_p, int userID) {
  int max_u = -1;
  int fSize = tab[userID].filmList.size();
  for (int i = 0; i < fSize; i++) {
    max_u = max(max_u, tab[userID].filmList[i]);
    if (tab[userID].filmList[i] > max_p)
      ans.push_back(tab[userID].filmList[i]);
  }

  //printf("sss\n");

  int vSize = tab[userID].childList.size();
  for (int i = 0; i < vSize; i++) {
    marathon_pom(max_u, tab[userID].childList[i]);
  }
}

bool opsort(int i, int j) {
  return (i > j);
}

bool marathon(int userID, int k) {
  if (!validBounds(userID, k))
    return false;

  ans.clear();
  ans.push_back(-1);
  //printf("s\n");

  int max_u = -1;
  int fSize = tab[userID].filmList.size();
  for (int i = 0; i < fSize; i++) {
    max_u = max(max_u, tab[userID].filmList[i]);
    ans.push_back(tab[userID].filmList[i]);
  }
  //printf("s\n");

  int vSize = tab[userID].childList.size();
  for (int i = 0; i < vSize; i++) {
    //printf("%d\n", tab[userID].childList[i]);
    marathon_pom(max_u, tab[userID].childList[i]);
  }


  sort(ans.begin(), ans.end(), opsort);
  vector <int>::iterator it;
  it = unique(ans.begin(), ans.end());
  ans.resize(distance(ans.begin(), it));


  if (ans.size() == 0 || ans[0] == -1 || k == 0) {
    cout << "NONE" << endl;
  } else {
    int i = 0;
    int aSize = ans.size();
    while (ans[i] != -1 && i < aSize && i < k) {
      if (i + 1 == aSize || ans[i+1] == -1 || i + 1 == k) {
        cout << ans[i] << endl;
      } else {
        cout << ans[i] << " ";
      }
      i++;
    }
  }

  return true;
}

int main() {
  for(int i = 0; i < 65536; i++) {
    tab[i].childList.clear();
    tab[i].filmList.clear();
    tab[i].intree = false;
  }

  tab[0].intree = true;

  char *input = (char *)malloc(sizeof(char) * MAX_INPUT_SIZE);
  //int count = 1;

  if (input == NULL)
    exit(EXIT_STATUS);

  while(scanf("%s", input) != EOF) {
    //printf("Operation %d\n", count);
    //count++;
    //printf("Input : %s\n", input);
    if (strcmp(input, "\n") == 0)
      continue;
    else if (strncmp(input, "#", 1) == 0) {
      // get and ignore one line
      //fgets(input, sizeof(char) * MAX_INPUT_SIZE, stdin);
      while(fgetc(stdin) != '\n'){};
      //printf("one line : %s\n", input);
      //getline(&input, &temp, stdin);
    } else if (strcmp(input, "addUser") == 0) {
      int parentID, userID;
      bool err = false;
      if (!scanf("%d %d",&parentID, &userID))
          err = true;

      if (!userAdd(parentID, userID) || err) {
        // prompt about failure to stderr
        fprintf(stderr, "%s\n", "ERROR");
      } else {
        // adds the node
        fprintf(stdout, "%s\n", "OK");
      }
    } else if (strcmp(input, "delUser") == 0) {
      int userID;
      bool err = false;
      if (!scanf("%d", &userID))
          err = true;

      if (!delUser(userID) || err) {
        // prompt about failure to stderr
        fprintf(stderr, "%s\n", "ERROR");
      } else {
        // adds the node
        printf("OK\n");
      }
    } else if (strcmp(input, "addMovie") == 0) {
      int userID, movieRating;
      bool err = false;
      if (!scanf("%d %d",&userID, &movieRating))
          err = true;

      if (!addMovie(userID, movieRating) || err) {
        // prompt about failure to stderr
        fprintf(stderr, "%s\n", "ERROR");
      } else {
        // adds the node
        printf("OK\n");
      }
    } else if (strcmp(input, "delMovie") == 0) {
      int userID, movieRating;
      bool err = false;
      if (!scanf("%d %d",&userID, &movieRating))
          err = true;

      if (!delMovie(userID, movieRating) || err) {
        // prompt about failure to stderr
        fprintf(stderr, "%s\n", "ERROR");
      } else {
        // adds the node
        printf("OK\n");
      }
    } else if (strcmp(input, "marathon") == 0) {
      int userID, k;
      bool err = false;
      if (!scanf("%d %d",&userID, &k))
          err = true;

      if (!marathon(userID, k) || err) {
        // prompt about failure to stderr
        fprintf(stderr, "%s\n", "ERROR");
      }
    } else {
      // input is invalid
      // get and ignore one line
      //fgets(input, sizeof(char) * MAX_INPUT_SIZE, stdin);
      while(fgetc(stdin) != '\n'){};
      fprintf(stderr, "%s\n", "ERROR");
    }
  }

  //printf("%d\n", tab[2].childList[0]);

  free(input);
  return 0;
}
