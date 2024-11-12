#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node
{
    vector<int> keys;
    vector<Node *> children;
    Node *parent;
    bool isLeaf;
    Node() : parent(nullptr), isLeaf(true) {}
};

Node *createNode()
{
    return new Node();
}

Node *findLeaf(Node *root, int key)
{
    Node *current = root;
    while (!current->isLeaf)
    {
        if (key < current->keys[0])
            current = current->children[0];
        else if (current->keys.size() == 1 || key < current->keys[1])
            current = current->children[1];
        else
            current = current->children[2];
    }
    return current;
}

void split(Node *&root, Node *node)
{
    int middleKey = node->keys[1];
    Node *leftChild = createNode();
    Node *rightChild = createNode();

    leftChild->keys.push_back(node->keys[0]);
    rightChild->keys.push_back(node->keys[2]);
    leftChild->isLeaf = rightChild->isLeaf = node->isLeaf;

    if (!node->isLeaf)
    {
        leftChild->children = {node->children[0], node->children[1]};
        rightChild->children = {node->children[2], node->children[3]};
        for (Node *child : leftChild->children)
            child->parent = leftChild;
        for (Node *child : rightChild->children)
            child->parent = rightChild;
    }

    if (!node->parent)
    {
        Node *newRoot = createNode();
        newRoot->keys.push_back(middleKey);
        newRoot->children = {leftChild, rightChild};
        leftChild->parent = rightChild->parent = newRoot;
        newRoot->isLeaf = false;
        root = newRoot;
    }
    else
    {
        Node *parent = node->parent;
        parent->keys.push_back(middleKey);
        sort(parent->keys.begin(), parent->keys.end());

        auto it = find(parent->children.begin(), parent->children.end(), node);
        int index = distance(parent->children.begin(), it);
        parent->children[index] = leftChild;
        parent->children.insert(parent->children.begin() + index + 1, rightChild);

        leftChild->parent = rightChild->parent = parent;

        if (parent->keys.size() == 3)
            split(root, parent);
    }
}

void insert(Node *&root, int key)
{

    if (!root)
    {
        root = createNode();
        root->keys.push_back(key);
        return;
    }

    Node *leaf = findLeaf(root, key);
    leaf->keys.push_back(key);
    sort(leaf->keys.begin(), leaf->keys.end());

    if (leaf->keys.size() == 3)
        split(root, leaf);
}

void levelOrderTraversal(Node *root)
{
    if (!root)
        return;

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        int levelSize = q.size();
        while (levelSize--)
        {
            Node *node = q.front();
            q.pop();

            for (int key : node->keys)
                cout << key << " ";
            cout << "| ";

            for (Node *child : node->children)
                q.push(child);
        }
        cout << endl;
    }
}

int main()
{
    Node *tree = nullptr;

    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 5);
    insert(tree, 15);
    insert(tree, 25);
    insert(tree, 30);

    cout << "Tree: " << endl;
    levelOrderTraversal(tree);

    return 0;
}
