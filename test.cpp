#include <iostream>
#include <fstream>
#include <iomanip>  // Для std::setw
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

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

struct TreeNode {
    record data;
    TreeNode* left;
    TreeNode* right;
};

// Функция сравнения для сортировки записей по "весу" (здесь - по ФИО)
bool compareByName(const record& a, const record& b) {
    return strncmp(a.name, b.name, 30) < 0;
}

// Функция построения дерева оптимального поиска по алгоритму А1
TreeNode* buildOptimalSearchTree(vector<record>& records, int start, int end) {
    if (start > end) return nullptr;

    // Находим узел с наибольшим "весом" (здесь используем просто середину для приближенной оптимальности)
    int mid = (start + end) / 2;
    
    TreeNode* node = new TreeNode{records[mid], nullptr, nullptr};
    node->left = buildOptimalSearchTree(records, start, mid - 1);
    node->right = buildOptimalSearchTree(records, mid + 1, end);
    
    return node;
}

// // Функция поиска узла по ФИО в дереве
TreeNode* searchTreeByName(TreeNode* root, const char* name) {
    if (!root) {
        cerr << "Error: Root of DOP isn't found" << endl;
        return nullptr;  // Изменил на nullptr для более точного контроля ошибок
    }
    int cmp = strncmp(name, root->data.name, 30);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return searchTreeByName(root->left, name);
    } else {
        return searchTreeByName(root->right, name);
    }
}

// Функция для вывода дерева (симметричный обход)
void printTree(TreeNode* root, int depth = 0) {
    if (!root) return;

    printTree(root->left, depth + 1);
    cout << string(depth * 4, ' ') << root->data.name << endl;
    printTree(root->right, depth + 1);
}

void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Функция для удаления лишних пробелов из строки
void trimSpaces(char* str) {
    if (!str) return;
    // Удаляем начальные пробелы
    while (std::isspace(static_cast<unsigned char>(*str))) {
        ++str;
    }
    // Удаляем конечные пробелы
    char* end = str + std::strlen(str) - 1;
    while (end > str && std::isspace(static_cast<unsigned char>(*end))) {
        --end;
    }
    // Устанавливаем нулевой терминатор после последнего ненулевого символа
    *(end + 1) = '\0';
    // Скопируем результат в оригинальное поле с удалением лишних пробелов
    std::strncpy(str, str, 30); // Копируем до 30 символов
}

// Измененная функция linkedListToVector с удалением пробелов
std::vector<record> linkedListToVector(list* head) {
    std::vector<record> vec;
    list* current = head;
    while (current != nullptr) {
        // Удаляем лишние пробелы из полей name перед добавлением в вектор
        trimSpaces(current->data.name);
        vec.push_back(current->data);
        current = current->next;
    }
    return vec;
}
// Function to load database from file into a linked list
list* loadDatabase(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error: Can't opening file '" << filename << "'!" << endl;
        return nullptr;
    }

    list* head = nullptr;
    list* tail = nullptr;

    record record;
    while (file.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        list* newNode = new list{record, nullptr};
        if (!head) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    file.close();
    return head;
}

// Function to deep copy a list
list* copyList(list* head) {
    if (!head) return nullptr;

    list* newHead = new list{head->data, nullptr};
    list* current = head->next;
    list* newTail = newHead;

    while (current) {
        newTail->next = new list{current->data, nullptr};
        newTail = newTail->next;
        current = current->next;
    }
    return newHead;
}

// Helper function to extract the day from the date string
bool parseDay(const char* dateStr, int& day) {
    if (strlen(dateStr) < 2) {
        cerr << "Error: Invalid date format '" << dateStr << "'" << endl;
        return false;
    }

    std::string dayStr(dateStr, 2);
    try {
        day = std::stoi(dayStr);
    } catch (std::exception& e) {
        cerr << "Error: Сonverting day from string: " << e.what() << endl;
        return false;
    }
    return true;
}

// Function to compare two records by birth day and full name
bool compareRecords(const record& a, const record& b) {
    int dayA, dayB;

    if (!parseDay(a.date, dayA)) return false;
    if (!parseDay(b.date, dayB)) return false;

    if (dayA != dayB) {
        return dayA < dayB;
    }

    return strcmp(a.name, b.name) < 0;
}

list* merge(list* left, list* right) {
    list dummy;
    list* tail = &dummy;

    while (left && right) {
        if (compareRecords(left->data, right->data)) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = left ? left : right;
    return dummy.next;
}

list* mergeSort(list* head) {
    if (!head || !head->next) {
        return head;
    }

    list* slow = head;
    list* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    list* mid = slow->next;
    slow->next = nullptr;

    list* left = mergeSort(head);
    list* right = mergeSort(mid);

    return merge(left, right);
}

// Function to display a range of records in a table format
void displayRecordsTable(list* head, int start, int end) {
    list* current = head;
    int count = 0;

    // Skip records until the start point
    while (current && count < start) {
        current = current->next;
        ++count;
    }

    // Display headers
    cout << string(90, '-') << endl;  // Horizontal separator
    cout << left << setw(5) << "No." 
         << setw(30) << "Name"
         << setw(15) << "Department"
         << setw(25) << "Post"
         << setw(15) << "Date of Birth" 
         << endl;

    cout << string(90, '-') << endl;  // Horizontal separator

    int displayed = 0;
    while (current && displayed < (end - start)) {
        cout << left << setw(5) << (start + displayed + 1) 
             << setw(30) << current->data.name
             << setw(15) << current->data.department
             << setw(25) << current->data.post
             << setw(15) << current->data.date 
             << endl;

        current = current->next;
        ++displayed;
    }
}

void displayRecord(TreeNode* node) {
    if (node) {
        cout << string(90, '-') << endl;
        cout << left << setw(30) << "Name"
             << setw(15) << "Department"
             << setw(25) << "Post"
             << setw(15) << "Date of Birth" 
             << endl;
        cout << string(90, '-') << endl;
        cout << left << setw(30) << node->data.name
             << setw(15) << node->data.department
             << setw(25) << node->data.post
             << setw(15) << node->data.date 
             << endl;
    } else {
        cout << "Record not found." << endl;
    }
}

// Function to display the next page of records in a table format
void displayNextPage(list* head, int& currentPage, int& totalPages) {
    int start = currentPage * 20;
    int end = start + 20;

    displayRecordsTable(head, start, end);

    // Calculate total number of pages
    int count = 0;
    list* temp = head;
    while (temp) {
        ++count;
        temp = temp->next;
    }
    totalPages = (count + 19) / 20;

    if (currentPage >= totalPages) {
        cout << "You are on the last page." << endl;
        currentPage = totalPages - 1;
    }
}

// Function to search for a record by its number and show the full page containing it
void searchRecordByNumberAndShowPage(list* head, int number) {
    int pageNumber = (number - 1) / 20;
    int start = pageNumber * 20;
    int end = start + 20;

    cout << "Record #" << number << " is on page #" << (pageNumber + 1) << "." << endl;
    displayRecordsTable(head, start, end);
}

void freeList(list* head) {
    while (head) {
        list* temp = head;
        head = head->next;
        delete temp;
    }
}

// list* binarySearchByBirthday(list* head, const char* date) {
//     list* current = head;
//     list* resultsHead = nullptr;
//     list* resultsTail = nullptr;

//     while (current) {
//         if (strncmp(current->data.date, date, 2) == 0) {
//             list* newNode = new list{current->data, nullptr};
//             if (!resultsHead) {
//                 resultsHead = newNode;
//             } else {
//                 resultsTail->next = newNode;
//             }
//             resultsTail = newNode;
//         }
//         current = current->next;
//     }
//     return resultsHead;
// }
// Функция для вычисления длины списка
int getListLength(list* head) {
    int length = 0;
    list* current = head;
    while (current) {
        length++;
        current = current->next;
    }
    return length;
}

// Бинарный поиск по дате в связанном списке
list* binarySearchByBirthday(list* head, const char* date) {
    int length = getListLength(head);
    list* resultsHead = nullptr;
    list* resultsTail = nullptr;

    int left = 0;
    int right = length - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // Находим средний индекс
        list* current = head;

        // Итерируем до середины списка
        for (int i = 0; i < mid; ++i) {
            current = current->next;
        }

        // Сравниваем дату в средней позиции со значением date
        if (strncmp(current->data.date, date, 2) == 0) {
            // Если совпадение, добавляем в результаты
            list* newNode = new list{current->data, nullptr};
            if (!resultsHead) {
                resultsHead = newNode;
            } else {
                resultsTail->next = newNode;
            }
            resultsTail = newNode;

            // Теперь ищем в обе стороны, чтобы найти все совпадения
            // Влево
            int tempIndex = mid - 1;
            while (tempIndex >= left) {
                current = head;
                for (int i = 0; i < tempIndex; ++i) {
                    current = current->next;
                }
                if (strncmp(current->data.date, date, 2) == 0) {
                    list* newNode = new list{current->data, nullptr};
                    if (!resultsHead) {
                        resultsHead = newNode;
                    } else {
                        resultsTail->next = newNode;
                    }
                    resultsTail = newNode;
                } else {
                    break; // Выход из цикла, если нет совпадений
                }
                tempIndex--;
            }

            // Вправо
            tempIndex = mid + 1;
            while (tempIndex <= right) {
                current = head;
                for (int i = 0; i < tempIndex; ++i) {
                    current = current->next;
                }
                if (strncmp(current->data.date, date, 2) == 0) {
                    list* newNode = new list{current->data, nullptr};
                    if (!resultsHead) {
                        resultsHead = newNode;
                    } else {
                        resultsTail->next = newNode;
                    }
                    resultsTail = newNode;
                } else {
                    break; // Выход из цикла, если нет совпадений
                }
                tempIndex++;
            }

            return resultsHead; // Возвращаем результат, если нашли совпадение
        } else if (strncmp(current->data.date, date, 2) < 0) {
            left = mid + 1; // Ищем в правой половине
        } else {
            right = mid - 1; // Ищем в левой половине
        }
    }

    return resultsHead; // Если ничего не найдено, вернём пустой список
}

int main() {
    system("chcp 866 > nul");
    list* originalDatabase = loadDatabase("testBase2.dat");
    if (!originalDatabase) return 1;

    // Create a copy of the original database for sorting
    list* copyOfOriginal = copyList(originalDatabase);
    list* sortedDatabase = mergeSort(copyOfOriginal);
    list* currentDatabase = sortedDatabase;

    int currentPage = 0;
    int totalPages = 0;
    bool isSorted = true;

    // Display the first page of the sorted database
    displayNextPage(sortedDatabase, currentPage, totalPages);

    while (true) {
        cout << string(90, '-') << endl;  // Horizontal separator
        cout << "Menu:" << endl;
        cout << "1. Show next 20 records" << endl;
        cout << "2. Go to page (page number)" << endl;
        cout << "3. Search record by number and show full page" << endl;
        cout << "4. Show original (unsorted) database" << endl;
        cout << "5. Show sorted database" << endl;
        cout << "6. Binary search" << endl;
        cout << "7. Exit the program" << endl;
        cout << string(90, '-') << endl;  // Horizontal separator
        cout << "Enter your choice (1-7): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                if (currentPage < totalPages - 1) {
                    ++currentPage;
                    displayNextPage(currentDatabase, currentPage, totalPages);
                } else {
                    cout << "You are already on the last page." << endl;
                }
                break;
            }
            case 2: {
                cout << "Enter page number (1-" << totalPages << "): ";
                int page;
                cin >> page;
                if (page >= 1 && page <= totalPages) {
                    currentPage = page - 1;
                    displayNextPage(currentDatabase, currentPage, totalPages);
                } else {
                    cout << "Invalid page number." << endl;
                }
                break;
            }
            case 3: {
                cout << "Enter record number to search: ";
                int number;
                cin >> number;
                searchRecordByNumberAndShowPage(currentDatabase, number);
                break;
            }
            case 4: {
                if (isSorted) {
                    cout << "Switching to original (unsorted) database." << endl;
                    freeList(currentDatabase); // Free the sorted database
                    currentDatabase = copyList(originalDatabase); // Copy unsorted database
                    currentPage = 0;
                    isSorted = false;
                    displayNextPage(currentDatabase, currentPage, totalPages);
                } else {
                    cout << "You are already viewing the original (unsorted) database." << endl;
                }
                break;
            }
            case 5: {
                if (!isSorted) {
                    cout << "Switching to sorted database." << endl;
                    freeList(currentDatabase); // Free the unsorted database
                    currentDatabase = sortedDatabase;
                    currentPage = 0;
                    isSorted = true;
                    displayNextPage(currentDatabase, currentPage, totalPages);
                } else {
                    cout << "You are already viewing the sorted database." << endl;
                }
                break;
            }
            case 6: {
                char target[2];
                cout << "Enter date (dd): ";
                cin >> target;
                list* foundRecords = binarySearchByBirthday(sortedDatabase, target);
                vector<record> vec = linkedListToVector(foundRecords);
                sort(vec.begin(), vec.end(), compareByName);
                TreeNode* root = buildOptimalSearchTree(vec, 0, vec.size());
                
                if (foundRecords) {
                    int foundCurrentPage = 0;
                    int foundTotalPages = 0;
                    
                    // Отображаем первую страницу найденных записей
                    displayNextPage(foundRecords, foundCurrentPage, foundTotalPages);
                    
                    // Меню для управления найденными записями
                    while (true) {
                        cout << string(90, '-') << endl;
                        cout << "1. Show next 20 records" << endl;
                        cout << "2. Go to page (page number)" << endl;
                        cout << "3. Search name in tree" << endl;
                        cout << "4. Exit found records view" << endl;
                        cout << "Enter your choice: ";
                        
                        int subChoice;
                        cin >> subChoice;
                        
                        switch (subChoice) {
                            case 1: {
                                if (foundCurrentPage < foundTotalPages - 1) {
                                    ++foundCurrentPage;
                                    displayNextPage(foundRecords, foundCurrentPage, foundTotalPages);
                                } else {
                                    cout << "You are already on the last page." << endl;
                                }
                                break;
                            }
                            case 2: {
                                cout << "Enter page number (1-" << foundTotalPages << "): ";
                                int page;
                                cin >> page;
                                if (page >= 1 && page <= foundTotalPages) {
                                    foundCurrentPage = page - 1;
                                    displayNextPage(foundRecords, foundCurrentPage, foundTotalPages);
                                } else {
                                    cout << "Invalid page number." << endl;
                                }
                                break;
                            }
                            case 3: {
                                if (root) {
                                    // printTree(root);

                                    char name[30];
                                    cout << "Enter full name: ";
                                    cin.ignore(); // Clear the buffer
                                    cin.getline(name, sizeof(name)); // Get the full name
                                    
                                    TreeNode* foundNode = searchTreeByName(root, name); // Передаем root как аргумент
                                    displayRecord(foundNode); // Display found node
                                    break;
                                } else {
                                    cerr << "Error: Root of DOP isn't found." << endl;
                                    break;
                                }
                            }
                            case 4: {
                                freeList(foundRecords); // Освобождаем память для найденных записей
                                goto exitFoundRecords;  // Выходим из меню просмотра найденных записей
                            }
                            default: {
                                cout << "Invalid choice. Please try again." << endl;
                                break;
                            }
                        }
                    }
                exitFoundRecords:
                    break;
                } else {
                    cout << "No records found with date of birth: " << target << endl;
                }
                break;
            }
            case 7: {
                cout << "Exiting program." << endl;
                freeList(sortedDatabase);
                freeList(originalDatabase);
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}
