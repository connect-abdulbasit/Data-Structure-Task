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
    void insertBeforeValue(int positionValue, Node *newNode)
    {
        Node *temp = head;
        while (temp->next->data != positionValue)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next = newNode;
        newNode->next->prev = newNode;
    }
    void insertAfterValue(int positionValue, Node *newNode)
    {
        Node *temp = head;
        while (temp->data != positionValue)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next = newNode;
        newNode->next->prev = newNode;
    }
    void deleteNodeFromHead()
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    void deleteNodeFromEnd()
    {
        Node *temp = head;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        Node *temp2 = temp->next;
        delete temp2;
        temp->next = NULL;
    }
    void deleteFromParticularValue(int value)
    {
        Node *temp = head;
        while (temp->data != value)
        {
            temp = temp->next;
        }
        Node *temp2 = temp;
        temp = temp->prev;
        temp->next = temp2->next;
        temp = temp->next;
        temp->prev = temp2->prev;
        delete temp2;
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
};
int main()
{
    Node a(1), b(2), c(3), d(4), e(5), f(11), g(3), h(2), i(4), j(8);
    DoublyLinkedList list(&a);
    cout << "Initial list: " << endl;
    list.display();
    cout << endl;
    list.insertAtEnd(&b);
    cout << "Inserting at the end: " << endl;
    list.display();
    cout << endl;
    list.insertAtFront(&c);
    cout << "Inserting at the front: " << endl;
    list.display();
    cout << endl;
    list.insertBeforeValue(2, &d);
    cout << "Inserting before value 2: " << endl;
    list.display();
    cout << endl;
    list.insertAfterValue(3, &e);
    cout << "Inserting after value 3: " << endl;
    list.display();
    cout << endl;
    list.deleteNodeFromEnd();
    cout << "Deleting from the end: " << endl;
    list.display();
    cout << endl;
    list.deleteNodeFromHead();
    cout << "Deleting from the head: " << endl;
    list.display();
    cout << endl;
    list.deleteFromParticularValue(1);
    cout << "Deleting node with value 1: " << endl;
    list.display();
    cout << endl;
    return 0;
}