#include <iostream>
#include <limits>
#include "subj.h"

namespace
{
    void DiscardInvalidInput()
    {
        if (std::cin.fail() && !std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    bool ReadNumber(const char* prompt, int& number)
    {
        std::cout << prompt;
        if (std::cin >> number)
        {
            return true;
        }

        if (!std::cin.eof())
        {
            std::cout << "Enter a number.\n";
            DiscardInvalidInput();
        }
        return false;
    }

    BasePiece* ReadPiece()
    {
        std::cout << "0 - King, 1 - Queen, 2 - Rook, 3 - Bishop, 4 - Knight, 5 - Pawn\n";
        int type;
        if (!ReadNumber("Choose a piece: ", type))
        {
            return nullptr;
        }

        if (type < static_cast<int>(PieceType::King) || type > static_cast<int>(PieceType::Pawn))
        {
            std::cout << "Invalid piece type.\n";
            return nullptr;
        }

        BasePiece* piece = BasePiece::Create(static_cast<PieceType>(type));
        if (!piece->Input())
        {
            delete piece;
            DiscardInvalidInput();
            return nullptr;
        }
        return piece;
    }
}

int main()
{
    ChessList list;

    while (!std::cin.eof())
    {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Add\n";
        std::cout << "2. Delete\n";
        std::cout << "3. Print one piece\n";
        std::cout << "4. Remove\n";
        std::cout << "5. Insert\n";
        std::cout << "6. Count\n";
        std::cout << "7. Clear\n";
        std::cout << "8. GetIndex\n";
        std::cout << "9. Print chess list\n";
        std::cout << "10. Find pieces that can attack a square\n";
        std::cout << "11. Find pieces that cannot attack a square\n";
        std::cout << "12. Find pieces by color\n";
        std::cout << "13. Sort by rank\n";
        std::cout << "0. Exit\n";

        int choice;
        if (!ReadNumber("Choose a command: ", choice))
        {
            continue;
        }

        int index = 0;
        if ((choice >= 2 && choice <= 5) || choice == 8)
        {
            if (!ReadNumber("Enter index (starting at 0): ", index))
            {
                continue;
            }

            if (index < 0)
            {
                std::cout << "Index must be >= 0.\n";
                continue;
            }
        }

        switch (choice)
        {
        case 1:
            if (BasePiece* piece = ReadPiece())
            {
                list.Add(piece);
                std::cout << "Piece added.\n";
            }
            break;

        case 2:
            list.Delete(index);
            break;

        case 3:
            if (const BasePiece* piece = list.GetPiece(index))
            {
                piece->Print();
            }
            else
            {
                std::cout << "Piece not found.\n";
            }
            break;

        case 4:
            if (Item* item = list.Remove(index))
            {
                delete item;
                std::cout << "Piece removed.\n";
            }
            else
            {
                std::cout << "Piece not found.\n";
            }
            break;

        case 5:
            if (BasePiece* piece = ReadPiece())
            {
                list.Insert(piece, index);
                std::cout << "Piece inserted.\n";
            }
            break;

        case 6:
            std::cout << list.Count() << '\n';
            break;

        case 7:
            list.Clear();
            std::cout << "List cleared.\n";
            break;

        case 8:
            if (BasePiece* piece = list.GetPiece(index))
            {
                std::cout << "Index: " << list.GetIndex(piece) << '\n';
            }
            else
            {
                std::cout << "Piece not found.\n";
            }
            break;

        case 9:
            list.Print();
            break;

        case 10:
        case 11:
        {
            int x, y;
            std::cout << "Target x y (1-8): ";
            if (std::cin >> x >> y)
            {
                list.FindByAttack(x, y, choice == 10);
            }
            else
            {
                std::cout << "Invalid coordinates.\n";
                DiscardInvalidInput();
            }
            break;
        }

        case 12:
        {
            int color;
            if (ReadNumber("Color (0 - White, 1 - Black): ", color))
            {
                if (color == 0 || color == 1)
                {
                    list.FindByColor(static_cast<Color>(color));
                }
                else
                {
                    std::cout << "Invalid color.\n";
                }
            }
            break;
        }

        case 13:
        {
            int order;
            if (ReadNumber("Order (1 - Pawn to King, -1 - King to Pawn): ", order))
            {
                if (order == 1 || order == -1)
                {
                    list.SortByRank(order == 1);
                    list.Print();
                }
                else
                {
                    std::cout << "Invalid order.\n";
                }
            }
            break;
        }

        case 0:
            std::cout << "Goodbye!\n";
            return 0;

        default:
            std::cout << "Invalid command.\n";
        }
    }

    return 0;
}
