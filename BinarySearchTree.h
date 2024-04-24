#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

struct Node {
    int data;
    int subtreeSize; // Хранимая мощность
    Node* left;
    Node* right;

    Node(int val, int size) : data(val), subtreeSize(size), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    // Приватные методы
    Node* insertRecursive(Node* root, int data, int size);
    Node* deleteRecursive(Node* root, int data);
    Node* minValueNode(Node* node);
    void concatRecursive(Node* root1, Node* root2);
    void eraseFromPosition(Node*& root, int p);
    void printInorder(Node* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    // Публичные методы
    void insert(int data, int size);
    void erase(int data);
    void concat(BinarySearchTree& tree2);
    void change(int p, BinarySearchTree& tree2);
    void printTree();
};

#endif // BINARY_SEARCH_TREE_H
