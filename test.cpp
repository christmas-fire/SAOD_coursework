#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

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

struct coding {
  char symbol; // Символ
  unsigned int quantity; // Встречаемость в текте
  float probability; // Вероятность
  unsigned short int lengthCW; // Длина кодового слова
  char * codeword; // Кодовое слово
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

void printTableSymbols(coding *code, int numSymbols) {
  std::cout << "+" << std::string(11, '-') << "+"
            << std::string(18, '-') << "+"
            << std::string(26, '-') << "+"
            << std::string(26, '-') << "+"
            << std::string(32, '-') << "+" << "\n";

  std::cout << "|" << std::setw(11) << "" << "|"
            << std::setw(18) << "" << "|"
            << std::setw(26) << "" << "|"
            << std::setw(26) << "" << "|"
            << std::setw(32) << "" << "|" << "\n";

  std::cout << "|" << "Code symbol" << "|"
            << "  Count in text   " << "|"
            << "   Probability in text    " << "|"
            << "     Length code word     " << "|"
            << "           Code word            " << "|" << "\n";

  std::cout << "|" << std::setw(11) << "" << "|"
            << std::setw(18) << "" << "|"
            << std::setw(26) << "" << "|"
            << std::setw(26) << "" << "|"
            << std::setw(32) << "" << "|" << "\n";

  std::cout << "+" << std::string(11, '-') << "+"
            << std::string(18, '-') << "+"
            << std::string(26, '-') << "+"
            << std::string(26, '-') << "+"
            << std::string(32, '-') << "+" << "\n";

  float entropy = 0;
  float averageLength = 0;

  for (int i = 0; i < numSymbols; i++) {
    entropy += code[i].probability * std::log2(code[i].probability);
    averageLength += (float)code[i].lengthCW * code[i].probability;
    std::cout << "|"
              << std::setw(7) << (int)(unsigned char)code[i].symbol << std::setw(4) << "" << "|"  // ASCII код (int)(unsigned char)
              << std::setw(15) << code[i].quantity << std::setw(3) << "" << "|"
              << std::setw(23) << std::fixed << code[i].probability << std::setw(3) << "" << "|"
              << std::setw(23) << code[i].lengthCW << std::setw(3) << "" << "|"
              << std::setw(29) << code[i].codeword << std::setw(3) << "   |" << "\n";
  }

  std::cout << "+" << std::string(11, '-') << "+"
            << std::string(18, '-') << "+"
            << std::string(26, '-') << "+"
            << std::string(26, '-') << "+"
            << std::string(32, '-') << "+" << "\n";

  std::cout << "Entropy: " << -entropy << "\n";
  std::cout << "Average length code word: " << averageLength << "\n";
}

// Сортировка для кодировки (сортировка по убыванию вероятности)
void quickSortCoding(coding* A, int R, int L) {
    while (L < R) {
    float x = A[L].probability;
    int i = L;
    int j = R;
    while (i <= j) {
      while (A[i].probability > x)
        i++;
      while (A[j].probability < x)
        j--;

      if (i <= j) {
        char tmp_ch;
        tmp_ch = A[i].symbol;
        A[i].symbol = A[j].symbol;
        A[j].symbol = tmp_ch;

        unsigned int tmp_q;
        tmp_q = A[i].quantity;
        A[i].quantity = A[j].quantity;
        A[j].quantity = tmp_q;

        float tmp_prop;
        tmp_prop = A[i].probability;
        A[i].probability = A[j].probability;
        A[j].probability = tmp_prop;
        i++;
        j--;
      }
    }
    if (j - L > R - i) {
      quickSortCoding(A, R, i);
      R = j;
    }
    else {
      quickSortCoding(A, j, L);
      L = i;
    }
  }
}

//Находит медиану части массива P, т.е. такой индекс L <= m <= R, что минимальна величина
int med(coding *code, int borderL, int borderR) {
  float SumL = 0;
  for (int i = borderL; i < borderR; i++)
    SumL = SumL + code[i].probability;

    float SumR = code[borderR].probability;
    int m = borderR;

    while (SumL >= SumR) {
        m = m - 1;
        SumL = SumL - code[m].probability;
        SumR = SumR + code[m].probability;
    }
  return m;
}

void codeFano(coding * code, int borderL, int borderR, int k) {
  //k - длина уже построенной части элементарных кодов
  if (borderL < borderR) {
    k = k + 1;
    int m = med(code, borderL, borderR);
    for (int i = borderL; i <= borderR; i++) {
      if (code[i].codeword != nullptr) {
        char *temp = new char[k + 1];
        for(int j = 0; j < k - 1; j++)
            temp[j] = code[i].codeword[j];
        delete[] code[i].codeword;
        code[i].codeword = temp;
      }
      else
        code[i].codeword = new char[k + 1];

      if (i <= m)
        code[i].codeword[k - 1] = '0';
      else
        code[i].codeword[k - 1] = '1';

      code[i].codeword[k] = '\0';
      code[i].lengthCW = code[i].lengthCW+ 1;
    }
    codeFano(code, borderL, m, k);
    codeFano(code, m + 1, borderR, k);
  }
}

void tableSymbols(coding* &code, int &numsUnique) {
  int windows866[256] = {0};
  int totalNums = 0;
  char ch;

  std::fstream file("testBase2.dat", std::ios::in | std::ios::binary);

  if (!(file.is_open())){
    std::cerr << "Error: file testBase2.dat isn't found.";
    exit(1);
  }

  while (!file.read((char*)&ch, sizeof(ch)).eof()){
        totalNums++;
        if (int(ch) < 0)
            windows866[int(ch) + 256]++;
        else
            windows866[int(ch)]++;
  }
  file.close();

  for (int i = 0; i < 256; i++)
    if (windows866[i] != 0 )
        numsUnique++;

//   code = new coding[numsUnique];
    code = new coding[numsUnique];
    for (int i = 0; i < numsUnique; i++) {
        code[i].codeword = nullptr; // Инициализация
        code[i].lengthCW = 0;       // Инициализация длины кодового слова
    }
    unsigned short int temp = 0;
    for (int i = 0; i < 256; i++) {
        if(windows866[i] != 0) {
        code[temp].symbol = char(i);
        code[temp].quantity = windows866[i];
        code[temp].probability = (float)windows866[i] / (float)totalNums;
        temp++;
        }
    }

    quickSortCoding(code, numsUnique - 1, 0);
    codeFano(code, 0, numsUnique - 1, 0);
}

void freeCoding(coding* code, int numSymbols) {
    if (code != nullptr) {
        for (int i = 0; i < numSymbols; i++) {
            delete[] code[i].codeword;
        }
        delete[] code;
        code = nullptr;
    }
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
        cout << "7. Coding" << endl;
        cout << "8. Exit the program" << endl;
        cout << string(90, '-') << endl;
        cout << "Enter your choice (1-8): ";

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
                int numSymbols = 0;
                coding *codeFano = nullptr;

                freeCoding(codeFano, numSymbols);
                tableSymbols(codeFano, numSymbols);
                printTableSymbols(codeFano, numSymbols);
                freeCoding(codeFano, numSymbols);
                break;
            }
            case 8: {
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
