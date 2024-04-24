#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

struct Node {
    char data;
    int subtreeSize; // Хранимая мощность
    Node* left;
    Node* right;

    Node(char val, int size) : data(val), subtreeSize(size), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    // Приватные методы
    Node* insertRecursive(Node* root, char data, int size);
    Node* deleteRecursive(Node* root, char data);
    Node* minValueNode(Node* node);
    void copyRecursive(Node*& dest, Node* source);
    void concatRecursive(Node* root1, Node* root2);
    void eraseFromPosition(Node*& root, int p1, int p2);
    void printInorder(Node* node);
    void eraseSubtree(Node *&node, Node *otherNode);
    Node *findMin(Node *node) const;
    void eraseRecursive(Node *&node, int data);
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() = default;
    // Публичные методы
    void insert(char data, int size);
    void erase(int p1, int p2);
    void concat(BinarySearchTree& tree2);
    void change(int p, BinarySearchTree& tree2);
    void printTree();
    int getSize() const;
    int subtreeSize(Node *root) const;

    void erase(const BinarySearchTree &other);



};

#endif // BINARY_SEARCH_TREE_H
