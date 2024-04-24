#include <iostream>
#include "BinarySearchTree.h"

// Функция для генерации случайной последовательности латинских букв
std::string generateRandomSequence(int length) {
    std::string sequence;
    for (int i = 0; i < length; ++i) {
        char letter = 'A' + rand() % 26; // Генерируем случайную букву от 'A' до 'Z'
        sequence += letter;
    }
    return sequence;
}

int main() {
    // Инициализируем генератор случайных чисел
    srand(time(nullptr));

    // Генерируем случайные последовательности для A, B, C, D, E
    std::string sequenceA = generateRandomSequence(5);
    std::string sequenceB = generateRandomSequence(5);
    std::string sequenceC = generateRandomSequence(5);
    std::string sequenceD = generateRandomSequence(5);
    std::string sequenceE = generateRandomSequence(5);

    std::cout << "Initial sequences:" << std::endl;
    std::cout << "A: " << sequenceA << std::endl;
    std::cout << "B: " << sequenceB << std::endl;
    std::cout << "C: " << sequenceC << std::endl;
    std::cout << "D: " << sequenceD << std::endl;
    std::cout << "E: " << sequenceE << std::endl;

    // Создаем деревья для A, B, C, D, E
    BinarySearchTree treeA {};
    BinarySearchTree treeB {};
    BinarySearchTree treeC {};
    BinarySearchTree treeD {};
    BinarySearchTree treeE {};

    // Вставляем элементы в деревья
    for (char letter : sequenceA)
        treeA.insert(letter, 1);
    for (char letter : sequenceB)
        treeB.insert(letter, 1);
    for (char letter : sequenceC)
        treeC.insert(letter, 1);
    for (char letter : sequenceD)
        treeD.insert(letter, 1);
    for (char letter : sequenceE)
        treeE.insert(letter, 1);

    // Вычисляем значение выражения ((A ∪ B) \ C) ∩ D ⊕ E

    // Создаем дерево для выражения (A ∪ B)
    BinarySearchTree unionAB {};
    unionAB.concat(treeA);
    unionAB.concat(treeB);
    std::cout << "A ∪ B: ";
    unionAB.printTree();

    // Создаем дерево для выражения ((A ∪ B) \ C)
    BinarySearchTree differenceABC {};
    differenceABC.concat(unionAB);
    differenceABC.concat(unionAB);
    differenceABC.erase(treeC);

    std::cout << "(A ∪ B) \\ C: " ;
    differenceABC.printTree();

    // Создаем дерево для выражения ((A ∪ B) \ C) ∩ D
    BinarySearchTree intersectionABCD {};
    intersectionABCD.concat(differenceABC);
    intersectionABCD.concat(treeD);
    std::cout << "(A ∪ B) \\ C) ∩ D: ";
    intersectionABCD.printTree();

    // Создаем дерево для выражения ((A ∪ B) \ C) ∩ D ⊕ E
    BinarySearchTree result {};
    result.concat(intersectionABCD);
    result.change(0, treeE);

    // Выводим результат
    std::cout << "Result: ";
    result.printTree();

    return 0;
}