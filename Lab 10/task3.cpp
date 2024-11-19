#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct Compare
{
    bool operator()(ListNode *a, ListNode *b)
    {
        return a->val > b->val;
    }
};

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    priority_queue<ListNode *, vector<ListNode *>, Compare> minHeap;

    for (ListNode *list : lists)
    {
        if (list)
        {
            minHeap.push(list);
        }
    }

    ListNode *dummy = new ListNode(0);
    ListNode *current = dummy;

    while (!minHeap.empty())
    {
        ListNode *smallest = minHeap.top();
        minHeap.pop();

        current->next = smallest;
        current = current->next;

        if (smallest->next)
        {
            minHeap.push(smallest->next);
        }
    }

    return dummy->next;
}

ListNode *createList(const vector<int> &values)
{
    ListNode *dummy = new ListNode(0);
    ListNode *current = dummy;
    for (int value : values)
    {
        current->next = new ListNode(value);
        current = current->next;
    }
    return dummy->next;
}

void printList(ListNode *head)
{
    while (head)
    {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main()
{
    vector<ListNode *> lists = {
        createList({1, 4, 5}),
        createList({1, 3, 4}),
        createList({2, 6})};

    ListNode *merged = mergeKLists(lists);
    printList(merged);

    return 0;
}
