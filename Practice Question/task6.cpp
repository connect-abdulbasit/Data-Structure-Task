#include <iostream>
using namespace std;
class CircularLinkList;
class Node
{
    string data;
    Node *next;

public:
    Node(string carName)
    {
        this->data = carName;
        this->next = NULL;
    }
    friend class CircularLinkList;
};
class CircularLinkList
{
    Node *head;

public:
    CircularLinkList()
    {
        head = NULL;
    }
    CircularLinkList(string name)
    {
        head = new Node(name);
        head->next = head;
    }
    void insertNewCar(string name)
    {
        if (head == NULL)
        {
            head = new Node(name);
            head->next = head;
        }
        else
        {
            Node *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = new Node(name);
            temp->next->next = head;
        }
    }
    void removeACar()
    {
        if (head == NULL)
        {
            cout << "No Car avaliable" << endl;
            return;
        }
        Node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = head->next;
        temp = head;
        head = head->next;
        delete temp;
    }
    void display()
    {
        if (head == NULL)
        {
            cout << "NULL" << endl;
            return;
        }

        Node *temp = head;
        do
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "Again First Car" << endl;
    }
};
int main()
{
    CircularLinkList c("honda");
    c.insertNewCar("civic");
    c.insertNewCar("alto");
    c.insertNewCar("bmw");
    cout << "Added 5 cars: \n"
         << endl;
    c.display();
    cout << endl
         << endl;
    c.removeACar();
    c.removeACar();
    cout << "Remove 2 cars: \n"
         << endl;
    c.display();
    return 0;
}