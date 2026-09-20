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

	Item* current = list->head;

	for (int i = 0; i < number; i++)
	{
		if (current == NULL)
		{
			return NULL;
		}

		current = current->next;
	}

	return current;
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

void Insert(List* list, Item* item, int number)
{
	if (list == NULL || item == NULL)
	{
		return;
	}

	Item* current = GetItem(list, number);

	if (current == NULL)
	{
		Add(list, item);
		return;
	}

	if (current == list->head)
	{
		item->prev = NULL;
		item->next = current;

		current->prev = item;
		list->head = item;

		return;
	}

	item->prev = current->prev;
	item->next = current;

	current->prev->next = item;
	current->prev = item;
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
