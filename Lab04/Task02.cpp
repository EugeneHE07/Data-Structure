
#include <iostream>
#include <climits>
using namespace std;

typedef int Status;
const int OK = 1;
const int ERROR = 0;
const int MAX_SIZE = 20;

struct Matrix {
    int Rows = 0;
    int Cols = 0;
    int rowMin[MAX_SIZE];
    int colMax[MAX_SIZE];
};

// 输入矩阵，同时统计行最小值和列最大值
Status ReadInMatrix(Matrix& M) {
    if (!(cin >> M.Rows >> M.Cols))
        return ERROR;

    if (M.Rows <= 0 || M.Rows > MAX_SIZE ||
        M.Cols <= 0 || M.Cols > MAX_SIZE)
        return ERROR;

    for (int i = 0; i < M.Rows; i++)
        M.rowMin[i] = INT_MAX;

    for (int j = 0; j < M.Cols; j++)
        M.colMax[j] = INT_MIN;

    for (int i = 0; i < M.Rows; i++) {
        for (int j = 0; j < M.Cols; j++) {
            int x;
            if (!(cin >> x)) return ERROR;

            if (x < M.rowMin[i])
                M.rowMin[i] = x;

            if (x > M.colMax[j])
                M.colMax[j] = x;
        }
    }
    return OK;
}

// 求所有马鞍点
Status FindSaddlePoints(const Matrix& M) {
    int P = INT_MIN;
    int Q = INT_MAX;

    for (int i = 0; i < M.Rows; i++) {
        if (M.rowMin[i] > P)
            P = M.rowMin[i];
    }

    for (int j = 0; j < M.Cols; j++) {
        if (M.colMax[j] < Q)
            Q = M.colMax[j];
    }

    if (P != Q) {
        cout << "No saddle point.\n";
        return ERROR;
    }

    // 收集所有满足条件的列
    int cols[MAX_SIZE];
    int count = 0;

    for (int j = 0; j < M.Cols; j++) {
        if (M.colMax[j] == Q)
            cols[count++] = j;
    }

    // 符合条件的行和列交叉形成所有马鞍点
    for (int i = 0; i < M.Rows; i++) {
        if (M.rowMin[i] == P) {
            for (int k = 0; k < count; k++) {
                cout << "(" << i + 1 << ", "
                     << cols[k] + 1 << ", "
                     << P << ")\n";
            }
        }
    }

    return OK;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Matrix M;

    if (!ReadInMatrix(M)) {
        cout << "Input error.\n";
        return 0;
    }

    cout << "Saddle points (row, col, value):\n";
    FindSaddlePoints(M);

    return 0;
}
