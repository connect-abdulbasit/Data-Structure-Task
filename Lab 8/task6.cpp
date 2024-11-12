#include <iostream>
using namespace std;

class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
private:
    Node *first;
    Node *second;
    Node *prev;

    void inorderTraversal(Node *root)
    {
        if (root == NULL)
            return;

        inorderTraversal(root->left);

        if (prev && root->val < prev->val)
        {

            if (first == NULL)
            {
                first = prev;
            }

            second = root;
        }
        prev = root;

        inorderTraversal(root->right);
    }

public:
    void recoverTree(Node *root)
    {
        first = second = prev = NULL;
        inorderTraversal(root);

        if (first && second)
        {
            swap(first->val, second->val);
        }
    }

    void inorderPrint(Node *root)
    {
        if (root == NULL)
            return;
        inorderPrint(root->left);
        cout << root->val << " ";
        inorderPrint(root->right);
    }
};

int main()
{

    Node *root = new Node(6);
    root->left = new Node(2);
    root->right = new Node(10);
    root->left->left = new Node(1);
    root->left->right = new Node(12);
    root->right->right = new Node(3);
    root->right->left = new Node(7);

    cout << "Original tree (with swapped nodes): ";
    Solution().inorderPrint(root);
    cout << endl;

    Solution().recoverTree(root);

    cout << "Recovered tree: ";
    Solution().inorderPrint(root);
    cout << endl;

    return 0;
}
