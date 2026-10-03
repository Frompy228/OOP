#include <stdlib.h>
#include "list.h"
#define _CRT_SECURE_NO_WARNINGS

void List::Add(Item* item)
{
	if (item == NULL)
	{
		return;
	}
	item->next = NULL;
	item->prev = tail;
	if (head == NULL)
	{
		head = item;
		tail = item;
	}
	else
	{
		tail->next = item;
		item->prev = tail;
		tail = item;
	}
}

int List::Count()
{
	int count = 0;
	Item* cur = head;

	while (cur != NULL)
	{
		count += 1;
		cur = cur->next;
	}

	return count;
}

Item* List::GetItem(int number)
{
	if (number < 0)
	{
		return NULL;
	}

	Item* current = head;

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

Item* List::Remove(int number)
{
	Item* cur = GetItem(number);
	if (cur == NULL)
	{
		return NULL;
	}

	Item* prev = cur->prev;
	Item* next = cur->next;

	if (prev == NULL)
	{
		head = next;
	}
	else
	{
		prev->next = next;
	}

	if (next == NULL)
	{
		tail = prev;
	}
	else
	{
		next->prev = prev;
	}

	cur->prev = NULL;
	cur->next = NULL;

	return cur;
}

void List::Delete(int number)
{
	Item* item = Remove(number);
	delete item;
}

void List::Insert(Item* item, int number)
{
	if (item == NULL)
	{
		return;
	}

	Item* current = GetItem(number);

	if (current == NULL)
	{
		Add(item);
		return;
	}

	if (current == head)
	{
		item->prev = NULL;
		item->next = current;

		current->prev = item;
		head = item;

		return;
	}

	item->prev = current->prev;
	item->next = current;

	current->prev->next = item;
	current->prev = item;
}

int List::GetIndex(Item* item)
{
	if (item == NULL)
	{
		return -1;
	}

	Item* cur = head;
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

void List::Clear()
{
	while (head != NULL)
	{
		Delete(0);
	}
}

const Item* Item::Next() const
{
	return next;
}

const Item* Item::Prev() const
{
	return prev;
}

Item::~Item()
{
	next = prev = nullptr;
}

List::~List()
{
	Clear();
}

const Item* List::Head() const
{
	return head;
}

const Item* List::Tail() const
{
	return tail;
}

