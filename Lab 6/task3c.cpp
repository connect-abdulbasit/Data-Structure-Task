#include <iostream>
using namespace std;
class Node
{
    string personName;
    Node *next;

public:
    Node(string name)
    {
        personName = name;
        next = NULL;
    }
    ~Node()
    {
    }
    friend class Queue;
};
class Queue
{
    Node *arr;

public:
    Queue()
    {
        arr = NULL;
    }
    Queue(string name)
    {
        arr = new Node(name);
    }
    void enqueue(string n)
    {
        if (arr == NULL)
        {
            arr = new Node(n);
        }
        else
        {

            Node *newNode = new Node(n);
            Node *temp = arr;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            cout << "Enqueue sucessfully\n";
        }
    }
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty\n";
        }
        else
        {
            Node *temp = arr;
            arr = arr->next;
            delete temp;
            cout << "Dequeue sucessfully\n";
        }
    }
    bool isEmpty()
    {
        return arr == NULL;
    }
    bool isFull()
    {
        return false;
    }
    string peekFront()
    {
        return arr->personName;
    }
    void display()
    {
        Node *temp = arr;
        while (temp != NULL)
        {
            cout << temp->personName << "\t";
            temp = temp->next;
        }
        cout << endl;
    }
};
int main()
{
    Queue ticketSystem;
    string names[15] = {"Abdul", "Basit", "Taha", "Hani", "Ali", "Qadir", "Ahmed", "Jawad", "Noor", "Amjad", "Alishba", "Sarah", "Hadi", "Mohid", "Hasan"};

    cout << "Enqueueing first 10 people into the queue:\n";
    for (int i = 0; i < 10; i++)
    {
        ticketSystem.enqueue(names[i]);
    }
    cout << "\nAfter adding 10 people:\n";
    ticketSystem.display();

    cout << "\nDequeueing 5 people from the queue:\n";
    for (int i = 0; i < 5; i++)
    {
        ticketSystem.dequeue();
    }
    cout << "\nAfter dequeuing 5 people:\n";
    ticketSystem.display();

    cout << "\nEnqueueing remaining 5 people into the queue:\n";
    for (int i = 10; i < 15; i++)
    {
        ticketSystem.enqueue(names[i]);
    }
    cout << "\nAfter enqueueing remaining 5 people:\n";
    ticketSystem.display();

    return 0;
}
