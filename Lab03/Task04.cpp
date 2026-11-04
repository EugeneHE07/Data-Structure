#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Status;

const Status RET_OK = 1;
const Status RET_CONFLICT = 0;
int N;

struct Point {
    int row;
    int col;
};

typedef Point ElemType;

struct SeqStack {
    ElemType* pBase = nullptr;
    ElemType* pTop = nullptr;
    int stacksize = 0;
};

SeqStack StkQueen[3];
int resultCount = 0;

Status InitStack(SeqStack& S) {
    if (S.pBase != nullptr) {
        return RET_CONFLICT;
    }

    S.pBase = (ElemType*)malloc(N * sizeof(ElemType));
    if (S.pBase == nullptr) {
        return RET_CONFLICT;
    }

    S.pTop = S.pBase;
    S.stacksize = N;
    return RET_OK;
}

Status DestroyStack(SeqStack& S) {
    if (S.pBase == nullptr) {
        return RET_CONFLICT;
    }

    free(S.pBase);
    S.pTop = S.pBase = nullptr;
    S.stacksize = 0;

    return RET_OK;
}

Status Push(SeqStack& S, const ElemType& e) {
    if (S.pBase == nullptr || S.pTop - S.pBase >= S.stacksize) {
        return RET_CONFLICT;
    }

    *S.pTop++ = e;
    return RET_OK;
}

Status Pop(SeqStack& S, ElemType& e) {
    if (S.pBase == nullptr || S.pTop == S.pBase) {
        return RET_CONFLICT;
    }

    e = *--S.pTop;
    return RET_OK;
}

Status OutputResult() {
    for (int i = 0; i < 3; ++i) {
        cout << char('A' + i) << ": [";

        for (const ElemType* p = StkQueen[i].pBase;
             p < StkQueen[i].pTop; ++p) {
            if (p != StkQueen[i].pBase) {
                cout << " ";
            }
            cout << p->row;
        }

        cout << "]";
        if (i == 2) cout << '\n';
        else cout << "  ";
    }
    return RET_OK;
}

Status MoveDisk(char from, char to) {
    int a = from - 'A';
    int b = to - 'A';
    ElemType disk;

    if (a < 0 || a >= 3 || b < 0 || b >= 3) {
        return RET_CONFLICT;
    }

    if (Pop(StkQueen[a], disk) != RET_OK) {
        return RET_CONFLICT;
    }

    // 检查是否违反大盘不能放在小盘上的规则
    if (StkQueen[b].pTop != StkQueen[b].pBase &&
        (StkQueen[b].pTop - 1)->row < disk.row) {
        if (Push(StkQueen[a], disk) != RET_OK) {
            return RET_CONFLICT;
        }
        return RET_CONFLICT;
    }

    disk.col = b;

    if (Push(StkQueen[b], disk) != RET_OK) {
        if (Push(StkQueen[a], disk) != RET_OK) {
            return RET_CONFLICT;
        }
        return RET_CONFLICT;
    }

    cout << "Step " << ++resultCount
         << ": Move disk " << disk.row
         << " from " << from << " to " << to << endl;

    OutputResult();
    return RET_OK;
}

// 7. 汉诺塔递归算法
Status Hanoi(int n, char from, char auxiliary, char to) {
    if (n <= 0) {
        return RET_OK;
    }

    if (n == 1) {
        return MoveDisk(from, to);
    }

    if (Hanoi(n - 1, from, to, auxiliary) != RET_OK)
        return RET_CONFLICT;

    if (MoveDisk(from, to) != RET_OK)
        return RET_CONFLICT;

    return Hanoi(n - 1, auxiliary, from, to);
}

int main() {
    cout << "Number of disks (1-10): ";
    if (!(cin >> N) || N < 1 || N > 10) {
        cout << "Invalid disk count." << endl;
        return 1;
    }

    // 初始化三根柱子
    for (int i = 0; i < 3; ++i) {
        if (InitStack(StkQueen[i]) != RET_OK) {
            for (int j = 0; j <= i; ++j) {
                DestroyStack(StkQueen[j]);
            }
            return 1;
        }
    }

    // 将所有盘子从大到小压入A柱
    for (int disk = N; disk >= 1; --disk) {
        if (Push(StkQueen[0], Point{disk, 0}) != RET_OK) {
            for (int i = 0; i < 3; ++i) {
                DestroyStack(StkQueen[i]);
            }
            return 1;
        }
    }

    cout << "Initial state:" << endl;
    OutputResult();

    // 将所有盘子从A移动到C
    if (Hanoi(N, 'A', 'B', 'C') != RET_OK) {
        cout << "Move failed." << endl;
        for (int i = 0; i < 3; ++i)
            DestroyStack(StkQueen[i]);
        return 1;
    }

    cout << "Total moves: " << resultCount << endl;

    for (int i = 0; i < 3; ++i)
        DestroyStack(StkQueen[i]);

    return 0;
}
