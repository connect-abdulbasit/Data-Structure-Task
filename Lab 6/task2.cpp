#include <iostream>
using namespace std;

class Node
{
    char data;
    Node *next;

public:
    Node() : data(' '), next(NULL) {}
    Node(char c) : data(c), next(NULL) {}
    ~Node() {}
    friend class Stack;
};

class Stack
{
    Node *head;

public:
    Stack() : head(NULL) {}
    void push(char ch)
    {
        Node *newNode = new Node(ch);
        if (head != NULL)
        {
            newNode->next = head;
        }
        head = newNode;
    }
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack empty" << endl;
            return;
        }
        Node *delNode = head;
        head = head->next;
        delete delNode;
    }
    char peak()
    {
        if (isEmpty())
        {
            return '\0';
        }
        return head->data;
    }
    bool isEmpty()
    {
        return head == NULL;
    }
};

int precedence(char ch)
{
    switch (ch)
    {
    case '(':
    case ')':
        return 0;
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return -1;
    }
}

bool isLeftToRightAssociative(char ch)
{
    return ch != '^';
}

bool isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')');
}

void postfix(const char *infix, int length)
{
    Stack stack;
    char result[length + 1];
    int resultLength = 0;

    for (int pos = 0; pos < length; pos++)
    {
        char current = infix[pos];

        if (isOperator(current))
        {
            if (current == '(')
            {
                stack.push(current);
            }
            else if (current == ')')
            {
                while (!stack.isEmpty() && stack.peak() != '(')
                {
                    result[resultLength++] = stack.peak();
                    stack.pop();
                }
                stack.pop();
            }
            else
            {
                while (!stack.isEmpty() && precedence(current) <= precedence(stack.peak()))
                {
                    if (precedence(current) < precedence(stack.peak()))
                    {
                        result[resultLength++] = stack.peak();
                        stack.pop();
                    }
                    else if (precedence(current) == precedence(stack.peak()))
                    {
                        if (isLeftToRightAssociative(current))
                        {
                            result[resultLength++] = stack.peak();
                            stack.pop();
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                stack.push(current);
            }
        }
        else
        {
            result[resultLength++] = current;
        }
    }
    while (!stack.isEmpty())
    {
        result[resultLength++] = stack.peak();
        stack.pop();
    }

    result[resultLength] = '\0';

    cout << "Postfix expression: " << result << endl;
}

void prefix(const char *infix, int length)
{
    Stack stack;
    char result[length + 1];
    int resultLength = 0;
    char reverse[length + 1];

    // Reverse the infix expression
    for (int i = length - 1; i >= 0; i--)
    {
        reverse[length - i - 1] = infix[i];
    }
    reverse[length] = '\0';

    for (int pos = 0; pos < length; pos++)
    {
        char current = reverse[pos];

        if (isOperator(current))
        {
            if (current == ')')
            { // In postfix ( is used
                stack.push(current);
            }
            else if (current == '(')
            { // In postfix ) is used
                while (!stack.isEmpty() && stack.peak() != ')')
                { // In postfix ( is exceptional case
                    result[resultLength++] = stack.peak();
                    stack.pop();
                }
                stack.pop();
            }
            else
            {
                while (!stack.isEmpty() && precedence(current) < precedence(stack.peak()))
                {
                    result[resultLength++] = stack.peak();
                    stack.pop();
                }
                stack.push(current);
            }
        }
        else
        {
            result[resultLength++] = current;
        }
    }
    while (!stack.isEmpty())
    {
        result[resultLength++] = stack.peak();
        stack.pop();
    }

    // Reverse the result array to get the prefix expression
    for (int i = 0; i < resultLength / 2; i++)
    {
        swap(result[i], result[resultLength - i - 1]);
    }
    result[resultLength] = '\0';

    cout << "Prefix expression: " << result << endl;
}

int main()
{
    const char exp[] = "K+L-M*N+(O^P)*W/U/V*T+Q";
    int length = sizeof(exp) / sizeof(exp[0]) - 1;
    postfix(exp, length);
    prefix(exp, length);
    return 0;
}
