#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "subj.h"
#include <stdio.h>
#include <stdbool.h>


typedef struct
{
    struct Item* next;
    struct Item* prev;

    int x;
    int y;

    Color color;
    PieceType type;
} King;

typedef struct
{
    struct Item* next;
    struct Item* prev;

    int x;
    int y;

    Color color;
    PieceType type;
} Queen;

typedef struct
{
    struct Item* next;
    struct Item* prev;

    int x;
    int y;

    Color color;
    PieceType type;
} Rook;

typedef struct
{
    struct Item* next;
    struct Item* prev;

    int x;
    int y;

    Color color;
    PieceType type;
} Bishop;

typedef struct
{
    struct Item* next;
    struct Item* prev;

    int x;
    int y;

    Color color;
    PieceType type;
} Knight;

typedef struct
{
    struct Item* next;
    struct Item* prev;

    int x;
    int y;

    Color color;
    PieceType type;
} Pawn;

BasePiece* Create(PieceType type)
{
    BasePiece* piece = NULL;

    switch (type)
    {
    case KING:
        piece = calloc(1, sizeof(King));
        break;
    case QUEEN:
        piece = calloc(1, sizeof(Queen));
        break;
    case ROOK:
        piece = calloc(1, sizeof(Rook));
        break;
    case BISHOP:
        piece = calloc(1, sizeof(Bishop));
        break;
    case KNIGHT:
        piece = calloc(1, sizeof(Knight));
        break;
    case PAWN:
        piece = calloc(1, sizeof(Pawn));
        break;
    default:
        return NULL;
    }

    if (piece)
    {
        piece->type = type;
    }

    return piece;
}

int InputPiece(BasePiece* piece)
{
    int colorNumber;
    int x;
    int y;

    if (piece == NULL)
    {
        return 0;
    }

    printf("Choose color:\n0 - WHITE\n1 - BLACK\n");
    scanf("%d", &colorNumber);
    printf("Enter x y (1-8): ");
    scanf("%d %d", &x, &y);
    piece->color = (Color)colorNumber;
    piece->x = x;
    piece->y = y;
    return 1;
}

void PrintPiece(BasePiece* piece)
{
    printf("--Piece--\n");

    switch (piece->type)
    {
    case KING:
        printf("Type: King\n");
        break;
    case QUEEN:
        printf("Type: Queen\n");
        break;
    case ROOK:
        printf("Type: Rook\n");
        break;
    case BISHOP:
        printf("Type: Bishop\n");
        break;
    case KNIGHT:
        printf("Type: Knight\n");
        break;
    case PAWN:
        printf("Type: Pawn\n");
        break;
    default:
        printf("Type: Unknown\n");
    }
    printf("Color: %d\n", piece->color);
    printf("X: %d\n", piece->x);
    printf("Y: %d\n", piece->y);
}

void PrintChessList(List* list)
{
    Item* cur = list->head;

    while (cur != NULL)
    {
        PrintPiece((BasePiece*)cur);
        cur = cur->next;
    }
}

bool CanAttackRook(Rook* piece, int x, int y)
{
    if (piece->x == x && piece->y == y)
    {
        return false;
    }

    if (piece->x == x || piece->y == y)
    {
        return true;
    }

    return 0;
}

bool CanAttackKing(King* piece, int x, int y)
{
    if (piece->x == x && piece->y == y)
    {
        return false;
    }

    if ((x >= piece->x - 1 && x <= piece->x + 1) &&
        (y >= piece->y - 1 && y <= piece->y + 1))
    {
        return true;
    }

    return false;
}

bool CanAttackQueen(Queen* piece, int x, int y)
{
    if (piece->x == x && piece->y == y)
    {
        return false;
    }

    if ((piece->x == x || piece->y == y) || (abs(x - piece->x) == abs(y - piece->y)))
    {
        return true;
    }

    return false;
}

bool CanAttackBishop(Bishop* piece, int x, int y)
{
    if (piece->x == x && piece->y == y)
    {
        return false;
    }

    if (abs(x - piece->x) == abs(y - piece->y))
    {
        return true;
    }

    return false;
}

bool CanAttackKnight(Knight* piece, int x, int y)
{
    int dx = abs(x - piece->x);
    int dy = abs(y - piece->y);

    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))
    {
        return true;
    }

    return false;
}

bool CanAttackPawn(Pawn* piece, int x, int y)
{
    if (abs(x - piece->x) != 1)
    {
        return false;
    }

    if (piece->color == WHITE && y == piece->y + 1)
    {
        return true;
    }

    if (piece->color == BLACK && y == piece->y - 1)
    {
        return true;
    }

    return false;
}

int CanAttack(BasePiece* piece, int x, int y)
{
    if (piece == NULL)
    {
        return 0;
    }

    if (x < 1 || x > 8 || y < 1 || y > 8)
    {
        return 0;
    }

    switch (piece->type)
    {
    case KING:
        return CanAttackKing((King*)piece, x, y);

    case QUEEN:
        return CanAttackQueen((Queen*)piece, x, y);

    case ROOK:
        return CanAttackRook((Rook*)piece, x, y);

    case BISHOP:
        return CanAttackBishop((Bishop*)piece, x, y);

    case KNIGHT:
        return CanAttackKnight((Knight*)piece, x, y);

    case PAWN:
        return CanAttackPawn((Pawn*)piece, x, y);

    default:
        return 0;
    }
}

void FindByAttack(List* list, int x, int y, int mustAttack)
{
    if (list == NULL)
    {
        return;
    }

    if (x < 1 || x > 8 || y < 1 || y > 8)
    {
        printf("Invalid coord\n");
        return;
    }

    Item* cur = list->head;
    int count = 0;

    while (cur != NULL)
    {
        BasePiece* piece = (BasePiece*)cur;

        if (CanAttack(piece, x, y) == mustAttack)
        {
            PrintPiece(piece);
            count++;
        }

        cur = cur->next;
    }

    if (count == 0)
    {
        printf("No pieces found\n");
    }
}

void FindByColor(List* list, Color color)
{
    if (list == NULL)
    {
        return;
    }

    Item* cur = list->head;
    int count = 0;

    while (cur != NULL)
    {
        BasePiece* piece = (BasePiece*)cur;

        if (piece->color == color)
        {
            PrintPiece(piece);
            count++;
        }

        cur = cur->next;
    }

    if (count == 0)
    {
        printf("No pieces found\n");
    }
}

bool condition(List* list, BasePiece* cur, BasePiece* next)
{
    if (cur->type < next->type)
    {
        return true;
    }

    return false;
}

void bubble(List* list, int porydok)
{
    int count = Count(list);

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            BasePiece* cur = (BasePiece*)GetItem(list, j);
            BasePiece* next = (BasePiece*)GetItem(list, j + 1);

            if ((porydok >= 0 && condition(list, cur, next)) ||
                (porydok < 0 && !condition(list, cur, next)))
            {
                Insert(list, Remove(list, j), j + 1);
            }
        }
    }
}

void SortByRank(List* list, int porydok)
{
    if (list == NULL || list->head == NULL)
    {
        return;
    }

    bubble(list, porydok);
}
