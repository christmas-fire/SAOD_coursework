#include "list.hpp"


// Функция переноса данных из списка в вектор
vector<record> linkedListToVector(list* head) {
    vector<record> vec;
    list* current = head;
    while (current != nullptr) {
        vec.push_back(current->data);
        current = current->next;
    }
    return vec;
}

// Функция записи БД в список
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

// Функция копирования списка
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

// Функция конвертации даты (дней) в число
bool parseDay(const char* dateStr, int& day) {
    if (strlen(dateStr) < 2) {
        cerr << "Error: Invalid date format '" << dateStr << "'" << endl;
        return false;
    }

    string dayStr(dateStr, 2);
    try {
        day = stoi(dayStr);
    } catch (exception& e) {
        cerr << "Error: Сonverting day from string: " << e.what() << endl;
        return false;
    }
    return true;
}

// Функия для сравнения полей даты и имени записи
bool compareRecords(const record& a, const record& b) {
    int dayA, dayB;

    if (!parseDay(a.date, dayA)) return false;
    if (!parseDay(b.date, dayB)) return false;

    if (dayA != dayB) {
        return dayA < dayB;
    }

    return strcmp(a.name, b.name) < 0;
}

// Функция слияния для MergeSort()
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

// Функция MergeSort()
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

// Вывод таблицы БД
void displayRecordsTable(list* head, int start, int end) {
    list* current = head;
    int count = 0;

    while (current && count < start) {
        current = current->next;
        ++count;
    }

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

// Вывод записи
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

// Вывод записи по номеру (с ее страницей)
void searchRecordByNumberAndShowPage(list* head, int number) {
    int pageNumber = (number - 1) / 20;
    int start = pageNumber * 20;
    int end = start + 20;

    cout << "Record #" << number << " is on page #" << (pageNumber + 1) << "." << endl;
    displayRecordsTable(head, start, end);
}

// Бинарный поиск по "дням" в дате
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

// Функция удаления списка из памяти
void freeList(list* head) {
    while (head) {
        list* temp = head;
        head = head->next;
        delete temp;
    }
}

// Функция вывода заголовка таблицы
void displayTableHeader() {
    cout << string(90, '-') << endl;
    cout << left << setw(30) << "Name"
         << setw(15) << "Department"
         << setw(25) << "Post"
         << setw(15) << "Date of Birth"
         << endl;
    cout << string(90, '-') << endl;
}