#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <queue>
#include <iomanip>
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

    AVLNode *deleteNode(AVLNode *node, int id)
    {
        if (!node)
            return nullptr;

        if (id < node->data.ID)
            node->left = deleteNode(node->left, id);
        else if (id > node->data.ID)
            node->right = deleteNode(node->right, id);
        else
        {
            if (!node->left || !node->right)
            {
                AVLNode *temp = node->left ? node->left : node->right;
                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else
            {
                AVLNode *temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data.ID);
            }
        }

        if (!node)
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode *findMin(AVLNode *node) const
    {
        AVLNode *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
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

    void update(int id, const string &newName, int newAge)
    {
        AVLNode *node = searchNode(root, id);
        if (node)
        {
            node->data.Name = newName;
            node->data.Age = newAge;
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
class BTreeNode
{
public:
    vector<Record> keys;
    vector<BTreeNode *> children;
    bool isLeaf;
    int t;

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

    void remove(int id)
    {
        int idx = findKey(id);

        if (idx < keys.size() && keys[idx].ID == id)
        {
            if (isLeaf)
                removeFromLeaf(idx);
            else
                removeFromNonLeaf(idx);
        }
        else
        {
            if (isLeaf)
                return;

            bool flag = (idx == keys.size());

            if (children[idx]->keys.size() < t)
                fill(idx);

            if (flag && idx > keys.size())
                children[idx - 1]->remove(id);
            else
                children[idx]->remove(id);
        }
    }

    int findKey(int id)
    {
        int idx = 0;
        while (idx < keys.size() && keys[idx].ID < id)
            ++idx;
        return idx;
    }

    void removeFromLeaf(int idx)
    {
        keys.erase(keys.begin() + idx);
    }

    void removeFromNonLeaf(int idx)
    {
        Record k = keys[idx];

        if (children[idx]->keys.size() >= t)
        {
            Record pred = getPred(idx);
            keys[idx] = pred;
            children[idx]->remove(pred.ID);
        }
        else if (children[idx + 1]->keys.size() >= t)
        {
            Record succ = getSucc(idx);
            keys[idx] = succ;
            children[idx + 1]->remove(succ.ID);
        }
        else
        {
            merge(idx);
            children[idx]->remove(k.ID);
        }
    }

    Record getPred(int idx)
    {
        BTreeNode *cur = children[idx];
        while (!cur->isLeaf)
            cur = cur->children[cur->keys.size()];
        return cur->keys.back();
    }

    Record getSucc(int idx)
    {
        BTreeNode *cur = children[idx + 1];
        while (!cur->isLeaf)
            cur = cur->children[0];
        return cur->keys.front();
    }

    void fill(int idx)
    {
        if (idx != 0 && children[idx - 1]->keys.size() >= t)
            borrowFromPrev(idx);
        else if (idx != keys.size() && children[idx + 1]->keys.size() >= t)
            borrowFromNext(idx);
        else
        {
            if (idx != keys.size())
                merge(idx);
            else
                merge(idx - 1);
        }
    }

    void borrowFromPrev(int idx)
    {
        BTreeNode *child = children[idx];
        BTreeNode *sibling = children[idx - 1];

        child->keys.insert(child->keys.begin(), keys[idx - 1]);

        if (!child->isLeaf)
            child->children.insert(child->children.begin(), sibling->children.back());

        keys[idx - 1] = sibling->keys.back();
        sibling->keys.pop_back();

        if (!sibling->isLeaf)
            sibling->children.pop_back();
    }

    void borrowFromNext(int idx)
    {
        BTreeNode *child = children[idx];
        BTreeNode *sibling = children[idx + 1];

        child->keys.push_back(keys[idx]);

        if (!child->isLeaf)
            child->children.push_back(sibling->children.front());

        keys[idx] = sibling->keys.front();
        sibling->keys.erase(sibling->keys.begin());

        if (!sibling->isLeaf)
            sibling->children.erase(sibling->children.begin());
    }

    void merge(int idx)
    {
        BTreeNode *child = children[idx];
        BTreeNode *sibling = children[idx + 1];

        child->keys.push_back(keys[idx]);

        for (int i = 0; i < sibling->keys.size(); ++i)
            child->keys.push_back(sibling->keys[i]);

        if (!child->isLeaf)
        {
            for (int i = 0; i < sibling->children.size(); ++i)
                child->children.push_back(sibling->children[i]);
        }

        keys.erase(keys.begin() + idx);
        children.erase(children.begin() + idx + 1);

        delete sibling;
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

    BTreeNode *search(int id) const
    {
        if (!root)
            return nullptr;
        return root->search(id);
    }

    void update(int id, string name, int age)
    {
        BTreeNode *node = search(id);
        if (node)
        {
            for (auto &key : node->keys)
            {
                if (key.ID == id)
                {
                    key.Name = name;
                    key.Age = age;
                    break;
                }
            }
        }
    }

    void remove(int id)
    {
        if (!root)
            return;

        root->remove(id);

        if (root->keys.empty())
        {
            BTreeNode *tmp = root;
            if (root->isLeaf)
                root = nullptr;
            else
                root = root->children[0];

            delete tmp;
        }
    }

    void traverse()
    {
        if (root)
            root->traverse();
    }
};
void performanceTestBST()
{
    vector<int> sizes = {1000, 10000, 50000};
    cout << setw(24) << left << "Tree Type" << setw(20) << "Size" << setw(20) << "Insert Time (ms)" << setw(20) << "Search Time (ms)" << setw(20) << "Update Time(ms)" << setw(20) << "Delete Time (ms)" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

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
        cout << setw(24) << left << "BST" << setw(20) << size << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i)
        {
            bst.search(i + 1);
        }
        end = chrono::high_resolution_clock::now();
        cout << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i)
        {
            bst.update(i + 1, "update", i + 1 % 100);
        }
        end = chrono::high_resolution_clock::now();
        cout << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i)
        {

            bst.remove(i + 1);
        }
        end = chrono::high_resolution_clock::now();
        cout << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    }
}

void performanceTestBTree(int degree)
{
    vector<int> sizes = {1000, 10000, 50000};
    cout << setw(24) << left << "Tree Type" << setw(20) << "Size" << setw(20) << "Insert Time (ms)" << setw(20) << "Search Time (ms)" << setw(20) << "Update Time (ms)" << setw(20) << "Delete Time (ms)" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

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
        cout << setw(24) << left << "B-Tree" << setw(20) << size << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i)
        {
            bTree.search(i + 1);
        }
        end = chrono::high_resolution_clock::now();
        cout << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i)
        {
            bTree.update(i + 1, "update", i + 1 % 100);
        }
        end = chrono::high_resolution_clock::now();
        cout << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i)
        {
            bTree.remove(i + 1);
        }
        end = chrono::high_resolution_clock::now();
        cout << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    }
}

void performanceTestAVL()
{
    vector<int> sizes = {1000, 10000, 50000};
    cout << setw(24) << left << "Tree Type" << setw(20) << "Size" << setw(20) << "Insert Time (ms)" << setw(20) << "Search Time (ms)" << setw(20) << "Update Time (ms)" << setw(20) << "Delete Time (ms)" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

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
        cout << setw(24) << left << "AVL" << setw(20) << size << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i)
        {
            avl.search(i + 1);
        }
        end = chrono::high_resolution_clock::now();
        cout << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i)
        {
            avl.update(i + 1, "update", i + 1 % 100);
        }
        end = chrono::high_resolution_clock::now();
        cout << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i)
        {
            avl.remove(i + 1);
        }
        end = chrono::high_resolution_clock::now();
        cout << setw(20) << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    }
}

int main()
{

    int bTreeDegree = 3;

    cout << "Performance Testing of Different Tree Data Structures with Various Database Sizes" << endl;
    cout << "=====================================================================================" << endl;

    cout << "\nTesting BST:" << endl;
    performanceTestBST();

    cout << "\nTesting AVL Tree:" << endl;
    performanceTestAVL();

    cout << "\nTesting B-Tree:" << endl;
    performanceTestBTree(bTreeDegree);

    return 0;
}