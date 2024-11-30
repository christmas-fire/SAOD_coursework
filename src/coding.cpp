#include "coding.hpp"

void printTableSymbols(coding *code, int numSymbols) {
    // Вывод заголовка таблицы
    cout << "+" << string(11, '-') << "+"
         << string(18, '-') << "+"
         << string(26, '-') << "+"
         << string(26, '-') << "+"
         << string(32, '-') << "+" << "\n";

    cout << "|" << setw(11) << "" << "|"
         << setw(18) << "" << "|"
         << setw(26) << "" << "|"
         << setw(26) << "" << "|"
         << setw(32) << "" << "|" << "\n";

    cout << "|" << "Code symbol" << "|"
         << "  Count in text   " << "|"
         << "   Probability in text    " << "|"
         << "     Length code word     " << "|"
         << "           Code word            " << "|" << "\n";

    cout << "|" << setw(11) << "" << "|"
         << setw(18) << "" << "|"
         << setw(26) << "" << "|"
         << setw(26) << "" << "|"
         << setw(32) << "" << "|" << "\n";

    cout << "+" << string(11, '-') << "+"
         << string(18, '-') << "+"
         << string(26, '-') << "+"
         << string(26, '-') << "+"
         << string(32, '-') << "+" << "\n";

    float entropy = 0;
    float averageLength = 0;
    int totalSymbols = 0; // Новая переменная для подсчёта общего количества символов

    // Вывод данных о символах
    for (int i = 0; i < numSymbols; i++) {
        entropy += code[i].probability * log2(code[i].probability);
        averageLength += (float)code[i].lengthCW * code[i].probability;
        totalSymbols += code[i].quantity; // Суммируем количество символов

        cout << "|"
             << setw(7) << code[i].symbol << setw(4) << "" << "|"  // ASCII код (int)(unsigned char)
             << setw(15) << code[i].quantity << setw(3) << "|"
             << setw(23) << fixed << code[i].probability << setw(3) << "|"
             << setw(23) << code[i].lengthCW << setw(3) << "|"
             << setw(29) << code[i].codeword << setw(3) << "   |" << "\n";
    }

    cout << "+" << string(11, '-') << "+"
         << string(18, '-') << "+"
         << string(26, '-') << "+"
         << string(26, '-') << "+"
         << string(32, '-') << "+" << "\n";

    // Вывод результатов
    cout << "Entropy: " << -entropy << "\n";
    cout << "Average length code word: " << averageLength << "\n";
    cout << "Total number of symbols in database: " << numSymbols << "\n";
}

// Сортировка для кодировки (сортировка по убыванию вероятности)
void quickSortCoding(coding* A, int R, int L) {
    while (L < R) {
    float x = A[L].probability;
    int i = L;
    int j = R;
    while (i <= j) {
        while (A[i].probability > x) {
            i++;
        }
        while (A[j].probability < x) {
            j--;
        }
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
        else {
            code[i].codeword = new char[k + 1];
        }
        if (i <= m) {
            code[i].codeword[k - 1] = '0';
        }
        else {
            code[i].codeword[k - 1] = '1';
        }
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

    fstream file("testBase2.dat", ios::in | ios::binary);

    if (!(file.is_open())){
        cerr << "Error: file testBase2.dat isn't found.";
        exit(1);
    }

    while (!file.read((char*)&ch, sizeof(ch)).eof()){
        totalNums++;
        if (int(ch) < 0) {
            windows866[int(ch) + 256]++;
        }
        else {
            windows866[int(ch)]++;
        }
    }
    file.close();

    for (int i = 0; i < 256; i++) {
        if (windows866[i] != 0 ) {
            numsUnique++;
        }
    }

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