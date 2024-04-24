//
// Created by stukenvitalii on 4/24/24.
//
#include "BinarySearchTree.h"

// Приватные методы

Node* BinarySearchTree::insertRecursive(Node* root, int data, int size) {
    if (root == nullptr)
        return new Node(data, size);

    if (data < root->data)
        root->left = insertRecursive(root->left, data, size);
    else if (data > root->data)
        root->right = insertRecursive(root->right, data, size);

    // Обновляем мощность поддерева
    root->subtreeSize = 1;
    if (root->left)
        root->subtreeSize += root->left->subtreeSize;
    if (root->right)
        root->subtreeSize += root->right->subtreeSize;

    return root;
}

Node* BinarySearchTree::deleteRecursive(Node* root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        root->left = deleteRecursive(root->left, data);
    else if (data > root->data)
        root->right = deleteRecursive(root->right, data);
    else {
        // Узел с одним или без детей
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Узел с двумя детьми: получаем минимальное значение из правого поддерева
        Node* temp = minValueNode(root->right);

        // Копируем значение минимального узла в текущий узел
        root->data = temp->data;

        // Удаляем минимальный узел из правого поддерева
        root->right = deleteRecursive(root->right, temp->data);
    }

    // Обновляем мощность поддерева
    root->subtreeSize = 1;
    if (root->left)
        root->subtreeSize += root->left->subtreeSize;
    if (root->right)
        root->subtreeSize += root->right->subtreeSize;

    return root;
}

Node* BinarySearchTree::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

void BinarySearchTree::concatRecursive(Node* root1, Node* root2) {
    if (root2 == nullptr)
        return;

    insert(root2->data, root2->subtreeSize);
    concatRecursive(root1, root2->left);
    concatRecursive(root1, root2->right);
}

void BinarySearchTree::eraseFromPosition(Node*& root, int p) {
    if (root == nullptr)
        return;

    if (p <= root->subtreeSize) {
        erase(root->data);
        return;
    }

    eraseFromPosition(root->right, p - (root->left ? root->left->subtreeSize : 0) - 1);
}

// Публичные методы

void BinarySearchTree::insert(int data, int size) {
    root = insertRecursive(root, data, size);
}

void BinarySearchTree::erase(int data) {
    root = deleteRecursive(root, data);
}

void BinarySearchTree::concat(BinarySearchTree& tree2) {
    concatRecursive(root, tree2.root);
}

void BinarySearchTree::change(int p, BinarySearchTree& tree2) {
    eraseFromPosition(root, p);
    concatRecursive(root, tree2.root);
}

void BinarySearchTree::printInorder(Node* node) {
    if (node == nullptr)
        return;
    printInorder(node->left);
    std::cout << "(" << node->data << ", " << node->subtreeSize << ") ";
    printInorder(node->right);
}

void BinarySearchTree::printTree() {
    printInorder(root);
    std::cout << std::endl;
}

