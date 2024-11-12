#include <iostream>
#include <fstream>
#include <iomanip>
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

// Функция сравнения для сортировки записей
bool compareByDepartment(const record& a, const record& b) {
    return a.department < b.department; // Сравнение по department
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

TreeNode* searchTreeByDepartment(TreeNode* root, unsigned short int dep) {
    if (root == nullptr) {
        return nullptr;
    }
    
    if (root->data.department > dep) {
        return searchTreeByDepartment(root->left, dep);
    } else if (root->data.department < dep) {
        return searchTreeByDepartment(root->right, dep);
    } else {
        return root;
    }
}

void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

std::vector<record> linkedListToVector(list* head) {
    std::vector<record> vec;
    list* current = head;
    while (current != nullptr) {
        vec.push_back(current->data);
        current = current->next;
    }
    return vec;
}

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

void displayRecordsTable(list* head, int start, int end) {
    list* current = head;
    int count = 0;

    while (current && count < start) {
        current = current->next;
        ++count;
    }

    // Display headers
    cout << string(90, '-') << endl;
    cout << left << setw(5) << "No." 
         << setw(30) << "Name"
         << setw(15) << "Department"
         << setw(25) << "Post"
         << setw(15) << "Date of Birth" 
         << endl;

    cout << string(90, '-') << endl;

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
        cout << left << setw(30) << node->data.name
             << setw(15) << node->data.department
             << setw(25) << node->data.post
             << setw(15) << node->data.date 
             << endl;
    } else {
        cout << "Record not found." << endl;
    }
}

void findAllRecordsByDepartment(TreeNode* root, unsigned short int dep, vector<TreeNode*>& results) {
    if (root == nullptr) {
        return;
    }

    if (root->data.department == dep) {
        results.push_back(root);
    }

    findAllRecordsByDepartment(root->left, dep, results);
    findAllRecordsByDepartment(root->right, dep, results);
}

void displayNextPage(list* head, int& currentPage, int& totalPages) {
    int start = currentPage * 20;
    int end = start + 20;

    displayRecordsTable(head, start, end);

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

list* binarySearchByBirthday(list* head, const char* date) {
    list* current = head;
    list* resultsHead = nullptr;
    list* resultsTail = nullptr;

    while (current) {
        if (strncmp(current->data.date, date, 2) == 0) {
            list* newNode = new list{current->data, nullptr};
            if (!resultsHead) {
                resultsHead = newNode;
            } else {
                resultsTail->next = newNode;
            }
            resultsTail = newNode;
        }
        current = current->next;
    }
    return resultsHead;
}

int getListLength(list* head) {
    int length = 0;
    list* current = head;
    while (current) {
        length++;
        current = current->next;
    }
    return length;
}

void displayTreeNode(const TreeNode* node) {
    if (node) {
        cout << left << setw(30) << node->data.name
             << setw(15) << node->data.department
             << setw(25) << node->data.post
             << setw(15) << node->data.date
             << endl;
    }
}

void displayTableHeader() {
    cout << string(90, '-') << endl;
    cout << left << setw(30) << "Name"
         << setw(15) << "Department"
         << setw(25) << "Post"
         << setw(15) << "Date of Birth"
         << endl;
    cout << string(90, '-') << endl;
}

void printTreeWithTable(TreeNode* root) {
    if (!root) return;

    printTreeWithTable(root->left);
    displayTreeNode(root);
    printTreeWithTable(root->right);
}

int main() {
    system("chcp 866 > nul");
    list* originalDatabase = loadDatabase("testBase2.dat");
    if (!originalDatabase) return 1;

    list* copyOfOriginal = copyList(originalDatabase);
    list* sortedDatabase = mergeSort(copyOfOriginal);
    list* currentDatabase = sortedDatabase;

    int currentPage = 0;
    int totalPages = 0;
    bool isSorted = true;

    displayNextPage(sortedDatabase, currentPage, totalPages);

    while (true) {
        cout << string(90, '-') << endl;
        cout << "Menu:" << endl;
        cout << "1. Show next 20 records" << endl;
        cout << "2. Go to page (page number)" << endl;
        cout << "3. Search record by number and show full page" << endl;
        cout << "4. Show original (unsorted) database" << endl;
        cout << "5. Show sorted database" << endl;
        cout << "6. Binary search" << endl;
        cout << "7. Exit the program" << endl;
        cout << string(90, '-') << endl;
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
                    freeList(currentDatabase);
                    currentDatabase = copyList(originalDatabase);
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
                    freeList(currentDatabase);
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
                std::sort(vec.begin(), vec.end(), compareByDepartment);
                TreeNode* root = buildOptimalSearchTree(vec, 0, vec.size() - 1);
                
                if (foundRecords) {
                    int foundCurrentPage = 0;
                    int foundTotalPages = 0;
                    
                    displayNextPage(foundRecords, foundCurrentPage, foundTotalPages);
                    
                    while (true) {
                        cout << string(90, '-') << endl;
                        cout << "1. Show next 20 records" << endl;
                        cout << "2. Go to page (page number)" << endl;
                        cout << "3. Search department in tree" << endl;
                        cout << "4. Output tree" << endl;
                        cout << "5. Exit found records view" << endl;
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
                                    unsigned short int dep;

                                    cout << "Enter department: ";
                                    cin.ignore();
                                    cin >> dep;
                                    
                                    TreeNode* foundNode = searchTreeByDepartment(root, dep);
                                    vector<TreeNode*> results;
                                    findAllRecordsByDepartment(root, dep, results);

                                    if (!results.empty()) {
                                        displayTableHeader();
                                        for (TreeNode* node : results) {
                                            displayRecord(node);
                                        }
                                    } else {
                                        cout << "No records found for department " << dep << "." << endl;
                                    }
                                    break;
                                } else {
                                    cerr << "Error: Root of DOP isn't found." << endl;
                                    break;
                                }


                            }
                            case 4: {
                                if (root) {
                                    cout << "Displaying tree in table format:" << endl;
                                    displayTableHeader();
                                    printTreeWithTable(root);
                                } else {
                                    cout << "Tree is empty." << endl;
                                }
                                break;
                            }
                            case 5: {
                                freeList(foundRecords);
                                goto exitFoundRecords;
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
