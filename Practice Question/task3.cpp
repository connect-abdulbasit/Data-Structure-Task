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

    void insertAtFront(int num)
    {
        Node *newNode = new Node(num);
        newNode->next = this->head;
        head = newNode;
    }
    bool search(int num)
    {
        return searchInLinkList(head, num);
    }
    bool searchInLinkList(Node *node, int num)
    {
        if (node == NULL)
        {
            return false;
        }
        if (node->data == num)
        {
            return true;
        }
        bool find = searchInLinkList(node->next, num);
        if (head == node)
        {
            if (find)
            {
                cout << num << " is found" << endl;
            }
            else
            {
                cout << num << " is not found" << endl;
            }
        }
        return find;
    }
};
int main()
{
    SingleLinkList m(2);
    m.insertAtFront(1);
    m.insertAtFront(12);
    m.insertAtFront(14);
    int num;
    cout << "Enter the number you want to search in link list" << endl;
    cin >> num;
    m.search(num);

    return 0;
}