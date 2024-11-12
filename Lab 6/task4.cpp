#include <iostream>
using namespace std;

class Stack
{
    int *data;
    int top;
    int size;

public:
    Stack(int n)
    {
        data = new int[n];
        top = 0;
        size = n;
    }
    void push(int n)
    {
        if (isFull())
        {
            cout << "Stack is full" << endl;
            return;
        }
        data[top] = n;
        top++;
    }
    int pop()
    {
        if (isEmpty())
        {
            return -1;
        }

        top--;
        return data[top];
    }
    int peak()
    {
        return data[top];
    }
    bool isEmpty()
    {
        if (top == 0)
        {
            return true;
        }
        return false;
    }
    bool isFull()
    {
        if (top == size)
        {
            return true;
        }
        return false;
    }
};
class QUEUE
{
    Stack *s1, *s2;

public:
    QUEUE(int n)
    {
        s1 = new Stack(n);
        s2 = new Stack(n);
    }
    void enqueue(int n)
    {
        if (s1->isFull())
        {
            cout << "Queue is full" << endl;
            return;
        }

        while (!s1->isEmpty())
        {
            s2->push(s1->pop());
        }
        s1->push(n);
        while (!s2->isEmpty())
        {
            s1->push(s2->pop());
        }
    }
    int dequeue()
    {
        return s1->pop();
    }
    void display()
    {
        int n;
        while (!s1->isEmpty())
        {
            n = s1->pop();
            cout << n << " ";
            s2->push(n);
        }
        cout << endl;
        while (!s2->isEmpty())
        {
            s1->push(s2->pop());
        }
    }
    ~QUEUE()
    {
        delete s1;
        delete s2;
    }
};
int main()
{
    QUEUE q(10);
    for (int i = 0; i < 10; i++)
    {
        q.enqueue(i);
    }
    cout << "Added 1 to 10 " << endl;
    q.display();
    for (int i = 0; i < 5; i++)
    {
        q.dequeue();
    }
    cout << "Remove 5 element from the stack " << endl;
    q.display();
    return 0;
}