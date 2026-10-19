#include <iostream>
#include <cstdlib>
using namespace std;

typedef int ElemType;
typedef int Status;

const int OK = 1;
const int ERROR = 0;

// 单链表结点
struct LNode {
    ElemType data;
    LNode* next;
};

// 单链表管理结构
struct SListInfo {
    LNode* head = nullptr;
    LNode* tail = nullptr;
    LNode* pCurNode = nullptr;
    int length = 0;
};

// !以下功能函数为本人编写，仅测试部分有AI生成，主要用于全面验证正确性。
Status InitList(SListInfo& L) {
    if (L.head != nullptr) {
        cout << "List already initialized." << endl;
        return ERROR;
    }

    L.head = (LNode*)malloc(sizeof(LNode));

    if (L.head == nullptr) {
        cout << "Memory allocation failed." << endl;
        return ERROR;
    }

    L.head->next = nullptr;
    L.tail = L.head;
    L.pCurNode = L.head;
    L.length = 0;

    return OK;
}

Status ClearList(SListInfo& L) {
    if(L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;

    while(p != nullptr) {
        LNode* q = p->next;
        free(p);
        p = q;
    }

    L.head->next = nullptr;
    L.tail = L.head;
    L.pCurNode = L.head;
    L.length = 0;

    return OK;
}

Status DestroyList(SListInfo& L) {
    if(L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    ClearList(L);
    free(L.head);
    L.head = nullptr;
    L.tail = nullptr;
    L.pCurNode = nullptr;
    L.length = 0;

    return OK;
}

bool ListEmpty(const SListInfo& L) {
    return L.length == 0;
}

int ListLength(const SListInfo& L) {
    return L.length;
}

Status GetElem(const SListInfo& L, int i, ElemType& e){
    if (L.head == nullptr || i < 1 || i > L.length) {
        cout << "Invalid position or uninitialized list." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;

    for (int j = 1; j < i; j++)  {
        p = p->next;
    }

    e= p->data;

    return OK;
}

int LocateElem(const SListInfo& L, ElemType e) {
    if (L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return -1;
    }

    LNode* p = L.head->next;
    int pos = 1;

    while (p != nullptr) {
        if(p->data == e) {
            return pos;
        }
        p = p->next;
        pos ++;
    }

    return 0;
}

// !以下测试代码部分为了验证上述函数的正确性，部分测试角度为AI生成，以全面测试各功能函数正确性


int main() {
    SListInfo L{};
    ElemType e;
    cout << boolalpha;

    // 1. 初始化、判空、获取长度
    cout << "Init: " << (InitList(L) == OK) << endl;
    cout << "Empty: " << ListEmpty(L)
         << ", Length: " << ListLength(L) << endl;

    // 2. 手动建立含重复元素的链表
    int values[] = {10, 20, 30, 20};
    for (int v : values) {
        LNode* p = (LNode*)malloc(sizeof(LNode));
        if (!p) {
            DestroyList(L);
            return 1;
        }
        p->data = v;
        p->next = nullptr;
        L.tail->next = p;
        L.tail = p;
        L.length++;
    }

    cout << "After Insert: " << ListEmpty(L)
         << ", Length: " << ListLength(L) << endl;

    // 3. 按位置获取元素
    GetElem(L, 3, e);
    cout << "Get(3): " << e << endl;

    // 4. 查找首位、中间、末位及不存在的元素
    cout << "Locate(10): " << LocateElem(L, 10) << endl;
    cout << "Locate(20): " << LocateElem(L, 20) << endl;
    cout << "Locate(30): " << LocateElem(L, 30) << endl;
    cout << "Locate(99): " << LocateElem(L, 99) << endl;

    // 5. 清空后验证空表查找与重复清空
    cout << "Clear: " << (ClearList(L) == OK) << endl;
    cout << "After Clear: " << ListEmpty(L)
         << ", Length: " << ListLength(L) << endl;
    cout << "Locate Empty: " << LocateElem(L, 20) << endl;
    cout << "Clear Again: " << (ClearList(L) == OK) << endl;

    // 6. 清空后重新使用，测试非空链表销毁
    LNode* p = (LNode*)malloc(sizeof(LNode));
    if (!p) {
        DestroyList(L);
        return 1;
    }
    p->data = 99;
    p->next = nullptr;
    L.tail->next = p;
    L.tail = p;
    L.length++;

    cout << "Reuse Locate(99): " << LocateElem(L, 99) << endl;
    cout << "Destroy: " << (DestroyList(L) == OK) << endl;
    cout << "Reset: " << (L.head == nullptr &&
                          L.tail == nullptr &&
                          L.pCurNode == nullptr &&
                          L.length == 0) << endl;

    return 0;
}
