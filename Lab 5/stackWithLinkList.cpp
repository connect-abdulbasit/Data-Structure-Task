#include <iostream>
using namespace std;
class Stack;
class Node
{

    int data;
    Node *next;

public:
    Node()
    {
        data = 0;
        next = NULL;
    }
    Node(int val)
    {
        data = val;
        next = NULL;
    }
    ~Node()
    {
        delete next;
    }
    friend class Stack;
};

class Stack
{
    Node *head;

public:
    Stack(Node *head)
    {
        this->head = head;
    }
    Stack()
    {
        head = NULL;
    }
    void push(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }
    void pop()
    {
        if (!isEmpty())
        {

            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    int peak()
    {
        return head->data;
    }
    bool isEmpty()
    {
        return (head) ? false : true;
    }
    bool isFull()
    {
        return false;
    }
    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
};

int main()
{
    Stack stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.push(4);
    cout << stack1.peak() << endl;
    stack1.pop();
    cout << stack1.peak() << endl;

    return 0;
}