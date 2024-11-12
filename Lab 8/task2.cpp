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
    void levelOrderTraversal()
    {
        if (root == NULL)
        {
            return;
        }

        queue<Node *> q;
        q.push(root);
        q.push(NULL);
        while (!q.empty())
        {

            if (!q.empty())
            {
                Node *temp = q.front();
                q.pop();

                if (temp == NULL)
                {
                    cout << endl;
                    if (!q.empty())
                    {
                        q.push(NULL);
                    }
                }
                else
                {
                    cout << temp->val << " ";
                    if (temp->left)
                    {
                        q.push(temp->left);
                    }
                    if (temp->right)
                    {
                        q.push(temp->right);
                    }
                }
            }
        }
    }
    void zigzagTraversal()
    {
        deque<Node *> q;
        q.push_back(root);
        bool isLeftToRight = true;
        while (!q.empty())
        {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++)
            {
                Node *temp;
                if (isLeftToRight)
                {
                    temp = q.front();
                    q.pop_front();
                    if (temp->left)
                    {
                        q.push_back(temp->left);
                    }
                    if (temp->right)
                    {
                        q.push_back(temp->right);
                    }
                }
                else
                {
                    temp = q.back();
                    q.pop_back();
                    if (temp->right)
                    {
                        q.push_front(temp->right);
                    }
                    if (temp->left)
                    {
                        q.push_front(temp->left);
                    }
                }
                cout << temp->val << " ";
            }
            cout << endl;
            isLeftToRight = !isLeftToRight;
        }
    }
};
int main()
{
    Binarytree b;
    b.insertion(10);
    b.insertion(7);
    b.insertion(15);
    b.insertion(8);
    b.insertion(0);
    b.insertion(19);
    b.insertion(11);
    b.insertion(2);
    b.insertion(9);
    b.insertion(90);
    b.insertion(81);
    cout << "Level Order Traversal" << endl;
    b.levelOrderTraversal();
    cout << endl;
    cout << endl;
    cout << "Zig Zag Traversal" << endl;

    b.zigzagTraversal();
}