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
    void rotateByKNodes(int k)
    {
        k = k % lengthOfSingleLinkList();
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        Node *curr = head;
        Node *prev = NULL;
        for (int i = 0; i < k; i++)
        {
            prev = curr;
            curr = curr->next;
        }
        prev->next = NULL;
        temp->next = head;
        head = curr;
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
};
int main()
{
    SingleLinkList m(2);
    m.insertAtFront(1);
    m.insertAtFront(12);
    m.insertAtFront(14);
    m.display();
    m.rotateByKNodes(90);
    m.display();
    return 0;
}