#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "subj.h"
#include <stdio.h>
#include <stdbool.h>
#include <iostream>


BasePiece::BasePiece(int x, int y, Color color)
    :x(x), y(y), color(color)
{
       
}

int BasePiece::getX()
{
    return x;
}

int BasePiece::getY()
{
    return y;
}

Color BasePiece::getColor()
{
    return color;
}

bool BasePiece::CanAttack(int x, int y)
{
    if (x < 1 || x > 8 || y < 1 || y > 8)
    {
        return false;
    }

    if (this->x == x && this->y == y)
    {
        return false;
    }

    return true;
}


bool King::CanAttack(int x, int y)
{
    if (!BasePiece::CanAttack(x, y))
    {
        return false;
    }

    if ((x >= this->x - 1 && x <= this->x + 1) &&
        (y >= this->y - 1 && y <= this->y + 1))
    {
        return true;
    }

    return false;
}


bool Queen::CanAttack(int x, int y)
{
    if (!BasePiece::CanAttack(x, y))
    {
        return false;
    }

    if ((this->x == x || this->y == y) || (abs(x - this->x) == abs(y - this->y)))
    {
        return true;
    }

    return false;
}

bool Rook::CanAttack(int x, int y)
{
    if (!BasePiece::CanAttack(x, y))
    {
        return false;
    }

    if (this->x == x || this->y == y)
    {
        return true;
    }

    return false;
}

bool Bishop::CanAttack(int x, int y)
{
    if (!BasePiece::CanAttack(x, y))
    {
        return false;
    }

    if (abs(x - this->x) == abs(y - this->y))
    {
        return true;
    }

    return false;
}

bool Knight::CanAttack(int x, int y)
{
    if (!BasePiece::CanAttack(x, y))
    {
        return false;
    }

    int dx = abs(x - this->x);
    int dy = abs(y - this->y);

    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))
    {
        return true;
    }

    return false;
}

bool Pawn::CanAttack(int x, int y)
{
    if (!BasePiece::CanAttack(x, y))
    {
        return false;
    }

    if (abs(x - this->x) != 1)
    {
        return false;
    }

    if (this->color == WHITE && y == this->y + 1)
    {
        return true;
    }

    if (this->color == BLACK && y == this->y - 1)
    {
        return true;
    }

    return false;
}

King::King(int x, int y, Color color) : BasePiece(x, y, color)
{

}

Queen::Queen(int x, int y, Color color) : BasePiece(x, y, color)
{

}

Rook::Rook(int x, int y, Color color) : BasePiece(x, y, color)
{

}

Bishop::Bishop(int x, int y, Color color) : BasePiece(x, y, color)
{

}

Knight::Knight(int x, int y, Color color) : BasePiece(x, y, color)
{

}

Pawn::Pawn(int x, int y, Color color) : BasePiece(x, y, color)
{

}

std::string King::getName()
{
    return "King";
}

std::string Queen::getName()
{
    return "Queen";
}

std::string Rook::getName()
{
    return "Rook";
}

std::string Bishop::getName()
{
    return "Bishop";
}

std::string Knight::getName()
{
    return "Knight";
}

std::string Pawn::getName()
{
    return "Pawn";
}

void PrintPiece(BasePiece* piece)
{
    printf("--Piece--\n");
    std::cout << "type: " << piece->getName() << std::endl;
    std::cout << "color: " << piece->getColor() << std::endl;
    std::cout << "X: " << piece->getX() << std::endl;
    std::cout << "Y: " << piece->getY() << std::endl;
}

void ChessList::Print()
{
    const Item* cur = head;

    while (cur != nullptr)
    {
        PrintPiece((BasePiece*)cur);
        cur = cur->Next();
    }
}

void ChessList::FindByAttack(int x, int y, bool mustAttack)
{
    if (x < 1 || x > 8 || y < 1 || y > 8)
    {
        printf("Invalid coord\n");
        return;
    }

    const Item* cur = head;
    int count = 0;

    while (cur != NULL)
    {
        BasePiece* piece = (BasePiece*)cur;

        if (piece->CanAttack(x, y) == mustAttack)
        {
            PrintPiece(piece);
            count++;
        }

        cur = cur->Next();
    }

    if (count == 0)
    {
        printf("No pieces found\n");
    }
}

void ChessList::FindByColor(Color color)
{
    const Item* cur = head;
    int count = 0;

    while (cur != NULL)
    {
        BasePiece* piece = (BasePiece*)cur;

        if (piece->getColor() == color)
        {
            PrintPiece(piece);
            count++;
        }

        cur = cur->Next();
    }

    if (count == 0)
    {
        printf("No pieces found\n");
    }
}

int GetTypeByName(const std::string &name)
{
    if (name == "Pawn")
        return 1;
    else if (name == "Knight")
        return 2;
    else if (name == "Bishop")
        return 3;
    else if (name == "Rook")
        return 4;
    else if (name == "Queen")
        return 5;
    else if (name == "King")
        return 6;

    return 0;
}

bool condition(BasePiece* cur, BasePiece* next)
{
    return GetTypeByName(cur->getName()) < GetTypeByName(next->getName());
}

void bubble(ChessList* list, int porydok)
{
    int count = list->Count();

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            BasePiece* cur = (BasePiece*)list->GetItem(j);
            BasePiece* next = (BasePiece*)list->GetItem(j + 1);

            if ((porydok >= 0 && condition(cur, next)) ||
                (porydok < 0 && !condition(cur, next)))
            {
                list->Insert(list->Remove(j), j + 1);
            }
        }
    }
}

void ChessList::SortByRank(int porydok)
{
    if (head == NULL)
    {
        return;
    }

    bubble(this, porydok);
}
