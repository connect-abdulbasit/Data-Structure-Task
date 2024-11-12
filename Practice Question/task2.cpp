#include <iostream>

using namespace std;
class SingleLinkList;
class Node
{
    int data;
    Node *next;

public:
    Node()
    {
        this->data = 0;
        this->next = NULL;
    }

    Node(int num)
    {
        this->data = num;
        this->next = NULL;
    }
    friend class SingleLinkList;
};
class SingleLinkList
{
    Node *head;

public:
    SingleLinkList(int num)
    {
        head = new Node(num);
    }

    SingleLinkList()
    {
        head = NULL;
    }
    int lengthOfSingleLinkList()
    {
        return lengthOfLinkList(this->head, 0);
    }
    int lengthOfLinkList(Node *head, int count)
    {
        if (head == NULL)
        {
            return count;
        }
        return lengthOfLinkList(head->next, count + 1);
    }
    void insertAtFront(int num)
    {
        Node *newNode = new Node(num);
        newNode->next = this->head;
        head = newNode;
    }
};
int main()
{
    SingleLinkList m(2);
    m.insertAtFront(1);
    m.insertAtFront(12);
    m.insertAtFront(14);
    cout << "Length of linklist is " << m.lengthOfSingleLinkList();
    return 0;
}