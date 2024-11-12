#include <iostream>
using namespace std;
class SingleLinkList;
class Node
{

private:
    int data;
    Node *next;

public:
    Node(int data) : data(data), next(NULL)
    {
    }
    Node() : data(0), next(NULL)
    {
    }
    ~Node()
    {
        if (next != NULL)
        {
            delete next;
        }
    }
    friend class SingleLinkList;
};
class SingleLinkList
{
    Node *head;

public:
    SingleLinkList() : head(NULL)
    {
    }

    SingleLinkList(Node *n) : head(n)
    {
    }
    ~SingleLinkList()
    {
        if (head != NULL)
        {
            delete head;
        }
    }
    void reverseTheList()
    {
        Node *temp = head;
        Node *prev = NULL;
        Node *next = NULL;
        while (temp != NULL)
        {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        head = prev;
    }
    void insertAtEnd(Node *n)
    {
        Node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = n;
    }
    void display()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
int main()
{
    Node a(1), b(2), c(3), d(4), e(5);
    SingleLinkList list(&a);
    list.insertAtEnd(&b);
    list.insertAtEnd(&c);
    list.insertAtEnd(&d);
    list.insertAtEnd(&e);
    cout << "Insert few nodes" << endl;
    list.display();
    cout << endl;
    cout << "Reversed Version of original " << endl;
    list.reverseTheList();
    list.display();
}