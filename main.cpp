/*
    B = 2 (файл testBase2.dat);
    C = 2 - по дням(!) pождения и ФИО, К = день pождения;
    S = 3 Метод пpямого слияния
    Файл базы данных загpужается в динамическую память в виде списка,
    сортировка проводится с использованием очередей, затем, для проведения
    быстрого поиска, по отсортированному списку строится индексный массив.
    D = 3 Дерево оптимального поиска (приближеный алгоритм А1)
    E = 3 Код Фано
*/

#include <iostream>
#include <fstream>

using namespace std;

struct record {
    char name[30];
    unsigned short int department;
    char post[22];
    char date[10];
};

int main() {
    system("chcp 866 > nul");

    // Создаём массив для хранения 4000 записей
    record arr[4000];

    // Открываем бинарный файл
    ifstream database("testBase2.dat", ios::binary);

    // Проверяем, открылся ли файл
    if (!database) {
        cerr << "error open database!" << endl;
        return 1;
    }

    // Чтение всех 4000 записей из файла
    database.read(reinterpret_cast<char*>(arr), sizeof(arr));

    database.close();

// Переменные для управления выводом
    int choice = 1;  // Управляет продолжением работы
    int count = 0;   // Счётчик записей
    int totalRecords = 4000;  // Общее количество записей

    while (choice != 0 && count < totalRecords) {
        // Выводим по 20 записей за один раз
        for (int i = 0; i < 20 && count < totalRecords; i++, count++) {
            cout << "Record " << count + 1 << endl;  // Нумерация записей
            cout << (arr[count].name);
            cout << endl;
            cout << (arr[count].department);
            cout << endl;
            cout << (arr[count].post);
            cout << endl;
            cout << (arr[count].date);
            cout << endl << endl;
        }

        // Спрашиваем у пользователя, продолжать или нет
        if (count < totalRecords) {
            cout << "Type '1' to continue, '0' to exit: ";
            cin >> choice;
        } else {
            cout << "Все записи выведены." << endl;
            break;
        }
    }

    return 0;
}
