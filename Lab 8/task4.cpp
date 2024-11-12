#include <iostream>
#include <deque>
#include <queue>
using namespace std;
class Node
{
    int val;
    Node *left;
    Node *right;

public:
    Node(int val)
    {
        this->val = val;
        right = NULL;
        left = NULL;
    }
    friend class Binarytree;
};
class Binarytree
{
    Node *root;

    bool isIdentical(Node *r1, Node *r2)
    {
        if (r1 == NULL && r2 == NULL)
        {
            return true;
        }
        if (r1 == NULL || r2 == NULL)
        {
            return false;
        }
        if (r1->val == r2->val)
        {
            return isIdentical(r1->left, r2->left) && isIdentical(r1->right, r2->right);
        }
        return false;
    }

    bool isSubTreeIdentical(Node *r1, Node *r2)
    {
        if (r1 == NULL && r2 == NULL)
        {
            return true;
        }

        if (r2 == NULL)
        {
            return true;
        }
        if (r1 == NULL)
        {
            return false;
        }
        if (r1->val == r2->val)
        {
            return isIdentical(r1, r2);
        }

        return isSubTreeIdentical(r1, r2->left) || isSubTreeIdentical(r1, r2->right);
    }

public:
    Binarytree()
    {
        root = NULL;
    }
    void insertion(int val)
    {
        root = insert(val, root);
    }
    Node *insert(int val, Node *head)
    {
        if (head == NULL)
        {
            return new Node(val);
        }
        if (val > head->val)
        {
            head->right = insert(val, head->right);
        }
        else
        {
            head->left = insert(val, head->left);
        }
        return head;
    }

    bool isSubtreeI(Binarytree b1, Binarytree b2)
    {
        return isSubTreeIdentical(b1.root, b2.root);
    }
};
int main()
{
    Binarytree b, c;

    b.insertion(12);
    b.insertion(10);
    b.insertion(3);
    b.insertion(1);
    b.insertion(102);

    c.insertion(10);
    c.insertion(3);
    c.insertion(1);

    if (b.isSubtreeI(b, c))
    {
        cout << "Subtree is present" << endl;
    }
    else
    {
        cout << "Subtree is not present" << endl;
    }

    return 0;
}
