#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "struct.hpp"
#include "tree.hpp"

using namespace std;

vector<record> linkedListToVector(list* head);
list* loadDatabase(const char* filename);
list* copyList(list* head);
bool parseDay(const char* dateStr, int& day);
bool compareRecords(const record& a, const record& b);
list* merge(list* left, list* right);
list* mergeSort(list* head);
void displayRecordsTable(list* head, int start, int end);
void displayNextPage(list* head, int& currentPage, int& totalPages);
void searchRecordByNumberAndShowPage(list* head, int number);
list* binarySearchByBirthday(list* head, const char* date);
void freeList(list* head);
void displayTableHeader();