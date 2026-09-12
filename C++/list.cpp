#include <cstdio>
#include "list.h"

void Add(List* list, Item* item)
{
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
	printf_s("+1");
}

int Count(List* list)
{
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
	if (number <= 0)
	{
		printf("Ne Popal\n");
		return NULL;
	}

	Item* cur = list->head;
	for (int i = 1; i < number; i++)
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
	delete item;
}

void Insert(List* list, Item* item, int number)
{
	if (list == NULL || item == NULL)
	{
		return;
	}

	Item* cur = GetItem(list, number);
	if (cur == NULL)
	{
		return;
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
}

int GetIndex(List* list, Item* item)
{
	if (list == NULL || item == NULL)
	{
		return -1;
	}

	Item* cur = list->head;
	int number = 1;
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
		Delete(list, 1);
	}
}
