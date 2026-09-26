#ifndef SUBJ_H
#define SUBJ_H

#include "list.h"

typedef enum
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
} PieceType;

typedef enum
{
    WHITE,
    BLACK
} Color;

typedef struct
{
    struct Item* next;
    struct Item* prev;

    int x;
    int y;

    Color color;
    PieceType type;
} BasePiece;


BasePiece* Create(PieceType type);
int InputPiece(BasePiece* piece);

void PrintChessList(List* list);
void SortByRank(List* list, int porydok);
void FindByColor(List* list, Color color);
void FindByAttack(List* list, int x, int y, int mustAttack);
void PrintPiece(BasePiece* piece);
int CanAttack(BasePiece* piece, int x, int y);

#endif
