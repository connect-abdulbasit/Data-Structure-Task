#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <random>

using namespace std;

struct Record
{
    int ID;
    string Name;
    int Age;
};

class BSTNode
{
public:
    Record data;
    BSTNode *left, *right;
    BSTNode(Record rec) : data(rec), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    BSTNode *root;

    BSTNode *insertNode(BSTNode *node, const Record &rec)
    {
        if (!node)
            return new BSTNode(rec);
        if (rec.ID < node->data.ID)
            node->left = insertNode(node->left, rec);
        else if (rec.ID > node->data.ID)
            node->right = insertNode(node->right, rec);
        return node;
    }

    BSTNode *searchNode(BSTNode *node, int id) const
    {
        if (!node || node->data.ID == id)
            return node;
        return id < node->data.ID ? searchNode(node->left, id) : searchNode(node->right, id);
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

    BSTNode *findMin(BSTNode *node) const
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    void inOrder(BSTNode *node) const
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

    void insert(const Record &rec)
    {
        root = insertNode(root, rec);
    }

    const Record *search(int id) const
    {
        BSTNode *result = searchNode(root, id);
        return result ? &result->data : nullptr;
    }

    void update(int id, const string &newName, int newAge)
    {
        Record *record = const_cast<Record *>(search(id));
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

    void display() const
    {
        inOrder(root);
    }
};

vector<Record> generateData(int size)
{
    vector<Record> data(size);
    for (int i = 0; i < size; ++i)
    {
        data[i] = {i + 1, "Name_" + to_string(i + 1), 20 + (i % 30)};
    }
    shuffle(data.begin(), data.end(), mt19937(random_device{}()));
    return data;
}

void performanceTest(int dataSize)
{
    vector<Record> data = generateData(dataSize);
    BST bst;

    auto start = chrono::high_resolution_clock::now();
    for (const auto &rec : data)
    {
        bst.insert(rec);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "BST Insert Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 20; ++i)
    {
        bst.search(i + 1);
    }
    end = chrono::high_resolution_clock::now();
    cout << "BST Search Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << endl;
}

int main()
{
    int dataSize = 10000;
    cout << "Performance Testing with " << dataSize << " records:" << endl;
    performanceTest(dataSize);
    return 0;
}
