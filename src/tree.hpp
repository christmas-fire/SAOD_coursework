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

using namespace std;

TreeNode* buildOptimalSearchTree(vector<record>& records, int start, int end);
TreeNode* searchTreeByDepartment(TreeNode* root, unsigned short int dep);
void findAllRecordsByDepartment(TreeNode* root, unsigned short int dep, vector<TreeNode*>& results);
void displayTreeNode(TreeNode* node);
void printTreeWithTable(TreeNode* root);
void freeTree(TreeNode* root);
bool compareByDepartment(const record& a, const record& b); 