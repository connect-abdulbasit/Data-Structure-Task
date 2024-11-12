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
    void insertAtEnd(Node *n)
    {

        if (head == NULL)
        {
            head = n;
        }
        else
        {
            Node *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = n;
        }
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
    void segregateTheList()
    {
        Node even(0);
        Node odd(0);
        Node *temp = head;
        Node *extra = NULL;
        SingleLinkList oddList(&even);
        SingleLinkList evenList(&odd);

        while (temp)
        {
            extra = temp->next;
            if (temp->data % 2 == 0)
            {

                temp->next = NULL;
                evenList.insertAtEnd(temp);
            }
            else
            {

                temp->next = NULL;
                oddList.insertAtEnd(temp);
            }
            temp = extra;
        }
        evenList.insertAtEnd(oddList.head);
        head = evenList.head->next;
        cout << "Segregated List" << endl;
        display();
    }
};
int main()
{
    Node a(1), b(31), c(32), d(40), e(58), f(11), g(3), h(2), i(4), j(8);
    SingleLinkList list(&a);
    list.insertAtEnd(&b);
    list.insertAtEnd(&c);
    list.insertAtEnd(&d);
    list.insertAtEnd(&e);
    list.insertAtEnd(&f);
    list.insertAtEnd(&g);
    list.insertAtEnd(&h);
    list.insertAtEnd(&i);
    list.insertAtEnd(&j);
    cout << "Insert Few Values " << endl;
    list.display();
    cout << endl;
    list.segregateTheList();
    return 0;
}