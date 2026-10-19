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

Status PriorElem(const SListInfo& L, ElemType cur_e, ElemType& pre_e) {
    if(L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;
    LNode* pre = L.head;

    while ( p != nullptr) {
        if (p->data == cur_e) {
            if (pre == L.head) {
                cout << "No prior element exists." << endl;
                return ERROR;
            }
            pre_e = pre->data;
            return OK;
        }
        pre = p;
        p = p->next;
    }

    cout << "Element not found." << endl;
    return ERROR;
}

Status NextElem(const SListInfo& L, ElemType cur_e, ElemType& next_e) {
    if(L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;
    LNode* p_next = nullptr;

    while (p != nullptr) {
        if (p->data == cur_e) {
            p_next = p->next;
            if (p_next == nullptr) {
                cout << "No next element exists." << endl;
                return ERROR;
            }
            next_e = p_next->data;
            return OK;
        }
        p = p->next;
    }

    cout << "Element not found." << endl;
    return ERROR;
}

Status ListTraverse(const SListInfo& L) {
    if (L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;

    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }

    cout << endl;
    return OK;
}

Status SetElem(SListInfo& L, int i, ElemType& e) {
    if (L.head == nullptr || i < 1 || i > L.length) {
        cout << "Invalid position or uninitialized list." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;
    
    for (int j = 1; j < i;j++) {
        p = p->next;
    }
    
    ElemType old_e = p->data;
    p->data = e;
    e = old_e;

    return OK;
}

// !以下测试代码部分为了验证上述函数的正确性，部分测试角度为AI生成，以全面测试各功能函数正确性
int main() {
    SListInfo L{};
    ElemType e = 0;
    Status s;
    cout << boolalpha;

    // 1. 初始化、判空和长度
    s = InitList(L);
    cout << "Init: " << (s == OK) << endl;
    if (s != OK) return 1;

    cout << "Empty/Length: " << ListEmpty(L)
         << " / " << ListLength(L) << endl;

    // 2. 创建测试链表 10 -> 20 -> 30
    int values[] = {10, 20, 30};
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

    cout << "Traverse: ";
    ListTraverse(L);
    cout << endl;

    // 3. 测试按位置访问、按值查找、前驱和后继
    GetElem(L, 2, e);
    cout << "Get(2): " << e << endl;
    cout << "Locate(20): " << LocateElem(L, 20) << endl;
    cout << "Locate(99): " << LocateElem(L, 99) << endl;

    PriorElem(L, 20, e);
    cout << "Prior(20): " << e << endl;

    NextElem(L, 20, e);
    cout << "Next(20): " << e << endl;

    cout << "Prior(10) invalid: "
         << (PriorElem(L, 10, e) == ERROR) << endl;
    cout << "Next(30) invalid: "
         << (NextElem(L, 30, e) == ERROR) << endl;

    // 4. 修改中间元素，检查旧值与新值
    e = 25;
    s = SetElem(L, 2, e);
    cout << "Set(2,25): " << (s == OK)
         << ", Old: " << e << endl;

    GetElem(L, 2, e);
    cout << "Get(2) after Set: " << e << endl;

    // 5. 修改首元素和尾元素
    e = 5;
    SetElem(L, 1, e);
    cout << "Set(1,5) Old: " << e << endl;

    e = 35;
    SetElem(L, 3, e);
    cout << "Set(3,35) Old: " << e << endl;

    cout << "After Set: ";
    ListTraverse(L);
    cout << endl;

    // 6. 测试非法位置，e 应保持不变
    e = 99;
    s = SetElem(L, 0, e);
    cout << "Set(0) invalid: "
         << (s == ERROR && e == 99) << endl;

    s = SetElem(L, 4, e);
    cout << "Set(4) invalid: "
         << (s == ERROR && e == 99) << endl;

    // 7. 清空、判空以及空表修改
    cout << "Clear: " << (ClearList(L) == OK) << endl;
    cout << "Empty/Length: " << ListEmpty(L)
         << " / " << ListLength(L) << endl;

    cout << "Set Empty invalid: "
         << (SetElem(L, 1, e) == ERROR) << endl;
    cout << "Clear Again: " << (ClearList(L) == OK) << endl;

    // 8. 清空后复用，并销毁非空链表
    LNode* p = (LNode*)malloc(sizeof(LNode));
    if (!p) {
        DestroyList(L);
        return 1;
    }
    p->data = 50;
    p->next = nullptr;
    L.tail->next = p;
    L.tail = p;
    L.length++;

    cout << "Reuse: ";
    ListTraverse(L);
    cout << endl;

    cout << "Destroy: " << (DestroyList(L) == OK) << endl;
    cout << "Reset: " << (L.head == nullptr &&
                          L.tail == nullptr &&
                          L.pCurNode == nullptr &&
                          L.length == 0) << endl;

    return 0;
}

