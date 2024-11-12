#include <iostream>
using namespace std;
class Queue
{
    string *arr;
    int rear;
    int front;
    int size;

public:
    Queue(int n)
    {
        arr = new string[n];
        size = n;
        rear = -1;
        front = -1;
    }
    void enqueue(string n)
    {
        if (!isFull())
        {
            rear++;
            arr[rear] = n;
            cout << "Enqueue sucessfully\n";
        }
        else
        {
            cout << "Queue is Full\n";
        }
    }
    void dequeue()
    {
        if (!isEmpty())
        {
            front++;
            cout << "Dequeue sucessfully\n";
        }
        else
        {
            cout << "Queue is empty\n";
        }
    }
    bool isEmpty()
    {
        return front == rear;
    }
    bool isFull()
    {
        return (rear + 1) == size;
    }
    string peekFront()
    {
        return arr[front + 1];
    }
    void display()
    {
        for (int i = front + 1; i <= rear; i++)
        {
            cout << arr[i] << "\t";
        }
        cout << endl;
    }
};
int main()
{
    Queue ticketSystem(10);
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