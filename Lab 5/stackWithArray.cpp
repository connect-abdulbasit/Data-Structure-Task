#include <iostream>
using namespace std;

class Stack
{
    int maxSize;
    int *arr;
    int top;

public:
    Stack(int n)
    {
        maxSize = n;
        arr = new int[n];
        top = 0;
    }
    void push(int num)
    {
        if (!isFull())
        {

            arr[top] = num;
            top++;
        }
        else
        {
            cout << "No space for new element" << endl;
        }
    }
    void pop()
    {
        if (isEmpty())
        {
            cout << "The array is empty" << endl;
            return;
        }
        top--;
    }
    int peak()
    {
        if (isEmpty())
        {
            cout << "The array is empty" << endl;
            return -1;
        }
        return arr[top];
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
        if (top == maxSize)
        {
            return true;
        }
        return false;
    }
};

int main()
{
    Stack stack1(5);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.push(4);
    return 0;
}