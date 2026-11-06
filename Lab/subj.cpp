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
        King() : BasePiece(PieceType::King) {}
        bool Input() { return ReadFields("King"); }
        void Print() const { PrintFields("King"); }
        int GetRank() const { return 6; }

        bool CanAttack(int targetX, int targetY) const
        {
            return std::abs(targetX - x) <= 1 && std::abs(targetY - y) <= 1;
        }
    };

    class Queen : public BasePiece
    {
    public:
        Queen() : BasePiece(PieceType::Queen) {}
        bool Input() { return ReadFields("Queen"); }
        void Print() const { PrintFields("Queen"); }
        int GetRank() const { return 5; }

        bool CanAttack(int targetX, int targetY) const
        {
            return targetX == x || targetY == y
                || std::abs(targetX - x) == std::abs(targetY - y);
        }
    };

    class Rook : public BasePiece
    {
    public:
        Rook() : BasePiece(PieceType::Rook) {}
        bool Input() { return ReadFields("Rook"); }
        void Print() const { PrintFields("Rook"); }
        int GetRank() const { return 4; }

        bool CanAttack(int targetX, int targetY) const
        {
            return targetX == x || targetY == y;
        }
    };

    class Bishop : public BasePiece
    {
    public:
        Bishop() : BasePiece(PieceType::Bishop) {}
        bool Input() { return ReadFields("Bishop"); }
        void Print() const { PrintFields("Bishop"); }
        int GetRank() const { return 3; }

        bool CanAttack(int targetX, int targetY) const
        {
            return std::abs(targetX - x) == std::abs(targetY - y);
        }
    };

    class Knight : public BasePiece
    {
    public:
        Knight() : BasePiece(PieceType::Knight) {}
        bool Input() { return ReadFields("Knight"); }
        void Print() const { PrintFields("Knight"); }
        int GetRank() const { return 2; }

        bool CanAttack(int targetX, int targetY) const
        {
            const int dx = std::abs(targetX - x);
            const int dy = std::abs(targetY - y);
            return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
        }
    };

    class Pawn : public BasePiece
    {
    public:
        Pawn() : BasePiece(PieceType::Pawn) {}
        bool Input() { return ReadFields("Pawn"); }
        void Print() const { PrintFields("Pawn"); }
        int GetRank() const { return 1; }

        bool CanAttack(int targetX, int targetY) const
        {
            const int direction = color == Color::White ? 1 : -1;
            return std::abs(targetX - x) == 1 && targetY == y + direction;
        }
    };
}

BasePiece::BasePiece(PieceType type) : type(type)
{
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

bool BasePiece::Input()
{
    switch (type)
    {
    case PieceType::King:   return static_cast<King*>(this)->Input();
    case PieceType::Queen:  return static_cast<Queen*>(this)->Input();
    case PieceType::Rook:   return static_cast<Rook*>(this)->Input();
    case PieceType::Bishop: return static_cast<Bishop*>(this)->Input();
    case PieceType::Knight: return static_cast<Knight*>(this)->Input();
    case PieceType::Pawn:   return static_cast<Pawn*>(this)->Input();
    }
    return false;
}

void BasePiece::Print() const
{
    switch (type)
    {
    case PieceType::King:   static_cast<const King*>(this)->Print(); break;
    case PieceType::Queen:  static_cast<const Queen*>(this)->Print(); break;
    case PieceType::Rook:   static_cast<const Rook*>(this)->Print(); break;
    case PieceType::Bishop: static_cast<const Bishop*>(this)->Print(); break;
    case PieceType::Knight: static_cast<const Knight*>(this)->Print(); break;
    case PieceType::Pawn:   static_cast<const Pawn*>(this)->Print(); break;
    }
}

bool BasePiece::CanAttack(int targetX, int targetY) const
{
    if (!IsOnBoard(targetX, targetY) || (x == targetX && y == targetY))
    {
        return false;
    }

    switch (type)
    {
    case PieceType::King:   return static_cast<const King*>(this)->CanAttack(targetX, targetY);
    case PieceType::Queen:  return static_cast<const Queen*>(this)->CanAttack(targetX, targetY);
    case PieceType::Rook:   return static_cast<const Rook*>(this)->CanAttack(targetX, targetY);
    case PieceType::Bishop: return static_cast<const Bishop*>(this)->CanAttack(targetX, targetY);
    case PieceType::Knight: return static_cast<const Knight*>(this)->CanAttack(targetX, targetY);
    case PieceType::Pawn:   return static_cast<const Pawn*>(this)->CanAttack(targetX, targetY);
    }
    return false;
}

int BasePiece::GetRank() const
{
    switch (type)
    {
    case PieceType::King:   return static_cast<const King*>(this)->GetRank();
    case PieceType::Queen:  return static_cast<const Queen*>(this)->GetRank();
    case PieceType::Rook:   return static_cast<const Rook*>(this)->GetRank();
    case PieceType::Bishop: return static_cast<const Bishop*>(this)->GetRank();
    case PieceType::Knight: return static_cast<const Knight*>(this)->GetRank();
    case PieceType::Pawn:   return static_cast<const Pawn*>(this)->GetRank();
    }
    return 0;
}

Color BasePiece::GetColor() const
{
    return color;
}

bool BasePiece::ReadFields(const char* name)
{
    int newX, newY, colorNumber;
    std::cout << name << " x y (1-8): ";
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

void BasePiece::PrintFields(const char* name) const
{
    std::cout << name << " (" << x << ", " << y << "), "
              << (color == Color::White ? "White" : "Black") << '\n';
}

void ChessList::Add(BasePiece* piece)
{
    List::Add(piece);
}

void ChessList::Insert(BasePiece* piece, int index)
{
    List::Insert(piece, index);
}

BasePiece* ChessList::GetPiece(int index)
{
    return static_cast<BasePiece*>(GetItem(index));
}

void ChessList::Print() const
{
    if (!Head())
    {
        std::cout << "List is empty.\n";
        return;
    }

    int index = 0;
    for (const Item* item = Head(); item; item = item->Next())
    {
        std::cout << index++ << ". ";
        static_cast<const BasePiece*>(item)->Print();
    }
}

void ChessList::FindByColor(Color color) const
{
    bool found = false;
    for (const Item* item = Head(); item; item = item->Next())
    {
        const BasePiece* piece = static_cast<const BasePiece*>(item);
        if (piece->GetColor() == color)
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
        const BasePiece* piece = static_cast<const BasePiece*>(item);
        if (piece->CanAttack(x, y) == mustAttack)
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
    for (int end = Count() - 1; end > 0; --end)
    {
        bool swapped = false;
        for (int i = 0; i < end; ++i)
        {
            const int leftRank = GetPiece(i)->GetRank();
            const int rightRank = GetPiece(i + 1)->GetRank();
            if (ascending ? leftRank > rightRank : leftRank < rightRank)
            {
                // Move the left node past the right one using the List interface.
                Insert(static_cast<BasePiece*>(Remove(i)), i + 1);
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}
