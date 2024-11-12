#include <iostream>
using namespace std;
class SinglelinkList;
class Node
{

private:
    int data;
    Node *next;

public:
    Node(int data) : data(data), next(NULL)
    {
    }
    Node() : data(0), next(NULL)
    {
    }
    ~Node()
    {
        if (next != NULL)
        {
            delete next;
        }
    }
    friend class SingleLinkList;
};

class SingleLinkList
{
    Node *head;

public:
    SingleLinkList() : head(NULL)
    {
    }
    SingleLinkList(Node *n) : head(n) {}

    void insertAtEnd(Node *n)
    {
        if (head)
        {

            Node *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = n;
        }
        else
        {
            head = n;
        }
    }
    void reverse()
    {
        Node *newHead = reverseByRecursion(head);
        head = newHead;
    }
    Node *reverseByRecursion(Node *temp)
    {
        if (temp == NULL)
        {
            return NULL;
        }
        if (temp->next == NULL)
        {
            return temp;
        }

        Node *newNode = reverseByRecursion(temp->next);
        temp->next->next = temp;
        temp->next = NULL;
        return newNode;
    }
    void display()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
int main()
{
    Node n1(1), n2(2), n3(3), n4(4);
    SingleLinkList list(&n1);
    list.insertAtEnd(&n2);
    list.insertAtEnd(&n3);
    list.insertAtEnd(&n4);
    cout << "Before sorting:" << endl;
    list.display();
    list.reverse();
    cout << "After sorting:" << endl;
    list.display();
    return 0;
}