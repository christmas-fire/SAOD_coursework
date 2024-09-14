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

// Function to load database from file into a linked list
list* loadDatabase(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file '" << filename << "'!" << endl;
        return nullptr;
    }

    list* head = nullptr;
    list* tail = nullptr;

    // Load records from file
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
        cerr << "Error converting day from string: " << e.what() << endl;
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

// Function to merge two sorted lists
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

// Recursive merge sort function
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
    // Calculate the page number (each page contains 20 records)
    int pageNumber = (number - 1) / 20;
    int start = pageNumber * 20;
    int end = start + 20;

    cout << "Record #" << number << " is on page #" << (pageNumber + 1) << "." << endl;
    displayRecordsTable(head, start, end);
}

// Free memory of the list
void freeList(list* head) {
    while (head) {
        list* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    system("chcp 866 > nul");

    // Load database from file
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
        cout << "Menu:" << endl;
        cout << "1. Show next 20 records" << endl;
        cout << "2. Go to page (page number)" << endl;
        cout << "3. Search record by number" << endl;
        cout << "4. Search record by number and show full page" << endl;
        cout << "5. Show original (unsorted) database" << endl;
        cout << "6. Show sorted database" << endl;
        cout << "7. Exit the program" << endl;
        cout << "Enter your choice: ";

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
                cout << "Enter record number to search: ";
                int number;
                cin >> number;
                searchRecordByNumberAndShowPage(currentDatabase, number);
                break;
            }
            case 5: {
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
            case 6: {
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
