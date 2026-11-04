#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Status;

const int RET_OK = 1;
const int RET_CONFLICT = 0;
const int N = 8;

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

SeqStack StkQueen;
int resultCount = 0;

Status InitStack(SeqStack& S) {
    if (S.pBase != nullptr) {
        return RET_CONFLICT;
    }

    S.pBase = (ElemType*)malloc(N * sizeof(ElemType));
    if (!S.pBase) {
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
    S.pBase = nullptr;
    S.pTop = nullptr;
    S.stacksize = 0;
    return RET_OK;
}

Status Push(SeqStack& S, ElemType& e) {
    if (S.pBase == nullptr || S.pTop- S.pBase >= S.stacksize) {
        return RET_CONFLICT;
    }

    *S.pTop ++= e;
    return RET_OK;
}

Status Pop(SeqStack& S, ElemType& e) {
    if(S.pBase == nullptr || S.pTop == S.pBase) {
        return RET_CONFLICT;
    }

    e = *--S.pTop;
    return RET_OK;
}

Status JudgeQueenConfliction(const Point& newQueen,const SeqStack& S) {
    for (const ElemType* p = S.pBase;p < S.pTop;p++) {
        if(newQueen.row == p->row || newQueen.col == p->col || abs(newQueen.row - p->row) == abs(newQueen.col - p->col)) {
            return RET_CONFLICT;
        }
    }
    return RET_OK;
}

Status OutputResult(const SeqStack& S) {
    cout << "Solution" << ++resultCount << ": " << endl;

    for (const ElemType* p = S.pBase; p < S.pTop; p++) {
        cout << p->col +1 << (p+1 == S.pTop ? "\n": " ");
    }

    return RET_OK;
}

Status PlaceQueen(int row) {
    for (int col = 0; col < N; col ++) {
        Point curQueen = {row, col};
        if (JudgeQueenConfliction(curQueen,StkQueen) == RET_CONFLICT){
            continue;
        }
        Push(StkQueen, curQueen);

        if (row == N - 1) {
            OutputResult(StkQueen);
        } else {
            PlaceQueen(row + 1);
        }

        ElemType removedQueen;
        Pop(StkQueen, removedQueen);
    }

    return RET_OK;
}

int main() {
    if( InitStack(StkQueen) != RET_OK) {
        return 1;
    }

    if(PlaceQueen(0) != RET_OK) {
        DestroyStack(StkQueen);
        return 1;
    }

    cout << "Total solutions: " << resultCount << endl;
    DestroyStack(StkQueen);

    return 0;
}