#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <random>

using namespace std;

class Record
{
public:
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

class AVLNode
{
public:
    Record data;
    AVLNode *left, *right;
    int height;
    AVLNode(Record rec) : data(rec), left(nullptr), right(nullptr), height(1) {}
};

class AVL
{
private:
    AVLNode *root;

    int getHeight(AVLNode *node) const
    {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode *node) const
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode *rotateRight(AVLNode *y)
    {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        return x;
    }

    AVLNode *rotateLeft(AVLNode *x)
    {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    AVLNode *insertNode(AVLNode *node, const Record &rec)
    {
        if (!node)
            return new AVLNode(rec);

        if (rec.ID < node->data.ID)
            node->left = insertNode(node->left, rec);
        else if (rec.ID > node->data.ID)
            node->right = insertNode(node->right, rec);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && rec.ID < node->left->data.ID)
            return rotateRight(node);

        if (balance < -1 && rec.ID > node->right->data.ID)
            return rotateLeft(node);

        if (balance > 1 && rec.ID > node->left->data.ID)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && rec.ID < node->right->data.ID)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode *searchNode(AVLNode *node, int id) const
    {
        if (!node || node->data.ID == id)
            return node;
        return id < node->data.ID ? searchNode(node->left, id) : searchNode(node->right, id);
    }

    void inOrder(AVLNode *node) const
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
    AVL() : root(nullptr) {}

    void insert(const Record &rec)
    {
        root = insertNode(root, rec);
    }

    const Record *search(int id) const
    {
        AVLNode *result = searchNode(root, id);
        return result ? &result->data : nullptr;
    }

    void display() const
    {
        inOrder(root);
    }
};
class BTreeNode
{
public:
    vector<Record> keys;          // Keys stored in this node
    vector<BTreeNode *> children; // Pointers to child nodes
    bool isLeaf;                  // True if this is a leaf node
    int t;                        // Minimum degree

    BTreeNode(int t, bool isLeaf) : t(t), isLeaf(isLeaf) {}

    void traverse()
    {
        int i;
        for (i = 0; i < keys.size(); i++)
        {
            if (!isLeaf)
                children[i]->traverse();
            cout << "ID: " << keys[i].ID << ", Name: " << keys[i].Name
                 << ", Age: " << keys[i].Age << endl;
        }
        if (!isLeaf)
            children[i]->traverse();
    }

    BTreeNode *search(int id)
    {
        int i = 0;
        while (i < keys.size() && id > keys[i].ID)
            i++;

        if (i < keys.size() && keys[i].ID == id)
            return this;

        if (isLeaf)
            return nullptr;

        return children[i]->search(id);
    }

    void insertNonFull(const Record &rec)
    {
        int i = keys.size() - 1;

        if (isLeaf)
        {
            keys.resize(keys.size() + 1);
            while (i >= 0 && rec.ID < keys[i].ID)
            {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = rec;
        }
        else
        {
            while (i >= 0 && rec.ID < keys[i].ID)
                i--;
            i++;

            if (children[i]->keys.size() == 2 * t - 1)
            {
                splitChild(i, children[i]);

                if (rec.ID > keys[i].ID)
                    i++;
            }
            children[i]->insertNonFull(rec);
        }
    }

    void splitChild(int i, BTreeNode *y)
    {
        BTreeNode *z = new BTreeNode(y->t, y->isLeaf);
        z->keys.resize(t - 1);

        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];

        if (!y->isLeaf)
        {
            z->children.resize(t);
            for (int j = 0; j < t; j++)
                z->children[j] = y->children[j + t];
        }

        y->keys.resize(t - 1);
        y->children.resize(t);

        children.insert(children.begin() + i + 1, z);
        keys.insert(keys.begin() + i, y->keys[t - 1]);
    }
};

class BTree
{
private:
    BTreeNode *root;
    int t;

public:
    BTree(int t) : t(t), root(nullptr) {}

    void insert(const Record &rec)
    {
        if (!root)
        {
            root = new BTreeNode(t, true);
            root->keys.push_back(rec);
        }
        else
        {
            if (root->keys.size() == 2 * t - 1)
            {
                BTreeNode *newRoot = new BTreeNode(t, false);
                newRoot->children.push_back(root);
                newRoot->splitChild(0, root);
                root = newRoot;
            }
            root->insertNonFull(rec);
        }
    }

    const BTreeNode *search(int id) const
    {
        if (!root)
            return nullptr;
        return root->search(id);
    }
    void display() const
    {
        if (root)
            root->traverse();
    }
};
void performanceTestBST()
{
    vector<int> sizes = {1000, 10000, 50000};
    for (int size : sizes)
    {
        vector<Record> data = generateData(size);
        BST bst;

        auto start = chrono::high_resolution_clock::now();
        for (const auto &rec : data)
        {
            bst.insert(rec);
        }
        auto end = chrono::high_resolution_clock::now();
        cout << "BST Insert Time for " << size << " records: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms" << endl;

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < 20; ++i)
        {
            bst.search(i + 1);
        }
        end = chrono::high_resolution_clock::now();
        cout << "BST Search Time for 20 records in " << size << " size database:"
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms" << endl;
    }
}

void performanceTestAVL()
{
    vector<int> sizes = {1000, 10000, 50000};
    for (int size : sizes)
    {
        vector<Record> data = generateData(size);
        AVL avl;

        auto start = chrono::high_resolution_clock::now();
        for (const auto &rec : data)
        {
            avl.insert(rec);
        }
        auto end = chrono::high_resolution_clock::now();
        cout << "AVL Insert Time for " << size << " records: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms" << endl;

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < 20; ++i)
        {
            avl.search(i + 1);
        }
        end = chrono::high_resolution_clock::now();
        cout << "AVL Search Time for 20 records in " << size << " size database:"
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms" << endl;
    }
}

void performanceTestBTree(int degree)
{
    vector<int> sizes = {1000, 10000, 50000};
    for (int size : sizes)
    {
        vector<Record> data = generateData(size);
        BTree bTree(degree);

        auto start = chrono::high_resolution_clock::now();
        for (const auto &rec : data)
        {
            bTree.insert(rec);
        }
        auto end = chrono::high_resolution_clock::now();
        cout << "B-Tree Insert Time for " << size << " records: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms" << endl;

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < 20; ++i)
        {
            bTree.search(i + 1);
        }
        end = chrono::high_resolution_clock::now();
        cout << "B-Tree Search Time for 20 records in " << size << " size database: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms" << endl;
    }
}
int main()
{
    int bTreeDegree = 3;

    cout << "Performance Testing" << endl;

    cout << "\nTesting BST:" << endl;
    performanceTestBST();

    cout << "\nTesting AVL Tree:" << endl;
    performanceTestAVL();

    cout << "\nTesting B-Tree:" << endl;
    performanceTestBTree(bTreeDegree);

    return 0;
}