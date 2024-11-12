#include <iostream>
using namespace std;
class linkedList;
void radixSort(linkedList &l1);
void countSort(linkedList &l1, int exp);
class Node
{
    int score;
    string name;
    Node *next;
    Node *prev;

public:
    Node()
    {
        score = 0;
        name = "";
        next = NULL;
        prev = NULL;
    }

    Node(int s, string n)
    {
        score = s;
        name = n;
        next = NULL;
        prev = NULL;
    }

    friend class linkedList;
    friend void radixSort(linkedList &l1);
    friend void countSort(linkedList &l1, int exp);
};

class linkedList
{

public:
    Node *head;
    linkedList()
    {
        head = NULL;
    }

    void push_back(int s, string n)
    {
        if (head == NULL)
        {
            head = new Node(s, n);
            return;
        }
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new Node(s, n);
        temp->next->prev = temp;
    }

    int getMax()
    {
        Node *temp = head;
        int max = temp->score;
        while (temp != NULL)
        {
            if (temp->score > max)
            {
                max = temp->score;
            }
            temp = temp->next;
        }
        return max;
    }
    void display()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->name << " " << temp->score << endl;
            temp = temp->next;
        }
        cout << endl;
    }
};

void countSort(linkedList &l1, int exp)
{
    int count[10] = {0};
    int n = 0;
    Node *temp = l1.head;

    while (temp != NULL)
    {
        count[((temp->score) / exp) % 10]++;
        temp = temp->next;
        n++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    Node **output = new Node *[n];

    temp = l1.head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    while (temp != NULL)
    {
        int index = ((temp->score) / exp) % 10;
        output[count[index] - 1] = temp;
        count[index]--;
        temp = temp->prev;
    }
    l1.head = output[0];
    temp = l1.head;
    for (int i = 1; i < n; i++)
    {
        temp->next = output[i];
        temp = temp->next;
    }
    temp->next = NULL;

    delete[] output;
}

void radixSort(linkedList &l1)
{
    int max = l1.getMax();

    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        countSort(l1, exp);
    }
}

int main()
{
    linkedList l1;
    int n;

    cout << "Enter the number of students: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int s;
        string name;

        cout << "Enter the score and name of student " << i + 1 << ": ";
        cin >> s >> name;
        l1.push_back(s, name);
    }
    cout << "Before sorting: " << endl;
    l1.display();

    radixSort(l1);

    cout << "After sorting: " << endl;
    l1.display();
    return 0;
}
