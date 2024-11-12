#include <iostream>
using namespace std;
class SingleLinkList;
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
    void insertAtFront(Node *n)
    {
        if (head)
        {
            n->next = head;
        }
        head = n;
    }
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
    void insertNodeBeforeValue(int value, Node *n)
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }

        Node *temp = head;
        if (temp->data == value)
        {
            insertAtFront(n);
        }
        else
        {
            while (temp->next != NULL && temp->next->data != value)
            {
                temp = temp->next;
            }
            if (temp->next == NULL)
            {
                cout << "Value not found" << endl;
                return;
            }
            Node *temp2 = temp->next;
            temp->next = n;
            n->next = temp2;
        }
    }
    void insertNodeAfterValue(int value, Node *n)
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }

        Node *temp = head;

        while (temp->next != NULL && temp->data != value)
        {
            temp = temp->next;
        }
        if (temp->next == NULL)
        {
            cout << "Value not found " << endl;
            return;
        }

        Node *temp2 = temp->next;
        temp->next = n;
        n->next = temp2;
    }
    void deleteFromHead()
    {
        if (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void deleteFromEnd()
    {
        if (head)
        {
            if (head->next == NULL)
            {
                delete head;
                head = NULL;
                return;
            }
            Node *temp = head;
            while (temp->next->next)
            {
                temp = temp->next;
            }
            Node *del = temp->next;
            temp->next = NULL;
            delete del;
        }
    }
    void deleteNodeFromParticularValue(int value)
    {
        if (head)
        {

            Node *temp = head;
            if (temp->data == value)
            {
                deleteFromHead();
            }
            else
            {

                while (temp->next->data != value && temp->next != NULL)
                {
                    temp = temp->next;
                }
                if (temp->next == NULL)
                {
                    cout << "Value not found" << endl;
                    return;
                }
                Node *temp2 = temp->next;
                temp->next = temp2->next;
                delete temp2;
            }
        }
    }
    int numberOfNodes()
    {
        int count = 0;
        Node *temp = head;
        while (temp)
        {
            temp = temp->next;
            count++;
        }
        return count;
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
    ~SingleLinkList()
    {
        if (head != NULL)
        {
            delete head;
        }
    }
};
int main()
{
    Node a(1), b(2), c(3), d(4), e(5);

    SingleLinkList list(&a);
    cout << "Initial List" << endl;
    list.display();
    cout << endl;
    cout << "Insert At End" << endl;
    list.insertAtEnd(&b);
    list.display();
    cout << endl;
    cout << "Insert Before the value (1)" << endl;
    list.insertNodeBeforeValue(1, &c);
    list.display();
    cout << endl;
    cout << "Insert at Front" << endl;
    list.insertAtFront(&e);
    list.display();
    cout << endl;
    cout << "Insert after the value (1)" << endl;
    list.insertNodeAfterValue(1, &d);
    list.display();
    cout << endl;
    cout << "Delete from end" << endl;
    list.deleteFromEnd();
    list.display();
    cout << endl;
    cout << "Delete 1 from the single link list " << endl;
    list.deleteNodeFromParticularValue(1);
    list.display();
    cout << endl;
    cout << "Delete from head" << endl;
    list.deleteFromHead();
    list.display();
    cout << endl;
    cout << "Number of nodes: " << list.numberOfNodes() << endl;
    return 0;
}