#include <iostream>
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
};

Binarytree *balancedBinaryTree(Binarytree *root, int arr[], int l, int r)
{
    if (l > r)
    {
        return root;
    }
    int mid = (l + r) / 2;
    root->insertion(arr[mid]);
    balancedBinaryTree(root, arr, l, mid - 1);
    balancedBinaryTree(root, arr, mid + 1, r);
    return root;
}

int main()
{
    int sortedArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Binarytree *root = new Binarytree();
    root = balancedBinaryTree(root, sortedArray, 0, 9);
    root->levelOrderTraversal();
    return 0;
}
