#pragma once

// Запись БД
struct record {
    char name[30];
    unsigned short int department;
    char post[22];
    char date[10];
};

// Односвязный список
struct list {
    record data;
    list* next;
};

// Узел дерева
struct TreeNode {
    record data;
    TreeNode* left;
    TreeNode* right;
};

// Кодировка
struct coding {
    char symbol; // Символ
    unsigned int quantity; // Встречаемость в текте
    float probability; // Вероятность
    unsigned short int lengthCW; // Длина кодового слова
    char *codeword; // Кодовое слово
};