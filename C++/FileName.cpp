#include <cstdio>
#include "list.h"

void PrintList(List* list);

int main()
{
	List list;
	int choice;
	int number;
	Item* item;
	list.head = NULL;
	list.tail = NULL;

	do
	{
		printf("\n===== MENU =====\n");
		printf("1. ADD\n");
		printf("2. DELETE\n");
		printf("3. GetItem\n");
		printf("4. Remove\n");
		printf("5. Insert\n");
		printf("6. Count\n");
		printf("7. Clear\n");
		printf("8. GetIndex\n");
		printf("9. PrintList\n");
		printf("0. EXIT\n");
		printf_s("Vvedite vibor: ");
		if (scanf_s("%d", &choice) != 1)
		{
			printf("ERROR: Nuzhno chislo\n");
			break;
		}

		if ((choice >= 2 && choice <= 5) || choice == 8)
		{
			printf("Vvedite nomer elementa (s 1): ");
			if (scanf_s("%d", &number) != 1)
			{
				printf("ERROR: Nuzhno chislo\n");
				break;
			}
		}

		switch (choice)
		{
		case 1:
			Add(&list, new Item{ NULL, NULL });
			break;

		case 2:
			Delete(&list, number);
			break;

		case 3:
			item = GetItem(&list, number);
			if (item == NULL)
			{
				printf("Element ne naiden\n");
			}
			else
			{
				printf("Item: %p  prev: %p  next: %p\n", item, item->prev, item->next);
			}
			break;

		case 4:
			item = Remove(&list, number);
			if (item == NULL)
			{
				printf("Element ne naiden\n");
			}
			else
			{
				printf("Removed: %p  prev: %p  next: %p\n", item, item->prev, item->next);
				delete item;
			}
			break;

		case 5:
			if (GetItem(&list, number) == NULL)
			{
				printf("Element ne naiden\n");
			}
			else
			{
				item = new Item{ NULL, NULL };
				Insert(&list, item, number);
				printf("Vstavlen pered elementom %d\n", number);
			}
			break;

		case 6:
			printf_s("%d\n", Count(&list));
			break;

		case 7:
			Clear(&list);
			printf("List cleared\n");
			break;

		case 8:
			item = GetItem(&list, number);
			printf("Index: %d\n", GetIndex(&list, item));
			break;

		case 9:
			PrintList(&list);
			break;

		case 0:
			printf("Goodbye!\n");
			break;

		default:
			printf("ERROR: Invalid choice\n");
		}
	} while (choice != 0);

	Clear(&list);
}



void PrintList(List* list)
{
	printf("List: %p  Head: %p  Tail: %p\n", list, list->head, list->tail);
	printf("#\tp\t\t\tprev\t\t\tnext\n");

	int i = 0;
	Item* p = list->head;
	while (p != NULL)
	{
		printf("%d\t%p\t%p\t%p\n", i, p, p->prev, p->next);
		p = p->next;
		i++;
	}
}
