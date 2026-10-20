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

Status InitList(SListInfo& L) {
    if (L.head != nullptr) {
        cout << "List already initialized." << endl;
        return ERROR;
    }

    L.head = (LNode*)malloc(sizeof(LNode));
    L.head->next = nullptr;
    L.tail = L.head;
    L.length = 0;

    return OK;
}

Status AppendElem(SListInfo& L, ElemType e) {
    if(L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* newNode = (LNode*)malloc(sizeof(LNode));

    if(!newNode) {
        cout << "Memory allocation failed." << endl;
        return ERROR;
    }

    newNode->data = e;
    newNode->next = nullptr;
    L.tail->next = newNode;
    L.tail = newNode;
    L.length ++;
    
    return OK;
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

    return OK
}



int main() {
    SListInfo L{};
    cout << boolalpha;

    if (InitList(L) != OK) return 1;

    // 1. 创建包含24个元素的无序链表
    int values[] = {
        8, 3, 8, 1, 5, 3, 9, 2,
        1, 7, 5, 4, 9, 6, 2, 10,
        4, 7, 6, 8, 11, 10, 12, 11
    };

    for (int x : values) {
        if (InsertElem(L, ListLength(L) + 1, x) != OK) {
            DestroyList(L);
            return 1;
        }
    }

    cout << "Before (" << ListLength(L) << "): ";
    ListTraverse(L);

    // 2. 去重并检查长度
    // 设置当前指针指向最后一个重复结点
    L.pCurNode = L.tail;

    cout << "Remove: "
         << (RemoveDuplicatesUnsorted(L) == OK) << endl;

    cout << "After (" << ListLength(L) << "): ";
    ListTraverse(L);

    // 3. 检查尾指针及当前指针是否有效
    cout << "Tail: " << L.tail->data << endl;
    cout << "Tail/Cur valid: "
         << (L.tail->next == nullptr &&
             L.pCurNode == L.tail) << endl;

    // 4. 再次去重，验证结果不变
    RemoveDuplicatesUnsorted(L);
    cout << "Remove Again Length: "
         << ListLength(L) << endl;

    // 5. 清空并销毁
    cout << "Clear: " << (ClearList(L) == OK) << endl;
    cout << "Empty: " << ListEmpty(L) << endl;
    cout << "Destroy: " << (DestroyList(L) == OK) << endl;

    return 0;
}
