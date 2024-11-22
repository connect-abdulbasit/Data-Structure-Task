#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <random>

using namespace std;

// Record structure
struct Record
{
    int ID;
    string Name;
    int Age;
};

// Binary Search Tree (BST) Implementation
class BSTNode
{
public:
    Record data;
    BSTNode *left;
    BSTNode *right;

    BSTNode(Record rec) : data(rec), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    BSTNode *root;

    BSTNode *insertNode(BSTNode *node, Record rec)
    {
        if (node == nullptr)
            return new BSTNode(rec);
        if (rec.ID < node->data.ID)
            node->left = insertNode(node->left, rec);
        else if (rec.ID > node->data.ID)
            node->right = insertNode(node->right, rec);
        return node;
    }

    BSTNode *searchNode(BSTNode *node, int id)
    {
        if (!node || node->data.ID == id)
            return node;
        if (id < node->data.ID)
            return searchNode(node->left, id);
        return searchNode(node->right, id);
    }

    BSTNode *deleteNode(BSTNode *node, int id)
    {
        if (!node)
            return nullptr;
        if (id < node->data.ID)
            node->left = deleteNode(node->left, id);
        else if (id > node->data.ID)
            node->right = deleteNode(node->right, id);
        else
        {
            if (!node->left)
            {
                BSTNode *temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right)
            {
                BSTNode *temp = node->left;
                delete node;
                return temp;
            }
            BSTNode *minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = deleteNode(node->right, minNode->data.ID);
        }
        return node;
    }

    BSTNode *findMin(BSTNode *node)
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    void inOrder(BSTNode *node)
    {
        if (node)
        {
            inOrder(node->left);
            cout << "ID: " << node->data.ID << ", Name: " << node->data.Name
                 << ", Age: " << node->data.Age << endl;
            inOrder(node->right);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(Record rec)
    {
        root = insertNode(root, rec);
    }

    Record *search(int id)
    {
        BSTNode *result = searchNode(root, id);
        return result ? &result->data : nullptr;
    }

    void update(int id, const string &newName, int newAge)
    {
        Record *record = search(id);
        if (record)
        {
            record->Name = newName;
            record->Age = newAge;
        }
    }

    void remove(int id)
    {
        root = deleteNode(root, id);
    }

    void display()
    {
        inOrder(root);
    }
};

// AVL Tree Implementation
// Similar to BST but with balancing logic
// For brevity, AVL tree code is omitted here, but you can add the balancing rotations (left-right, right-left, etc.).

// Dummy Data Generation
vector<Record> generateData(int size)
{
    vector<Record> data;
    for (int i = 1; i <= size; ++i)
    {
        data.push_back({i, "Name_" + to_string(i), 20 + (i % 30)});
    }

    // Use a random number generator
    random_device rd;                     // Seed for random number generator
    mt19937 g(rd());                      // Mersenne Twister random number generator
    shuffle(data.begin(), data.end(), g); // Use std::shuffle

    return data;
}

// Performance Testing
void performanceTest(int dataSize)
{
    vector<Record> data = generateData(dataSize);

    BST bst;
    // AVL and B-Tree classes would be initialized here.

    // Insert Performance
    auto start = chrono::high_resolution_clock::now();
    for (const auto &rec : data)
    {
        bst.insert(rec);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "BST Insert Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << endl;

    // Search Performance
    start = chrono::high_resolution_clock::now();
    for (int i = 1; i <= 20; ++i)
    {
        bst.search(i);
    }
    end = chrono::high_resolution_clock::now();
    cout << "BST Search Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << endl;

    // Similarly, test Update and Delete.
}

// Main Function
int main()
{
    int dataSize = 10000; // Change to 1000, 10,000, 50,000 as needed.

    cout << "Performance Testing with " << dataSize << " records:" << endl;
    performanceTest(dataSize);

    return 0;
}
