#ifndef LIST_DOUBLE_SEEN
#define LIST_DOUBLE_SEEN

struct doubleList{
  unsigned short value;
  struct doubleList *next;
  struct doubleList *prev;
};

typedef struct doubleList BList;

extern BList* initBList(unsigned short value, int *ret);

extern bool addFrontBList(unsigned short value, BList **list);

extern bool isNullBList(BList *list);

extern void traverseBList(BList *list);

extern void deleteConnectBLists(BList *toDelete,
  BList *startList2, BList *endList2);

extern void specificDeletionInsideList(BList *firstList);

extern bool addAfterFirstElemBList(unsigned short value, BList *list);

extern BList* getNextBList(BList *list);

extern BList* getPrevBList(BList *list);

extern unsigned short getValueBList(BList *list);

extern void freeBList(BList *front);

extern BList* nullBList();

#endif /* !FILE_SEEN */
