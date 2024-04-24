#include <iostream>
#include "BinarySearchTree.h"

int main() {
    // Создаем объекты деревьев
    BinarySearchTree tree1;
    BinarySearchTree tree2;

    // Вставляем элементы в первое дерево
    tree1.insert(5, 1);
    tree1.insert(3, 1);
    tree1.insert(7, 1);

    // Вставляем элементы во второе дерево
    tree2.insert(10, 1);
    tree2.insert(8, 1);
    tree2.insert(12, 1);

    // Печатаем деревья до операций
    std::cout << "Tree 1: ";
    tree1.printTree();
    std::cout << "Tree 2: ";
    tree2.printTree();

    // Выполняем операции CONCAT и CHANGE
    tree1.concat(tree2);
    tree1.change(2, tree2);

    // Печатаем дерево после операций
    std::cout << "Resulting Tree: ";
    tree1.printTree();

    return 0;
}