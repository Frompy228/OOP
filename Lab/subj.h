#pragma once

#include "list.h"

enum class PieceType { Pawn, Knight, Bishop, Rook, Queen, King };
enum class Color { White, Black };

class BasePiece : public Item
{
public:
    BasePiece(const BasePiece&) = delete;
    BasePiece& operator=(const BasePiece&) = delete;

    static BasePiece* Create(PieceType type);
    virtual bool Input() = 0;
    virtual void Print() const = 0;
    virtual bool CanAttack(int targetX, int targetY) const;
    virtual PieceType GetType() const = 0;
    Color GetColor() const;

protected:
    BasePiece() = default;
    bool ReadFields(const char* name);
    void PrintFields(const char* name) const;

    int x = 1;
    int y = 1;
    Color color = Color::White;

};

class ChessList : public List
{
public:
    ChessList() = default;
    ChessList(const ChessList&) = delete;
    ChessList& operator=(const ChessList&) = delete;

    BasePiece* GetPiece(int index);

    void Print() const;
    void FindByColor(Color color) const;
    void FindByAttack(int x, int y, bool mustAttack) const;
    void SortByRank(bool ascending);
};
