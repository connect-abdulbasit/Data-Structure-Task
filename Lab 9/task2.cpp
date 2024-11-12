#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

Node* leftRotate(Node *root) {
    Node *temp = root->right;
    Node *t2 = temp->left;
    temp->left = root;
    root->right = t2;
    return temp;
}

Node* rightRotate(Node *root) {
    Node *t1 = root->left;
    Node *t2 = t1->right;
    t1->right = root;
    root->left = t2;
    return t1;
}

int height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    int lh = height(root->left);
    int rh = height(root->right);
    return 1 + max(lh, rh);
}

Node* insert(Node *root, int data, int &count) {
    if (root == NULL) {
        return new Node(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data, count);
    } else {
        root->right = insert(root->right, data, count);
    }
    if (height(root->left) - height(root->right) > 1 && data < root->left->data) {
        count++;
        return rightRotate(root);
    } else if (height(root->right) - height(root->left) > 1 && data > root->right->data) {
        count++;
        return leftRotate(root);
    } else if (height(root->left) - height(root->right) > 1 && data > root->left->data) {
        count += 2;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (height(root->right) - height(root->left) > 1 && data < root->right->data) {
        count += 2;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    } else {
        return root;
    }
}

int totalRotations(Node *root, int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i], count);
    }
    return count;
}

int main() {
    int arr[] = {10, 20, 30, 25, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node *root = NULL;
    cout<<"Total rotation required is "<<totalRotations(root, arr, n);
    return 0;
}

