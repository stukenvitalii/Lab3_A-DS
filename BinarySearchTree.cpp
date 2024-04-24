//
// Created by stukenvitalii on 4/24/24.
//
#include "BinarySearchTree.h"

// Приватные методы

Node* BinarySearchTree::insertRecursive(Node* root, char data, int size) {
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

Node* BinarySearchTree::deleteRecursive(Node* root, char data) {
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

void BinarySearchTree::eraseFromPosition(Node*& root, int p1, int p2) {
    if (root == nullptr)
        return;

    // Удаляем узлы, начиная с позиции p1 до позиции p2
    if (root->subtreeSize >= p1 && root->subtreeSize <= p2) {
        root = deleteRecursive(root, root->data); // Удаляем текущий узел
        return;
    }

    // Если текущий узел не в диапазоне, рекурсивно вызываем для правого поддерева
    if (root->subtreeSize < p1)
        eraseFromPosition(root->right, p1 - root->subtreeSize, p2 - root->subtreeSize);
        // Если текущий узел в диапазоне, рекурсивно вызываем для обоих поддеревьев
    else if (root->subtreeSize > p2) {
        eraseFromPosition(root->left, p1, p2);
        eraseFromPosition(root->right, p1, p2);
    }
}

void BinarySearchTree::copyRecursive(Node*& dest, Node* source) {
    if (source == nullptr)
        return;

    // Копируем узел из второго дерева
    dest = new Node(source->data, source->subtreeSize);

    // Рекурсивно копируем левое и правое поддерево
    copyRecursive(dest->left, source->left);
    copyRecursive(dest->right, source->right);
}

void BinarySearchTree::eraseSubtree(Node*& node, Node* otherNode) {
    if (otherNode == nullptr) {
        return;
    }

    eraseSubtree(node, otherNode->left);
    eraseSubtree(node, otherNode->right);

    eraseRecursive(node, otherNode->data);
}

void BinarySearchTree::eraseRecursive(Node*& node, int data) {
    if (node == nullptr) {
        return;
    }

    if (data < node->data) {
        eraseRecursive(node->left, data);
    } else if (data > node->data) {
        eraseRecursive(node->right, data);
    } else {
        // Нашли узел для удаления
        Node* temp = node;
        if (node->left == nullptr) {
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            node = node->left;
            delete temp;
        } else {
            // Узел имеет двух потомков
            Node* minRight = findMin(node->right);
            node->data = minRight->data;
            eraseRecursive(node->right, minRight->data);
        }
    }
}

Node* BinarySearchTree::findMin(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}


// Публичные методы

void BinarySearchTree::insert(char data, int size) {
    root = insertRecursive(root, data, size);
}

void BinarySearchTree::erase(int p1, int p2) {
    eraseFromPosition(root, p1, p2);
}

void BinarySearchTree::erase(const BinarySearchTree& other) {
    eraseSubtree(root, other.root);
}



void BinarySearchTree::concat(BinarySearchTree& tree2) {
    concatRecursive(root, tree2.root);
}

void BinarySearchTree::change(int p, BinarySearchTree& tree2) {
    eraseFromPosition(root, p, p + tree2.root->subtreeSize - 1); // Удаляем элементы, начиная с позиции p
    copyRecursive(root, tree2.root); // Копируем элементы из второго дерева
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

int BinarySearchTree::subtreeSize(Node* root) const {
    if (root == nullptr)
        return 0;
    return root->subtreeSize;
}

int BinarySearchTree::getSize() const {
    return subtreeSize(root);
}

