#include <iostream>
using namespace std;
class DoublyLinkedList;
class Node
{
    int data;
    Node *next;
    Node *prev;

public:
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(int val) : data(val), next(NULL), prev(NULL) {}
    friend class DoublyLinkedList;
};
class DoublyLinkedList
{
public:
    Node *head;
    DoublyLinkedList() : head(NULL) {}
    DoublyLinkedList(Node *node) : head(node) {}
    void insertAtEnd(Node *newNode)
    {
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    void insertAtFront(Node *newNode)
    {
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
    }

    void display()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << "-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    void sortAndRemoveDuplicate()
    {
        bool sortReq = true;
        Node *temp = head;
        while (sortReq)
        {
            temp = head;
            sortReq = false;
            while (temp->next)
            {

                if (temp->next->data < temp->data)
                {
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;
                    temp->prev = temp->next;
                    temp->next = temp->next->next;
                    temp->prev->next = temp;
                    if (temp->next)
                    {

                        temp->next->prev = temp;
                    }
                    temp = temp->prev;
                    sortReq = true;
                }
                temp = temp->next;
            }
        }
        temp = head;
        Node *temp2;
        while (temp->next)
        {
            if (temp->next->data == temp->data)
            {
                temp2 = temp->next;
                temp->next = temp2->next;
                temp->next->prev = temp;
                delete temp2;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
};
int main()
{
    Node a(1), b(2), c(2), d(4), e(5), f(11), g(3), h(2), i(4), j(8);
    DoublyLinkedList list(&a);
    list.insertAtEnd(&c);
    list.insertAtEnd(&b);
    list.insertAtEnd(&f);
    list.insertAtEnd(&e);
    list.insertAtEnd(&d);
    list.insertAtEnd(&g);
    list.insertAtEnd(&h);
    list.insertAtEnd(&j);
    list.insertAtEnd(&i);
    cout << "Initial list" << endl;
    list.display();
    cout << endl;
    list.sortAndRemoveDuplicate();
    cout << "After sort and removing duplicate" << endl;
    list.display();
    return 0;
}