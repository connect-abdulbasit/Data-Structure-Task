#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Node
{
public:
    int val;
    Node *left;
    Node *right;

    Node(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
public:
    string serialize(Node *root)
    {
        if (!root)
            return "#,";

        string result = to_string(root->val) + ",";
        result += serialize(root->left);
        result += serialize(root->right);

        return result;
    }

    Node *deserializeHelper(istringstream &ss)
    {
        string token;
        getline(ss, token, ',');

        if (token == "#")
        {
            return NULL;
        }

        Node *node = new Node(stoi(token));
        node->left = deserializeHelper(ss);
        node->right = deserializeHelper(ss);

        return node;
    }

    Node *deserialize(string data)
    {
        istringstream ss(data);
        return deserializeHelper(ss);
    }
};

void printTree(Node *root)
{
    if (!root)
        return;
    cout << root->val << " ";
    printTree(root->left);
    printTree(root->right);
}

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->right->left = new Node(4);
    root->right->right = new Node(5);

    Codec codec;
    string serialized = codec.serialize(root);
    cout << "Serialized Tree: " << serialized << endl;

    Node *deserializedRoot = codec.deserialize(serialized);
    cout << "Deserialized Tree (Pre-order): ";
    printTree(deserializedRoot);
    cout << endl;

    return 0;
}
