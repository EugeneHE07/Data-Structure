#include <iostream>
#include <cstdlib>
#include <random>
using namespace std;

typedef int ElemType;
typedef int Status;

const int OK = 1;
const int ERROR = 0;
const int STACK_INIT_SIZE = 100;

struct SqStack {
    ElemType* base = nullptr;
    ElemType* top = nullptr;
    int stacksize = 0;
};

Status InitStack(SqStack& S) {
    if(S.base != nullptr) {
        return ERROR;
    }

    S.base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(int));

    if(!S.base) {
        return ERROR;
    }

    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;

    return OK;
}

Status DestroyStack(SqStack& S) {
    if(S.base == nullptr) {
        return ERROR;
    }

    free(S.base);

    S.base = nullptr;
    S.top = nullptr;
    S.stacksize = 0;

    return OK;
}

Status ClearStack(SqStack& S) {
    if(S.base == nullptr) {
        return ERROR;
    }

    S.top = S.base;

    return OK;
}

bool StackEmpty(SqStack& S) {
    if(S.base == nullptr) {
        return ERROR;
    }

    return S.top == S.base;
}

int StackLength(SqStack& S) {
    if(S.base == nullptr) {
        return -1;
    }

    return S.top - S.base;
}

Status GetTop(SqStack& S, ElemType& e) {
    if(S.base == nullptr || S.top == S.base) {
        return ERROR;
    }

    e = *(S.top - 1);

    return OK;
}

Status StackTraverse(SqStack& S) {
    if(S.base == nullptr) {
        return ERROR;
    }

    for (auto p = S.base; p < S.top; p++) {
        cout << *p << " ";
    }

    cout << endl;
    return OK;
}

Status Push(SqStack& S, ElemType e) {
    if (S.base == nullptr) {
        return ERROR;
    }

    if(S.top - S.base >= S.stacksize) {
        int length = S.top - S.base;

        ElemType* newBase = (ElemType*)realloc(S.base,(S.stacksize + STACK_INIT_SIZE) * sizeof(int));

        if(newBase == nullptr){
            return ERROR;
        }

        S.base = newBase;
        S.top = S.base + length;
        S.stacksize += STACK_INIT_SIZE;
    }

    *S.top ++= e;

    return OK;
}

Status Pop(SqStack& S,ElemType& e) {
    if(S.base == nullptr || S.top == S.base) {
        return ERROR;
    }

    e = *--S.top;

    return OK;
}

/*int main() {
    SqStack S;
    ElemType e = -1;

    // 测试1：初始化、重复初始化及空栈操作
    cout << "InitStack: " << InitStack(S) << endl;
    cout << "Init again: " << InitStack(S) << endl;
    cout << "Empty initially: " << StackEmpty(S) << endl;
    cout << "Length initially: " << StackLength(S) << endl;
    cout << "GetTop(empty): " << GetTop(S, e) << endl;
    cout << "Pop(empty): " << Pop(S, e) << endl;
    cout << "Traverse empty: ";
    StackTraverse(S);

    // 测试2：入栈、遍历、取栈顶及正常出栈
    cout << "Push 10: " << Push(S, 10) << endl;
    cout << "Push 20: " << Push(S, 20) << endl;
    cout << "Push 30: " << Push(S, 30) << endl;
    cout << "Traverse: ";
    StackTraverse(S);
    cout << "GetTop: " << GetTop(S, e)
         << ", value: " << e << endl;
    cout << "Pop: " << Pop(S, e)
         << ", value: " << e << endl;
    cout << "After pop: ";
    StackTraverse(S);
    cout << "Length after pop: " << StackLength(S) << endl;

    // 测试3：清空后长度、容量、判空及重复清空
    ElemType* oldBase = S.base;
    cout << "ClearStack: " << ClearStack(S) << endl;
    cout << "Empty after clear: " << StackEmpty(S) << endl;
    cout << "Length after clear: " << StackLength(S) << endl;
    cout << "Capacity after clear: " << S.stacksize << endl;
    cout << "Storage preserved: "
         << (S.base == oldBase) << endl;
    cout << "Pop after clear: " << Pop(S, e) << endl;
    cout << "Clear again: " << ClearStack(S) << endl;

    // 测试4：50个随机整数入栈，触发多次扩容
    mt19937 rng(2026);
    ElemType values[50];
    bool pushed = true;

    for (int i = 0; i < 50; i++) {
        values[i] = static_cast<ElemType>(rng() % 1000);

        if (Push(S, values[i]) != OK) {
            pushed = false;
            break;
        }
    }

    cout << "50 pushes succeeded: " << pushed << endl;
    cout << "Random stack: ";
    StackTraverse(S);
    cout << "Length after random pushes: "
         << StackLength(S) << endl;
    cout << "Capacity after growth: " << S.stacksize << endl;
    cout << "GetTop after growth: " << GetTop(S, e)
         << ", value matches: " << (e == values[49]) << endl;

    // 测试5：逆序出栈，验证后进先出规则
    bool lifo = true;

    for (int i = 49; i >= 0; i--) {
        if (Pop(S, e) != OK || e != values[i])
            lifo = false;
    }

    cout << "LIFO check: " << lifo << endl;
    cout << "Length after 50 pops: "
         << StackLength(S) << endl;
    cout << "Empty after 50 pops: " << StackEmpty(S) << endl;
    cout << "Pop again: " << Pop(S, e) << endl;

    // 测试6：销毁及销毁后的非法操作
    cout << "DestroyStack: " << DestroyStack(S) << endl;
    cout << "Pointers null: "
         << (S.base == nullptr && S.top == nullptr) << endl;
    cout << "Capacity after destroy: " << S.stacksize << endl;
    cout << "Destroy again: " << DestroyStack(S) << endl;
    cout << "Clear after destroy: " << ClearStack(S) << endl;
    cout << "GetTop after destroy: " << GetTop(S, e) << endl;
    cout << "Pop after destroy: " << Pop(S, e) << endl;
    cout << "Push after destroy: " << Push(S, 99) << endl;
    cout << "Traverse after destroy: "
         << StackTraverse(S) << endl;

    // 测试7：销毁后重新初始化并最终释放
    cout << "Reinit: " << InitStack(S) << endl;
    cout << "Empty after reinit: " << StackEmpty(S) << endl;
    cout << "Length after reinit: " << StackLength(S) << endl;
    cout << "Final destroy: " << DestroyStack(S) << endl;

    return 0;
}*/