#include <stdlib.h>
#include "list.h"

void Add(List* list, Item* item)
{
	if (list == NULL || item == NULL)
	{
		return;
	}
	item->next = NULL;
	item->prev = list->tail;
	if (list->head == NULL)
	{
		list->head = item;
		list->tail = item;
	}
	else
	{
		list->tail->next = item;
		item->prev = list->tail;
		list->tail = item;
	}
}

int Count(List* list)
{
	if (list == NULL)
	{
		return 0;
	}

	int count = 0;
	Item* cur = list->head;

	while (cur != NULL)
	{
		count += 1;
		cur = cur->next;
	}

	return count;
}

Item* GetItem(List* list, int number)
{
	if (list == NULL || number < 0)
	{
		return NULL;
	}

	Item* cur = list->head;
	for (int i = 0; i < number; i++)
	{
		if (cur == NULL)
		{
			return NULL;
		}
		cur = cur->next;
	}

	return cur;
}

Item* Remove(List* list, int number)
{
	Item* cur = GetItem(list, number);
	if (cur == NULL)
	{
		return NULL;
	}

	Item* prev = cur->prev;
	Item* next = cur->next;

	if (prev == NULL)
	{
		list->head = next;
	}
	else
	{
		prev->next = next;
	}

	if (next == NULL)
	{
		list->tail = prev;
	}
	else
	{
		next->prev = prev;
	}

	cur->prev = NULL;
	cur->next = NULL;

	return cur;
}

void Delete(List* list, int number)
{
	Item* item = Remove(list, number);
	free(item);
}

int Insert(List* list, Item* item, int number)
{
	if (list == NULL || item == NULL || number < 0)
	{
		return 0;
	}

	if (number == Count(list))
	{
		Add(list, item);
		return 1;
	}

	Item* cur = GetItem(list, number);
	if (cur == NULL)
	{
		return 0;
	}

	item->prev = cur->prev;
	item->next = cur;

	if (cur->prev == NULL)
	{
		list->head = item;
	}
	else
	{
		cur->prev->next = item;
	}

	cur->prev = item;
	return 1;
}

int GetIndex(List* list, Item* item)
{
	if (list == NULL || item == NULL)
	{
		return -1;
	}

	Item* cur = list->head;
	int number = 0;
	while (cur != NULL)
	{
		if (cur == item)
		{
			return number;
		}
		cur = cur->next;
		number++;
	}

	return -1;
}

void Clear(List* list)
{
	if (list == NULL)
	{
		return;
	}

	while (list->head != NULL)
	{
		Delete(list, 0);
	}
}
