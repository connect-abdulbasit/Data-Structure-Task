#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
public:
    int profit; // Profit or loss value
    Node *left;
    Node *right;

    Node(int x) : profit(x), left(NULL), right(NULL) {}
};

class StockProfitAnalyzer
{
public:
    int maxProfitPath(Node *root)
    {
        int maxPath = 0;
        calculateMaxPath(root, maxPath);
        return maxPath;
    }

private:
    int calculateMaxPath(Node *node, int &maxPath)
    {
        if (!node)
            return 0;

        int leftMax = calculateMaxPath(node->left, maxPath);
        int rightMax = calculateMaxPath(node->right, maxPath);

        int currentMax = node->profit + leftMax + rightMax;

        maxPath = max(maxPath, currentMax);

        return node->profit + max(leftMax, rightMax);
    }
};

int main()
{
    Node *root = new Node(10);
    root->left = new Node(2);
    root->right = new Node(10);
    root->left->left = new Node(20);
    root->left->right = new Node(1);
    root->right->right = new Node(-25);
    root->right->right->left = new Node(3);
    root->right->right->right = new Node(4);

    /*
               10
             /   \
            2     10
          /  \     \
        20   1     -25
             \     /
              3   4


              20->2->10->10->=42 maximum profit
    */

    StockProfitAnalyzer analyzer;
    int maxProfit = analyzer.maxProfitPath(root);
    cout << "Maximum Profit Path: " << maxProfit << endl;

    return 0;
}
