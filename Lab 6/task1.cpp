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
    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
        }

        for (int i = 0; i < top; i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};
void evenOddStack(Stack original, Stack &evenOne, Stack &oddOne)
{
    int n;
    while (!original.isEmpty())
    {
        n = original.pop();

        if (n % 2 == 0)
        {

            evenOne.push(n);
        }
        else
        {

            oddOne.push(n);
        }
    }
}
int main()
{
    Stack original(10), even(10), odd(10);
    for (int i = 0; i < 10; i++)
    {
        original.push(i);
    }
    original.display();
    evenOddStack(original, even, odd);
    cout << "Even Stack" << endl;
    even.display();
    cout << "Odd Stack" << endl;
    odd.display();
    return 0;
}