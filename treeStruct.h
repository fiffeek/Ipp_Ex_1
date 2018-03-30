#ifndef TREE_SEEN
#define TREE_SEEN

struct node;

typedef struct node Node;

extern void updatePointer(int index, Node *ptr);

extern Node* getPointer(int index);

extern bool isNullNode(int index);

extern void initNode(int number);

extern Node* getZeroPointer();

extern bool addChild(int parent, int current);

extern bool deleteChild(int current);

extern bool validBounds(int current, int rating);

extern bool addMovie(int current, int rating);

extern bool deleteMovie(int current, int rating);

extern void traverseNode(Node *ptr);

extern void freeTree(unsigned short val);

extern void traverseTree(Node *ptr);

extern bool bestMovies(int current, int k);

#endif /* !FILE_SEEN */
