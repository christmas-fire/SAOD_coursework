#include "struct.hpp"
#include "list.hpp"
#include "tree.hpp"
#include "coding.hpp"

using namespace std;

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
                sort(vec.begin(), vec.end(), compareByDepartment);
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
                                            displayTreeNode(node);
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
                                freeTree(root);
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
