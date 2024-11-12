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

void merge(Node *&root, Node *node)
{
    Node *parent = node->parent;

    int index = 0;
    while (index < parent->children.size() && parent->children[index] != node)
    {
        index++;
    }

    if (index > 0)
    {
        Node *leftSibling = parent->children[index - 1];
        leftSibling->keys.push_back(parent->keys[index - 1]);
        leftSibling->keys.insert(leftSibling->keys.end(), node->keys.begin(), node->keys.end());
        parent->keys.erase(parent->keys.begin() + index - 1);
        parent->children.erase(parent->children.begin() + index);

        if (parent == root && parent->keys.empty())
        {
            root = leftSibling;
            root->parent = nullptr;
        }
        else if (parent->keys.size() == 0)
        {
            merge(root, parent);
        }
    }
    else
    {
        Node *rightSibling = parent->children[index + 1];
        rightSibling->keys.insert(rightSibling->keys.begin(), parent->keys[index]);
        rightSibling->keys.insert(rightSibling->keys.begin(), node->keys.begin(), node->keys.end());
        parent->keys.erase(parent->keys.begin() + index);
        parent->children.erase(parent->children.begin() + index);

        if (parent == root && parent->keys.empty())
        {
            root = rightSibling;
            root->parent = nullptr;
        }
        else if (parent->keys.size() == 0)
        {
            merge(root, parent);
        }
    }
}

void deleteKey(Node *&root, int key)
{

    Node *leaf = findLeaf(root, key);
    auto it = find(leaf->keys.begin(), leaf->keys.end(), key);
    if (it == leaf->keys.end())
    {
        cout << "Key not found in the tree!" << endl;
        return;
    }

    leaf->keys.erase(it);

    if (leaf->keys.size() < 1 && leaf != root)
    {
        merge(root, leaf);
    }
}

void collectKeys(Node *node, vector<int> &keys)
{
    if (!node)
        return;

    for (int key : node->keys)
        keys.push_back(key);

    for (Node *child : node->children)
        collectKeys(child, keys);
}

Node *merge2trees(Node *tree1, Node *tree2)
{
    vector<int> keys;

    collectKeys(tree1, keys);
    collectKeys(tree2, keys);

    sort(keys.begin(), keys.end());

    Node *mergedTree = nullptr;
    for (int key : keys)
        insert(mergedTree, key);

    return mergedTree;
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
    Node *tree1 = nullptr;
    Node *tree2 = nullptr;

    insert(tree1, 10);
    insert(tree1, 20);
    insert(tree1, 5);
    insert(tree1, 15);
    insert(tree1, 25);
    insert(tree1, 30);

    insert(tree2, 11);
    insert(tree2, 12);
    insert(tree2, 13);
    insert(tree2, 14);
    insert(tree2, 16);
    insert(tree2, 17);

    cout << "Tree 1:" << endl;
    levelOrderTraversal(tree1);

    cout << "Tree 2:" << endl;
    levelOrderTraversal(tree2);

    Node *mergedTree = merge2trees(tree1, tree2);

    cout << "Merged Tree:" << endl;
    levelOrderTraversal(mergedTree);

    return 0;
}
