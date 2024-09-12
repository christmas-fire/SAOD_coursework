#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct vertex {
    int data;
    vertex *left;
    vertex *right;
};

void obhod(vertex *p) {
    if (p == nullptr) {
        cout << p->data << " ";
        obhod(p->left);
        cout << p->left->data;
        obhod(p->right);
        cout << p->right->data;
    } else {
        cout << "Дерево кончилось" << endl;
    }
}

int tree_size(vertex *p) {
    int n;
    if (p == nullptr) n = 0;
    else n = 1 + tree_size(p->left) + tree_size(p->right);
    return n;
}

int tree_sum(vertex *p) {
    int s;
    if (p == nullptr) s = 0;
    else s = 1 + tree_sum(p->left) + tree_sum(p->right);
    return s;
}

int tree_high(vertex *p) {
    int h;
    if (p == nullptr) h = 0;
    else h = 1 + max(tree_high(p->left), tree_high(p->right));
    return h;
}

int tree_sum_ways(vertex *p, int L) {
    int s;
    if (p == nullptr) s = 0;
    else s = L + tree_sum_ways(p->left, L+1) + tree_sum_ways(p->right, L+1);
    return s;
}

int main() {
    vertex *root;
    root = new vertex;
    root -> data = 0;

    root -> left = new vertex;
    root -> left -> data = 1;

    root -> right = new vertex;
    root -> right -> data = 1;

    cout << "Root data: " << root->data << endl;
    cout << "Left child data: " << root->left->data << endl;
    cout << "Right child data: " << root->right->data << endl;
    
    obhod(root);

}