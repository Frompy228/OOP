#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "subj.h"
#include <iostream>
#define elif else if


void PrintList(List* list);

int main(void)
{
	ChessList list;
	int choice;
	int number;

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
			

			if (scanf("%d", &typeNumber) != 1)
			{
				printf("ERROR: Invalid piece type\n");
				break;
			}

			int x, y, colorInt;
			Color color;

			printf("Choose x y:\n");
			std::cin >> x >> y;

			printf("Choose color:\n");
			printf("0 - WHITE\n");
			printf("1 - BLACK\n");

			std::cin >> colorInt;
			color = (Color)colorInt;

			BasePiece* piece = nullptr;


			if (typeNumber == 0)
			{
				piece = new King(x, y, color);
			}
			elif (typeNumber == 1)
			{
				piece = new Queen(x, y, color);
			}
			elif (typeNumber == 2)
			{
				piece = new Rook(x, y, color);
			}
			elif (typeNumber == 3)
			{
				piece = new Bishop(x, y, color);
			}
			elif (typeNumber == 4)
			{
				piece = new Knight(x, y, color);
			}
			elif (typeNumber == 5)
			{
				piece = new Pawn(x, y, color);
			}



			if (piece == nullptr)
			{
				printf("Error\n");
				break;
			}


			list.Add((BasePiece*)piece);
			printf("Figure added\n");

			break;
		}

		case 2:
			list.Delete(number);
			break;

		case 3:
			item = list.GetItem(number);
			if (item == nullptr)
			{
				printf("Element ne naiden\n");
			}
			else
			{
				PrintPiece((BasePiece*)item);
			}
			break;

		case 4:
			item = list.Remove(number);
			if (item == nullptr)
			{
				printf("Element ne naiden\n");
			}
			else
			{
				printf("Removed: %p  prev: %p  next: %p\n", item, item->Prev(), item->Next());
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


			if (scanf("%d", &typeNumber) != 1)
			{
				printf("ERROR: Invalid piece type\n");
				break;
			}

			int x, y, colorInt;
			Color color;

			printf("Choose x y:\n");
			std::cin >> x >> y;

			printf("Choose color:\n");
			printf("0 - WHITE\n");
			printf("1 - BLACK\n");

			std::cin >> colorInt;
			color = (Color)colorInt;

			BasePiece* piece = nullptr;


			if (typeNumber == 0)
			{
				piece = new King(x, y, color);
			}
			elif(typeNumber == 1)
			{
				piece = new Queen(x, y, color);
			}
			elif(typeNumber == 2)
			{
				piece = new Rook(x, y, color);
			}
			elif(typeNumber == 3)
			{
				piece = new Bishop(x, y, color);
			}
			elif(typeNumber == 4)
			{
				piece = new Knight(x, y, color);
			}
			elif(typeNumber == 5)
			{
				piece = new Pawn(x, y, color);
			}


			if (piece == nullptr)
			{
				printf("Error\n");
				break;
			}


			list.Insert((Item*)piece, number);
			printf("Figure inserted\n");

			break;
		}

		case 6:
			printf("%d\n", list.Count());
			break;

		case 7:
			list.Clear();
			printf("List cleared\n");
			break;

		case 8:
			item = list.GetItem(number);
			printf("Index: %d\n", list.GetIndex(item));
			break;

		case 9:
			PrintList(&list);
			break;

		case 10:
			list.Print();
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

			list.FindByAttack(x, y, true);
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

			list.FindByAttack(x, y, false);
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

			list.FindByColor((Color)colorNumber);
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

			list.SortByRank(porydok);
			list.Print();
			break;
		}

		case 0:
			printf("Goodbye!\n");
			break;

		default:
			printf("ERROR: Invalid choice\n");
		}
	} while (choice != 0);

	list.Clear();
	return 0;
}



void PrintList(List* list)
{
	printf("List: %p  Head: %p  Tail: %p\n", list, list->Head(), list->Tail());
	printf("#\tp\t\t\tprev\t\t\tnext\n");

	int i = 0;
	const Item* p = list->Head();
	while (p != nullptr)
	{
		printf("%d\t%p\t%p\t%p\n", i, p, p->Prev(), p->Next());
		p = p->Next();
		i++;
	}
}
