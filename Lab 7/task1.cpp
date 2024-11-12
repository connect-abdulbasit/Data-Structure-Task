#include <iostream>

using namespace std;

class Node
{
    int data;
    Node *next;
    Node *prev;
    static int count;
    int index;

public:
    Node(int n)
    {
        data = n;
        next = NULL;
        prev = NULL;
        count++;
        index = count;
    }
    Node()
    {
        data = 0;
        next = NULL;
        prev = NULL;
    }
    friend class linkedList;
};
int Node::count = 0;

class linkedList
{
    Node *head;

public:
    linkedList()
    {
        head = NULL;
    }
    linkedList(int n)
    {
        head = new Node(n);
    }
    void push_back(int n)
    {
        if (head == NULL)
        {
            head = new Node(n);
            return;
        }
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new Node(n);
        temp->next->prev = temp;
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

    void swapData(Node *n1, Node *n2)
    {
        if (n1 == n2)
            return;

        int tempData = n1->data;
        n1->data = n2->data;
        n2->data = tempData;
    }

    Node *partition(Node *left, Node *right, Node *pivot)
    {
        Node *i = left->prev;
        Node *j = left;

        while (j != right)
        {
            if (j->data <= pivot->data)
            {
                i = (i == NULL) ? left : i->next;
                swapData(i, j);
            }
            j = j->next;
        }
        i = (i == NULL) ? left : i->next;
        swapData(i, right);
        return i;
    }

    void quickSort(Node *left, Node *right)
    {
        if (right != NULL && left != right && left != right->next)
        {
            Node *pivot = partition(left, right, right);
            quickSort(left, pivot->prev);
            quickSort(pivot->next, right);
        }
    }

    void quickSorted()
    {
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        quickSort(head, temp);
    }
};

int main()
{
    linkedList l1;
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(7);
    l1.push_back(4);
    l1.display();
    l1.quickSorted();
    l1.display();
    return 0;
}
