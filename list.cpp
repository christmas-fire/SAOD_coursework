#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int value;
    Node* next;
};

int main() {

    Node *first = new Node;
    first->next = nullptr;
    first->value = 3;

    Node *second = new Node;
    second->next = nullptr;
    second->value = 1;

    Node *third = new Node;
    third->next = nullptr;
    third->value = 5;

    first->next = second;
    second->next = third;

    cout << first->value;
    return 0;
}