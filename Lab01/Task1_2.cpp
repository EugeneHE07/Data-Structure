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

Status InsertElem(SListInfo& L, int i, ElemType e) {
    if (L.head == nullptr || i < 1 || i > L.length + 1) {
        cout << "Invalid position or uninitialized list." << endl;
        return ERROR;
    }

    LNode* p = L.head;
    
    for (int j = 1; j < i; j++) {
        p = p->next;
    }

    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (!newNode) {
        cout << "Memory allocation failed." << endl;
        return ERROR;
    }
    
    newNode->data = e;
    newNode->next = p->next;
    p->next = newNode;

    if (p == L.tail) {
        L.tail = newNode;
    }

    L.length++;
    return OK;
}

Status DeleteElem(SListInfo& L, int i, ElemType& e) {
    if (L.head == nullptr || i < 1 || i > L.length) {
        cout << "Invalid position or uninitialized list." << endl;
        return ERROR;
    }

    LNode* p = L.head;
    
    for (int j = 1; j < i; j++) {
        p = p->next;
    }

    LNode* q = p->next;
    e = q->data;
    p->next = q->next;

    if (q == L.tail) {
        L.tail = p;
    }

    free(q);
    L.length--;
    return OK;
}

// !以下测试代码部分为了验证上述函数的正确性，部分测试角度为AI生成，以全面测试各功能函数正确性
int main() {
    SListInfo L{};
    ElemType e = 0;
    cout << boolalpha;

    // 1. 初始化和建立测试链表
    if (InitList(L) != OK) return 1;

    cout << "Init: " << (L.head != nullptr)
         << ", Empty: " << ListEmpty(L) << endl;

    for (int i = 1; i <= 4; i++)
        if (InsertElem(L, i, i * 10) != OK) {
            DestroyList(L);
            return 1;
        }

    cout << "Initial: ";
    ListTraverse(L);
    cout << "Length: " << ListLength(L) << endl;

    // 2. 测试访问、查找、前驱和后继
    GetElem(L, 3, e);
    cout << "Get(3): " << e
         << ", Locate(30): " << LocateElem(L, 30) << endl;

    PriorElem(L, 20, e);
    cout << "Prior(20): " << e << endl;
    NextElem(L, 20, e);
    cout << "Next(20): " << e << endl;

    // 3. 测试修改元素并返回旧值
    e = 25;
    SetElem(L, 2, e);
    cout << "Set Old: " << e << endl;
    cout << "After Set: ";
    ListTraverse(L);

    // 4. 测试非法删除，链表和 e 应保持不变
    e = 777;
    bool invalid = (DeleteElem(L, 0, e) == ERROR &&
                    DeleteElem(L, 5, e) == ERROR &&
                    e == 777 && ListLength(L) == 4);
    cout << "Invalid Delete: " << invalid << endl;

    // 5. 依次删除头部、中间、尾部和唯一结点
    DeleteElem(L, 1, e);
    cout << "Delete Head: " << e << endl;

    L.pCurNode = L.head->next->next;
    DeleteElem(L, 2, e);
    cout << "Delete Middle: " << e
         << ", Cur Valid: "
         << (L.pCurNode == L.head->next) << endl;

    DeleteElem(L, 2, e);
    cout << "Delete Tail: " << e
         << ", Tail Valid: "
         << (L.tail == L.head->next) << endl;

    DeleteElem(L, 1, e);
    cout << "Delete Last: " << e
         << ", Empty: " << ListEmpty(L)
         << ", Tail=head: " << (L.tail == L.head)
         << ", Cur=head: " << (L.pCurNode == L.head)
         << endl;

    cout << "Delete Empty: "
         << (DeleteElem(L, 1, e) == ERROR) << endl;

    // 6. 测试清空非空链表、重复清空
    InsertElem(L, 1, 99);
    InsertElem(L, 2, 100);

    cout << "Clear: " << (ClearList(L) == OK)
         << ", Length: " << ListLength(L) << endl;
    cout << "Clear Again: " << (ClearList(L) == OK) << endl;

    // 7. 清空后复用并销毁非空链表
    InsertElem(L, 1, 88);
    cout << "Reuse: ";
    ListTraverse(L);

    cout << "Destroy: " << (DestroyList(L) == OK) << endl;
    cout << "Reset: " << (L.head == nullptr &&
                          L.tail == nullptr &&
                          L.pCurNode == nullptr &&
                          L.length == 0) << endl;

    return 0;
}



