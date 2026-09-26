#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


#include "subj.h"

void PrintList(List* list);

int main(void)
{
	List list;
	int choice;
	int number;
	list.head = NULL;
	list.tail = NULL;

	Item* item;

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
		printf("10. PrintChessList\n");
		printf("11. FindCanAttack\n");
		printf("12. FindCannotAttack\n");
		printf("13. FindByColor\n");
		printf("14. SortByRank\n");
		printf("0. EXIT\n");
		printf("Vvedite vibor: ");
		if (scanf("%d", &choice) != 1)
		{
			printf("ERROR: Nuzhno chislo\n");
			break;
		}

		if ((choice >= 2 && choice <= 5) || choice == 8)
		{
			printf("Vvedite nomer elementa (s 0): ");
			if (scanf("%d", &number) != 1)
			{
				printf("ERROR: Nuzhno chislo\n");
				break;
			}

			if (number < 0)
			{
				printf("ERROR: Index must be >= 0\n");
				continue;
			}
		}

		switch (choice)
		{
		case 1:
		{
			int typeNumber;
			printf("Choose type:\n");
			printf("0 - KING\n");
			printf("1 - QUEEN\n");
			printf("2 - ROOK\n");
			printf("3 - BISHOP\n");
			printf("4 - KNIGHT\n");
			printf("5 - PAWN\n");
			

			if (scanf("%d", &typeNumber) != 1 ||
				typeNumber < KING || typeNumber > PAWN)
			{
				printf("ERROR: Invalid piece type\n");
				break;
			}

			BasePiece* piece = Create((PieceType)typeNumber);

			if (piece == NULL)
			{
				printf("Error\n");
				break;
			}

			if (InputPiece(piece) == 0)
			{
				printf("ERROR: Invalid color or coordinates\n");
				free(piece);
				break;
			}

			Add(&list, (Item*)piece);
			printf("Figure added\n");

			break;
		}

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
				PrintPiece((BasePiece*)item);
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
				free(item);
			}
			break;

		case 5:
		{
			int typeNumber;
			printf("Choose type:\n");
			printf("0 - KING\n");
			printf("1 - QUEEN\n");
			printf("2 - ROOK\n");
			printf("3 - BISHOP\n");
			printf("4 - KNIGHT\n");
			printf("5 - PAWN\n");
			

			if (scanf("%d", &typeNumber) != 1 ||
				typeNumber < KING || typeNumber > PAWN)
			{
				printf("ERROR: Invalid piece type\n");
				break;
			}

			BasePiece* piece = Create((PieceType)typeNumber);

			if (piece == NULL)
			{
				printf("Error\n");
				break;
			}

			if (InputPiece(piece) == 0)
			{
				printf("ERROR: Invalid color or coordinates\n");
				free(piece);
				break;
			}

			Insert(&list, (Item*)piece, number);
			printf("Figure inserted\n");

			break;
		}

		case 6:
			printf("%d\n", Count(&list));
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

		case 10:
			PrintChessList(&list);
			break;

		case 11:
		{
			int x;
			int y;

			printf("Enter x y (1-8): ");
			if (scanf("%d %d", &x, &y) != 2)
			{
				printf("ERROR:\n");
				break;
			}

			FindByAttack(&list, x, y, 1);
			break;
		}

		case 12:
		{
			int x;
			int y;

			printf("Enter x y (1-8): ");
			if (scanf("%d %d", &x, &y) != 2)
			{
				printf("ERROR:\n");
				break;
			}

			FindByAttack(&list, x, y, 0);
			break;
		}

		case 13:
		{
			int colorNumber;

			printf("Choose color:\n");
			printf("0 - WHITE\n");
			printf("1 - BLACK\n");
			if (scanf("%d", &colorNumber) != 1 ||
				colorNumber < WHITE || colorNumber > BLACK)
			{
				printf("ERROR: Invalid color\n");
				break;
			}

			FindByColor(&list, (Color)colorNumber);
			break;
		}

		case 14:
		{
			int porydok;

			printf("Choose order:\n");
			printf("-1 - KING to PAWN\n");
			printf("1 - PAWN to KING\n");
			if (scanf("%d", &porydok) != 1 ||
				(porydok != -1 && porydok != 1))
			{
				printf("ERROR: Invalid order\n");
				break;
			}

			SortByRank(&list, porydok);
			PrintChessList(&list);
			break;
		}

		case 0:
			printf("Goodbye!\n");
			break;

		default:
			printf("ERROR: Invalid choice\n");
		}
	} while (choice != 0);

	Clear(&list);
	return 0;
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
