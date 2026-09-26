#ifndef LIST_H
#define LIST_H

typedef struct Item
{
	struct Item* next;
	struct Item* prev;
} Item;

typedef struct List
{
	Item* head;
	Item* tail;
} List;

void Add(List* list, Item* item);
void Delete(List* list, int number);
Item* GetItem(List* list, int number);
Item* Remove(List* list, int number);
void Insert(List* list, Item* item, int number);
int Count(List* list);
void Clear(List* list);
int GetIndex(List* list, Item* item);

#endif
