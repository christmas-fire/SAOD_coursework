#include <iostream>
#include <fstream>
#include <iomanip>  // Для std::setw
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

struct record {
    char name[30];           // Employee full name
    unsigned short int department; // Department number
    char post[22];           // Job title
    char date[10];           // Date of birth in dd-mm-yy format
};

struct list {
    record data;
    list* next;
};

list* loadDatabase(const char* filename);
list* copyList(list* head);
bool parseDay(const char* dateStr, int& day);
bool compareRecords(const record& a, const record& b);
list* merge(list* left, list* right);
list* mergeSort(list* head);
void displayRecordsTable(list* head, int start, int end);
void displayNextPage(list* head, int& currentPage, int& totalPages);
void searchRecordByNumberAndShowPage(list* head, int number);
void freeList(list* head);
list* binarySearchByBirthday(list* head, const char* date);
