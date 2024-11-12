#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};
int height(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}
bool isValidAvl(Node *root)
{
    if (root == NULL)
    {
        return true;
    }
    int lh = height(root->left);
    int rh = height(root->right);
    if (abs(lh - rh) <= 1 && isValidAvl(root->left) && isValidAvl(root->right) && ((root->left == NULL) || ((root->left != NULL) && (root->left->data <= root->data))) && ((root->right == NULL) || ((root->right != NULL) && (root->right->data >= root->data))))
    {
        return true;
    }
    return false;
}
int main()
{
    Node *avlRoot = new Node(4);
    avlRoot->left = new Node(2);
    avlRoot->right = new Node(6);
    avlRoot->left->left = new Node(1);
    avlRoot->left->right = new Node(3);
    avlRoot->right->left = new Node(5);
    avlRoot->right->right = new Node(7);

    Node *nonAvlRoot = new Node(4);
    nonAvlRoot->left = new Node(2);
    nonAvlRoot->right = new Node(6);
    nonAvlRoot->left->left = new Node(1);
    nonAvlRoot->left->left->left = new Node(0);

    cout << "First tree is AVL and Binary Search Tree: ";
    if (isValidAvl(avlRoot))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }

    cout << "Second tree is AVL and Binary Search Tree: ";
    if (isValidAvl(nonAvlRoot))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
    return 0;
}
