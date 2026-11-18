#include "subj.h"

#include <cstdlib>
#include <iostream>

namespace
{
    bool IsOnBoard(int x, int y)
    {
        return x >= 1 && x <= 8 && y >= 1 && y <= 8;
    }

    class King : public BasePiece
    {
    public:
        std::string GetName() const override
        {
            return "King";
        }

        bool CanAttack(int targetX, int targetY) const override
        {
            if (!BasePiece::CanAttack(targetX, targetY))
            {
                return false;
            }
            return std::abs(targetX - x) <= 1 && std::abs(targetY - y) <= 1;
        }

        PieceType GetType() const override
        {
            return PieceType::King;
        }
    };

    class Queen : public BasePiece
    {
    public:
        std::string GetName() const override
        {
            return "Queen";
        }

        bool CanAttack(int targetX, int targetY) const override
        {
            if (!BasePiece::CanAttack(targetX, targetY))
            {
                return false;
            }
            return targetX == x || targetY == y
                || std::abs(targetX - x) == std::abs(targetY - y);
        }

        PieceType GetType() const override
        {
            return PieceType::Queen;
        }
    };

    class Rook : public BasePiece
    {
    public:
        std::string GetName() const override
        {
            return "Rook";
        }

        bool CanAttack(int targetX, int targetY) const override
        {
            if (!BasePiece::CanAttack(targetX, targetY))
            {
                return false;
            }
            return targetX == x || targetY == y;
        }

        PieceType GetType() const override
        {
            return PieceType::Rook;
        }
    };

    class Bishop : public BasePiece
    {
    public:
        std::string GetName() const override
        {
            return "Bishop";
        }

        bool CanAttack(int targetX, int targetY) const override
        {
            if (!BasePiece::CanAttack(targetX, targetY))
            {
                return false;
            }
            return std::abs(targetX - x) == std::abs(targetY - y);
        }

        PieceType GetType() const override
        {
            return PieceType::Bishop;
        }
    };

    class Knight : public BasePiece
    {
    public:
        std::string GetName() const override
        {
            return "Knight";
        }

        bool CanAttack(int targetX, int targetY) const override
        {
            if (!BasePiece::CanAttack(targetX, targetY))
            {
                return false;
            }
            const int dx = std::abs(targetX - x);
            const int dy = std::abs(targetY - y);
            return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
        }

        PieceType GetType() const override
        {
            return PieceType::Knight;
        }
    };

    class Pawn : public BasePiece
    {
    public:
        std::string GetName() const override
        {
            return "Pawn";
        }

        bool CanAttack(int targetX, int targetY) const override
        {
            if (!BasePiece::CanAttack(targetX, targetY))
            {
                return false;
            }
            const int direction = color == Color::White ? 1 : -1;
            return std::abs(targetX - x) == 1 && targetY == y + direction;
        }

        PieceType GetType() const override
        {
            return PieceType::Pawn;
        }
    };
}



BasePiece* BasePiece::Create(PieceType type)
{
    switch (type)
    {
    case PieceType::King:   return new King();
    case PieceType::Queen:  return new Queen();
    case PieceType::Rook:   return new Rook();
    case PieceType::Bishop: return new Bishop();
    case PieceType::Knight: return new Knight();
    case PieceType::Pawn:   return new Pawn();
    }
    return nullptr;
}


bool BasePiece::CanAttack(int targetX, int targetY) const
{
    if (!IsOnBoard(targetX, targetY) || (x == targetX && y == targetY))
    {
        return false;
    }
    return true;
}

Color BasePiece::GetColor() const
{
    return color;
}

bool BasePiece::Input()
{
    int newX, newY, colorNumber;
    std::cout << GetName() << " x y (1-8): ";
    if (!(std::cin >> newX >> newY) || !IsOnBoard(newX, newY))
    {
        std::cout << "Invalid coordinates.\n";
        return false;
    }

    std::cout << "Color (0 - White, 1 - Black): ";
    if (!(std::cin >> colorNumber) || (colorNumber != 0 && colorNumber != 1))
    {
        std::cout << "Invalid color.\n";
        return false;
    }

    x = newX;
    y = newY;
    color = static_cast<Color>(colorNumber);
    return true;
}

void BasePiece::Print() const
{
    std::cout << GetName() << " (" << x << ", " << y << "), "
        << (color == Color::White ? "White" : "Black") << '\n';
}

BasePiece* ChessList::GetPiece(int index)
{
    return dynamic_cast<BasePiece*>(GetItem(index));
}

void ChessList::Print() const
{
    if (!Head())
    {
        std::cout << "List is empty.\n";
        return;
    }

    int index = 0;
    for (const Item* item = Head(); item; item = item->Next(), ++index)
    {
        if (const BasePiece* piece = dynamic_cast<const BasePiece*>(item))
        {
            std::cout << index << ". ";
            piece->Print();
        }
    }
}

void ChessList::FindByColor(Color color) const
{
    bool found = false;
    for (const Item* item = Head(); item; item = item->Next())
    {
        const BasePiece* piece = dynamic_cast<const BasePiece*>(item);
        if (piece && piece->GetColor() == color)
        {
            piece->Print();
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No pieces found.\n";
    }
}

void ChessList::FindByAttack(int x, int y, bool mustAttack) const
{
    if (!IsOnBoard(x, y))
    {
        std::cout << "Invalid coordinates.\n";
        return;
    }

    bool found = false;
    for (const Item* item = Head(); item; item = item->Next())
    {
        const BasePiece* piece = dynamic_cast<const BasePiece*>(item);
        if (piece && piece->CanAttack(x, y) == mustAttack)
        {
            piece->Print();
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No pieces found.\n";
    }
}

void ChessList::SortByRank(bool ascending)
{
    const int count = Count();
    for (int end = count - 1; end > 0; --end)
    {
        bool swapped = false;
        for (int i = 0; i < end; ++i)
        {
            const BasePiece* left = GetPiece(i);
            const BasePiece* right = GetPiece(i + 1);
            if (!left || !right)
            {
                continue;
            }

            const PieceType leftType = left->GetType();
            const PieceType rightType = right->GetType();
            if (ascending ? leftType > rightType : leftType < rightType)
            {
                // Move the left node past the right one using the List interface.
                Insert(Remove(i), i + 1);
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}
