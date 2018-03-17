#ifndef LIST_DOUBLE_SEEN
#define LIST_DOUBLE_SEEN

struct doubleList{
  int value;
  struct doubleList *next;
  struct doubleList *prev;
};

typedef struct doubleList BList;

extern BList* initBList(int value);

extern void addFrontBList(int value, BList **list);

extern bool isNullBList(BList *list);

extern void traverseBList(BList *list);

extern void deleteConnectBLists(BList *toDelete,
  BList *startList2, BList *endList2);

extern void addAfterFirstElemBList(int value, BList *list);

extern BList* getNextBList(BList *list);

extern BList* getPrevBList(BList *list);

extern int getValueBList(BList *list);

extern void freeBList(BList *front);

extern BList* nullBList();

#endif /* !FILE_SEEN */
