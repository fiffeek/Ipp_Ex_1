#ifndef LIST_SEEN
#define LIST_SEEN

struct List{
  int value;
  struct List *next;
};

typedef struct List TList;

extern TList* initList(int value);

extern void addFront(int value, TList **list);

extern void setValue(TList *list, int value);

extern TList* getNext(TList *list);

extern int getValue(TList *list);

extern bool isNull(TList *list);

extern bool addSorted(int value, TList **list);

extern void connectLists(TList *endfirst, TList *frontsecond);

extern void freeTList(TList *front);

extern void traverseList(TList *list);

extern bool deleteElem(TList **list, int elem);

extern TList* nullTList();

#endif /* !FILE_SEEN */
