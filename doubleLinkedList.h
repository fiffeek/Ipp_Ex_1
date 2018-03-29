#ifndef LIST_DOUBLE_SEEN
#define LIST_DOUBLE_SEEN

struct doubleList{
  short value;
  struct doubleList *next;
  struct doubleList *prev;
};

typedef struct doubleList BList;

extern BList* initBList(short value);

extern void addFrontBList(short value, BList **list);

extern bool isNullBList(BList *list);

extern void traverseBList(BList *list);

extern void deleteConnectBLists(BList *toDelete,
  BList *startList2, BList *endList2);

extern void specificDeletionInsideList(BList *firstList);

extern void addAfterFirstElemBList(short value, BList *list);

extern BList* getNextBList(BList *list);

extern BList* getPrevBList(BList *list);

extern short getValueBList(BList *list);

extern void freeBList(BList *front);

extern BList* nullBList();

#endif /* !FILE_SEEN */
