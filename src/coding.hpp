#pragma once

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

void printTableSymbols(coding *code, int numSymbols);
void quickSortCoding(coding* A, int R, int L);
int med(coding *code, int borderL, int borderR);
void codeFano(coding * code, int borderL, int borderR, int k);
void tableSymbols(coding* &code, int &numsUnique);
void freeCoding(coding* code, int numSymbols);