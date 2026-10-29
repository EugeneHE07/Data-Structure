#include <iostream>
#include <cstdlib>
using namespace std;

typedef int ElemType;
typedef int Status;

const int OK = 1;
const int ERROR = 0;

struct LNode {
    ElemType data;
    LNode* next;
};

struct SListInfo {
    LNode* head = nullptr;
    LNode* tail = nullptr;
    int length = 0;
};

Status InitList(SListInfo& L) {
    if(L.head != nullptr) {
        cout << "List is already initialized." << endl;
        return ERROR;
    }

    L.head = (LNode*)malloc(sizeof(LNode));

    if (L.head == nullptr) {
        cout << "Failed to initialize list." << endl;
        return ERROR;
    }

    L.head->next = nullptr;
    L.tail = L.head;
    L.length = 0;

    return OK;
}




