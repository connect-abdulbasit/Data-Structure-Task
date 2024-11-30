#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Book
{
    int BID;
    string title;
    string author;

public:
    Book(int bid, string title, string author)
    {
        BID = bid;
        this->title = title;
        this->author = author;
    }
    int getBID()
    {
        return BID;
    }
    friend class HashTable;
};

class HashTable
{
    vector<list<Book>> table;
    int size;

    int hasFunction(int BID)
    {
        return BID / 10;
    }

public:
    HashTable(int size)
    {
        this->size = size;
        table.resize(size);
    }

    void insert(Book book)
    {
        int index = hasFunction(book.BID);
        table[index].push_back(book);
    }

    Book search(int BID)
    {
        int index = BID / 10;
        for (auto &b : table[index])
        {
            if (b.BID == BID)
            {

                return b;
            }
        }

        return Book(-1, "", "");
    }

    void deleteBook(int BID)
    {
        int index = BID / 10;
        for (auto it = table[index].begin(); it != table[index].end(); ++it)
        {
            if (it->BID == BID)
            {
                table[index].erase(it);
                return;
            }
        }
        cout << "Book not found" << endl;
    }

    void display()
    {
        for (int i = 0; i < size; ++i)
        {
            cout << "Index " << i << ": [";
            for (auto &b : table[i])
            {
                cout << "" << b.title << " by " << b.author;
            }
            cout << "]" << endl;
        }
    }
};

int main()
{
    HashTable table(10);

    Book book1(011, "book1", "authorA");
    Book book2(012, "book2", "authorA");
    Book book3(013, "book3", "authorA");
    Book book4(024, "book4", "authorB");
    Book book5(025, "book5", "authorB");
    Book book6(036, "book6", "authorC");
    Book book7(037, "book7", "authorC");
    Book book8(38, "book8", "authorC");
    Book book9(39, "book9", "authorC");

    table.insert(book1);
    table.insert(book2);
    table.insert(book3);
    table.insert(book4);
    table.insert(book5);
    table.insert(book6);
    table.insert(book7);
    table.insert(book8);
    table.insert(book9);
    cout << "After insertion" << endl;
    table.display();
    cout << "\n\nSearching Books\n";

    Book b1 = table.search(011);
    if (b1.getBID() != -1)
    {
        cout << "Book found: " << b1.getBID() << endl;
    }
    else
    {
        cout << "Book not found" << endl;
    }

    Book b2 = table.search(025);
    if (b2.getBID() != -1)
    {
        cout << "Book found: " << b2.getBID() << endl;
    }
    else
    {
        cout << "Book not found" << endl;
    }

    Book b3 = table.search(40);
    if (b3.getBID() != -1)
    {
        cout << "Book found: " << b3.getBID() << endl;
    }
    else
    {
        cout << "Book not found" << endl;
    }

    cout << "\n\nDeleting Books\n";

    table.deleteBook(b1.getBID());
    table.deleteBook(b2.getBID());

    cout << "\n\nAfter Deletion\n";
    table.display();

    return 0;
}
