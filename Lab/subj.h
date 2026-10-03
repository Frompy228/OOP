#pragma once

#include "list.h"
#include <stdbool.h>
#include <string>

typedef enum
{
    WHITE,
    BLACK
} Color;

class BasePiece : public Item
{
public:
    BasePiece(int x, int y, Color color);
    int getX();
    int getY();
    Color getColor();
    virtual bool CanAttack(int x, int y);
    virtual std::string getName() = 0;

protected:
    int x;
    int y;

    Color color;
    
};

class King : public BasePiece
{
public:
    King(int x, int y, Color color);
    std::string getName() override;
    bool CanAttack(int x, int y) override;
};

class Queen : public BasePiece
{
public:
    Queen(int x, int y, Color color);
    std::string getName() override;
    bool CanAttack(int x, int y) override;
};

class Rook : public BasePiece
{
public:
    Rook(int x, int y, Color color);
    std::string getName() override;
    bool CanAttack(int x, int y) override;
};

class Bishop : public BasePiece
{
public:
    Bishop(int x, int y, Color color);
    std::string getName() override;
    bool CanAttack(int x, int y) override;
};

class Knight : public BasePiece
{
public:
    Knight(int x, int y, Color color);
    std::string getName() override;
    bool CanAttack(int x, int y) override;
};

class Pawn : public BasePiece
{
public:
    Pawn(int x, int y, Color color);
    std::string getName() override;
    bool CanAttack(int x, int y) override;
};

class ChessList : public List
{
public:
    void Print();
    void SortByRank(int porydok);
    void FindByColor(Color color);
    void FindByAttack(int x, int y, bool mustAttack);
};

int InputPiece(BasePiece* piece);
void PrintPiece(BasePiece* piece);

