#include <iostream>
#include "list.h"

class DebugList : public List
{
public:
    void PrintList() const
    {
        std::cout << "List: " << this
            << "  Head: " << Head()
            << "  Tail: " << Tail() << '\n';
        std::cout << "#\tp\t\t\tprev\t\t\tnext\n";

        int i = 0;
        const Item* p = Head();
        while (p != nullptr)
        {
            std::cout << i << '\t' << p << '\t'
                << p->Prev() << '\t' << p->Next() << '\n';
            p = p->Next();
            ++i;
        }
    }
};


int main()
{
    DebugList list;
    int choice;
    int number;
    Item* item;

    do
    {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. ADD\n";
        std::cout << "2. DELETE\n";
        std::cout << "3. GetItem\n";
        std::cout << "4. Remove\n";
        std::cout << "5. Insert\n";
        std::cout << "6. Count\n";
        std::cout << "7. Clear\n";
        std::cout << "8. GetIndex\n";
        std::cout << "9. PrintList\n";
        std::cout << "0. EXIT\n";
        std::cout << "Vvedite vibor: ";

        if (!(std::cin >> choice))
        {
            std::cout << "ERROR: Nuzhno chislo\n";
            break;
        }

        if ((choice >= 2 && choice <= 5) || choice == 8)
        {
            std::cout << "Vvedite nomer elementa (s 0): ";
            if (!(std::cin >> number))
            {
                std::cout << "ERROR: Nuzhno chislo\n";
                break;
            }

            if (number < 0)
            {
                std::cout << "ERROR: Index must be >= 0\n";
                continue;
            }
        }

        switch (choice)
        {
        case 1:
            item = new Item();
            list.Add(item);
            std::cout << "+1\n";
            break;

        case 2:
            list.Delete(number);
            break;

        case 3:
            item = list.GetItem(number);
            if (item == nullptr)
            {
                std::cout << "Element ne naiden\n";
            }
            else
            {
                std::cout << "Item: " << item
                    << "  prev: " << item->Prev()
                    << "  next: " << item->Next() << '\n';
            }
            break;

        case 4:
            item = list.Remove(number);
            if (item == nullptr)
            {
                std::cout << "Element ne naiden\n";
            }
            else
            {
                std::cout << "Removed: " << item
                    << "  prev: " << item->Prev()
                    << "  next: " << item->Next() << '\n';
                delete item;
            }
            break;

        case 5:
            item = new Item();
            list.Insert(item, number);
            std::cout << "Element vstavlen\n";
            break;

        case 6:
            std::cout << list.Count() << '\n';
            break;

        case 7:
            list.Clear();
            std::cout << "List cleared\n";
            break;

        case 8:
            item = list.GetItem(number);
            if (item == nullptr)
            {
                std::cout << "Element ne naiden\n";
            }
            else
            {
                std::cout << "Index: " << list.GetIndex(item) << '\n';
            }
            break;

        case 9:
            list.PrintList();
            break;

        case 0:
            std::cout << "Goodbye!\n";
            break;

        default:
            std::cout << "ERROR: Invalid choice\n";
        }
    } while (choice != 0);

    list.Clear();
    return 0;
}


