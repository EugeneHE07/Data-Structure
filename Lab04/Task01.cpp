#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef int Status;
const int OK = 1;
const int ERROR = 0;
const int MAX_SIZE = 20;
const int MAX_TERMS = MAX_SIZE * MAX_SIZE;

struct Triple {
    int row;
    int col;
    int value;
};

struct SqMatrix {
    Triple arr[MAX_TERMS];
    int Rows = 0;
    int Cols = 0;
    int Nums = 0;
};

Status ReadInMatrix (SqMatrix& M) {
    if (!(cin >> M.Rows >> M.Cols)) {
        return ERROR;
    }

    if (M.Rows <= 0 || M.Cols <= 0 || M.Rows > MAX_SIZE || M.Cols > MAX_SIZE) {
        return ERROR;
    }

    M.Nums = 0;
    for (int i = 0; i < M.Rows; i++) {
        for (int j = 0; j < M.Cols; j++) {
            int value;
            cin >> value;
            if ( value != 0) {
                M.arr[M.Nums++] = {i, j, value};
            }
        }
    }
    return OK;
}

Status FastTransposeMatrix(SqMatrix& A,SqMatrix& B) {
    B.Rows = A.Cols;
    B.Cols = A.Rows;
    B.Nums = A.Nums;

    int rowNum[MAX_SIZE] = {};
    int rowStart[MAX_SIZE] = {};


    for (int k = 0; k < A.Cols; k++) {\
        rowStart[k] = 0;
    }
    for (int p = 0; p < A.Nums; p ++) {
        rowNum[A.arr[p].col]++;
    }

    rowStart[0] = 0;
    for (int k = 1; k < A.Cols; k ++) {
        rowStart[k] = rowStart[k -1]+ rowNum[k-1];
    }

    for (int p = 0; p < A.Nums; p ++) {
        int q = rowStart[A.arr[p].col];
        B.arr[q].col = A.arr[p].row;
        B.arr[q].row = A.arr[p].col;
        B.arr[q].value = A.arr[p].value;
        rowStart[A.arr[p].col]++;
    }

    return OK;
}

void BuildRowStart(const SqMatrix& M,int rowStart[]) {
    int rowNums[MAX_SIZE] = {};
    
    for (int p = 0; p < M.Nums; p++) {
        rowNums[M.arr[p].row]++;
    }
    rowStart[0] = 0;
    for (int k = 1; k <= M.Rows; k++) {
        rowStart[k] = rowStart[k - 1] + rowNums[k - 1];
    }
}

Status MultiplyMatrix(const SqMatrix& A, const SqMatrix& B,SqMatrix& C) {
    if(A.Cols != B.Rows) {
        return ERROR;
    } 
    
    C.Rows = A.Rows;
    C.Cols = B.Cols;
    C.Nums = 0;

    int startA[MAX_SIZE + 1] = {};
    int startB[MAX_SIZE + 1] = {};

    BuildRowStart(A, startA);
    BuildRowStart(B, startB);

    for (int i = 0; i < A.Rows; i++) {
        int sum[MAX_SIZE] = {};
        bool hasValue[MAX_SIZE] = {};
        int usedCols[MAX_SIZE] = {};
        int usedCount = 0;

        for (int p = startA[i];p < startA[i+1]; p++) {
            const Triple& a = A.arr[p];
            for (int q = startB[a.col];q < startB[a.col + 1]; q++){
                const Triple& b = B.arr[q];
                if(!hasValue[b.col]) {
                    hasValue[b.col] = true;
                    usedCols[usedCount++] = b.col;
                }                                   
                sum[b.col] += a.value * b.value;
            }
        }

        sort(usedCols, usedCols + usedCount);


        for (int p = 0; p < usedCount; p++) {
            int j = usedCols[p];
            if(sum[j] != 0){
                C.arr[C.Nums++] = {i, j, sum[j]};
            }
        }
    }
    return OK;
}

void PrintTriples(const SqMatrix &M) {
        cout << "Rows=" << M.Rows
         << ", Cols=" << M.Cols
         << ", Nums=" << M.Nums << '\n';

    cout << "(row, col, value):\n";
    for (int p = 0; p < M.Nums; ++p) {
        cout << '(' << M.arr[p].row + 1 << ", "
             << M.arr[p].col + 1 << ", "
             << M.arr[p].value << ")\n";
    }
}

void PrintMatrix(const SqMatrix &M) {
    int data[MAX_SIZE][MAX_SIZE] = {};
    for (int p = 0; p < M.Nums; p++) {
        data[M.arr[p].row][M.arr[p].col] = M.arr[p].value;
    }

    for (int i = 0; i < M.Rows; i++) {
        for (int j = 0; j < M.Cols; j ++) {
            cout << data[i][j] << (j + 1 == M.Cols ? "\n" : " ");
        }
    }
}

/*int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SqMatrix A, B, T, C;

    // 输入A和B
    if (!ReadInMatrix(A) || !ReadInMatrix(B)) {
        cout << "Input error: matrix size must be within 1..20.\n";
        return 0;
    }

    // 快速转置A
    FastTransposeMatrix(A, T);
    cout << "Transpose of A (triples):\n";
    PrintTriples(T);
    cout << "Transpose of A (matrix):\n";
    PrintMatrix(T);

    // 矩阵A乘B
    if (MultiplyMatrix(A, B, C)) {
        cout << "A * B (triples):\n";
        PrintTriples(C);
        cout << "A * B (matrix):\n";
        PrintMatrix(C);
    } else {
        cout << "Multiplication error: A.Cols != B.Rows.\n";
    }

    return 0;
}*/