#include "tree.hpp"

// Функция построения ДОП по алгоритму А1
TreeNode* buildOptimalSearchTree(vector<record>& records, int start, int end) {
    if (start > end) return nullptr;

    // Находим узел с наибольшим "весом" (здесь используем просто середину для приближенной оптимальности)
    int mid = (start + end) / 2;
    
    TreeNode* node = new TreeNode{records[mid], nullptr, nullptr};
    node->left = buildOptimalSearchTree(records, start, mid - 1);
    node->right = buildOptimalSearchTree(records, mid + 1, end);
    
    return node;
}

// Функция построения дерева с найденными записями
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

// Записываем дерево с найденными записями в вектор
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

// Вывод информации о записи
void displayTreeNode(TreeNode* node) {
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

// Вывод содержимого дерева
void printTreeWithTable(TreeNode* root) {
    if (!root) return;
    printTreeWithTable(root->left);
    displayTreeNode(root);
    printTreeWithTable(root->right);
}

// Удаление дерева из памяти
void freeTree(TreeNode* root) {
    if (!root) {
        return;     
    }
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Функция сравнения для сортировки записей
bool compareByDepartment(const record& a, const record& b) {
    return a.department < b.department;
}
