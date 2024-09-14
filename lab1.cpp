#include <iostream>
#include <iomanip> // Для вывода с фиксированной точностью

// Структура для узла двоичного дерева
struct Vertex {
    int Data;      // Данные в узле
    Vertex *Left;  // Левый потомок
    Vertex *Right; // Правый потомок

    Vertex(int data) : Data(data), Left(nullptr), Right(nullptr) {}
};

// Обход дерева сверху вниз (прямой обход)
void Obhod1(Vertex *p) {
    if (p != nullptr) {
        std::cout << p->Data << " "; // Обработка узла
        Obhod1(p->Left);             // Обход левого поддерева
        Obhod1(p->Right);            // Обход правого поддерева
    }
}

// Обход дерева снизу вверх (обратный обход)
void Obhod2(Vertex *p) {
    if (p != nullptr) {
        Obhod2(p->Left);             // Обход левого поддерева
        Obhod2(p->Right);            // Обход правого поддерева
        std::cout << p->Data << " "; // Обработка узла
    }
}

void Obhod3 (Vertex *p) {
    if (p != nullptr) {
        Obhod3(p->Left); // Обход левого поддерева
        std::cout << p->Data << " "; // Обработка узла
        Obhod3(p->Right); // Обход правого поддерева
    }
}

// Вычисление размера дерева (количество узлов)
int treeSize(Vertex *p) {
    if (p == nullptr)
        return 0;
    return 1 + treeSize(p->Left) + treeSize(p->Right);
}

// Вычисление контрольной суммы дерева (сумма всех данных узлов)
int treeChecksum(Vertex *p) {
    if (p == nullptr)
        return 0;
    return p->Data + treeChecksum(p->Left) + treeChecksum(p->Right);
}

// Вычисление высоты дерева (максимальная глубина)
int treeHeight(Vertex *p) {
    if (p == nullptr)
        return 0;
    return 1 + std::max(treeHeight(p->Left), treeHeight(p->Right));
}

// Рекурсивная функция для вычисления суммы глубин всех узлов
void calcAverageHeight(Vertex *p, int level, int &sumDepths, int &countNodes) {
    if (p != nullptr) {
        sumDepths += level; // Добавляем текущий уровень
        countNodes++;       // Увеличиваем счётчик узлов
        calcAverageHeight(p->Left, level + 1, sumDepths, countNodes);
        calcAverageHeight(p->Right, level + 1, sumDepths, countNodes);
    }
}

// Вычисление средней глубины дерева
double averageHeight(Vertex *p) {
    int sumDepths = 0, countNodes = 0;
    calcAverageHeight(p, 1, sumDepths, countNodes); // Начинаем с уровня 1
    return (double)sumDepths / countNodes;
}

// Главная программа
int main() {
    // Создаем дерево, соответствующее варианту №1:
    //   1
    //  / \ 
    // 2   3
    //    /  \
    //   4    5
    //       /
    //      6   

    Vertex *Root = new Vertex(1);
    Root->Left = new Vertex(2);
    Root->Right = new Vertex(3);
    Root->Right->Left = new Vertex(4);
    Root->Right->Right = new Vertex(5);
    Root->Right->Right->Left = new Vertex(6);

    std::cout << "Обход сверху вниз: ";
    Obhod1(Root);
    std::cout << std::endl;

    std::cout << "Обход слева направо: ";
    Obhod3(Root);
    std::cout << std::endl;

    std::cout << "Обход снизу вверх: ";
    Obhod2(Root);
    std::cout << std::endl;


    // Вычисление и вывод размера дерева
    int size = treeSize(Root);
    std::cout << "Размер дерева: " << size << std::endl;

    // Вычисление и вывод контрольной суммы дерева
    int checksum = treeChecksum(Root);
    std::cout << "Контрольная сумма: " << checksum << std::endl;

    // Вычисление и вывод высоты дерева
    int height = treeHeight(Root);
    std::cout << "Высота дерева: " << height << std::endl;

    // Вычисление и вывод средней глубины дерева
    double avgHeight = averageHeight(Root);
    std::cout << std::fixed << std::setprecision(2) << "Средняя высота: " << avgHeight << std::endl;

    return 0;
}
