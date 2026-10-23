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

/*
Status InitList(SListInfo& L) {
    if(L.head != nullptr) {
        cout << "List already initialized." << endl;
        return ERROR;
    }

    L.head = (LNode*)malloc(sizeof(LNode));
    if(L.head == nullptr) {
        cout << "Memory allocation failed." << endl;
        return ERROR;
    }

    L.head->next = nullptr;
    L.tail = L.head;
    L.length = 0;

    return OK;
}

Status AppendElem(SListInfo& L, ElemType e) {
    if (L.head = nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (!newNode) {
        cout << "Memory allocation failed." << endl;
        return ERROR;
    }

    newNode->data = e;
    newNode->next = nullptr;
    L.tail.next = newNode;
    L.tail = newNode;
    L.length++;

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

    return OK;
}

Status ClearList(SListInfo& L) {
    if (L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;

    while (p != nullptr) {
        LNode* q = p->next;
        free(p);
        p = q;
    }

    L.head->next = nullptr;
    L.tail = L.head;
    L.length = 0;

    return OK;
}

Status DestroyList(SListInfo& L) {
    if (L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    ClearList(L);
    free(L.head);
    L.head = nullptr;
    L.tail = nullptr;
    L.length = 0;

    return OK;
}
*/

Status ReverseList(SListInfo& L) {
    if (L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* prev = nullptr;
    LNode* current = L.head->next;

    L.tail = (current == nullptr) ? L.head : current;

    while (current != nullptr) {
        LNode* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    L.head->next = prev;

    return OK;
}

/*
int main() {
    SListInfo A{}, L{};
    cout << boolalpha;

    if (InitList(A) != OK) return 1;
    if (InitList(L) != OK) {
        free(A.head);
        return 1;
    }
    cout << "Init: true" << endl;

    // 1. 验证空链表和单结点链表
    cout << "Reverse Empty: "
         << (ReverseList(A) == OK &&
             A.head->next == nullptr && A.tail == A.head) << endl;

    AppendElem(A, 10);
    cout << "Reverse Single: "
         << (ReverseList(A) == OK &&
             A.head->next == A.tail &&
             A.tail->next == nullptr) << endl;

    // 2. 用固定数据检查逆置顺序
    for (int x : {20, 30, 40})
        AppendElem(A, x);

    cout << "Before: ";
    ListTraverse(A);
    cout << endl;

    bool smallOK = ReverseList(A) == OK;
    cout << "Reverse Small: " << smallOK << endl;

    cout << "After: ";
    ListTraverse(A);
    cout << endl;

    ReverseList(A);
    cout << "Reverse Twice: ";
    ListTraverse(A);
    cout << endl;

    // 3. 生成100个随机数，记录原始数据与结点地址
    mt19937 rng(2026);
    uniform_int_distribution<int> dist(0, 999);

    int values[100];
    LNode* nodes[100];
    bool appendOK = true;

    for (int i = 0; i < 100; i++) {
        values[i] = dist(rng);

        if (AppendElem(L, values[i]) != OK) {
            appendOK = false;
            break;
        }
        nodes[i] = L.tail;
    }

    cout << "Append 100: " << appendOK << endl;
    cout << "Length: " << L.length << endl;

    // 4. 逆置100个结点，核对地址和数据
    bool reverseOK = appendOK && ReverseList(L) == OK;
    bool orderOK = reverseOK;
    LNode* p = L.head->next;

    if (reverseOK) {
        for (int i = 99; i >= 0; i--) {
            if (p == nullptr ||
                p != nodes[i] ||
                p->data != values[i]) {
                orderOK = false;
                break;
            }
            p = p->next;
        }
        orderOK = orderOK && p == nullptr;
    }

    cout << "Reverse 100: " << reverseOK << endl;
    cout << "Order and Nodes: " << orderOK << endl;
    cout << "Tail Valid: "
         << (appendOK && L.tail == nodes[0] &&
             L.tail->next == nullptr && L.length == 100)
         << endl;

    // 5. 再次逆置，验证恢复原顺序
    bool restored = reverseOK && ReverseList(L) == OK;
    p = L.head->next;

    if (restored) {
        for (int i = 0; i < 100; i++) {
            if (p == nullptr || p != nodes[i]) {
                restored = false;
                break;
            }
            p = p->next;
        }
        restored = restored && p == nullptr;
    }

    cout << "Restore Original: " << restored << endl;

    // 6. 临时释放两条测试链表
    SListInfo* lists[] = {&A, &L};
    for (SListInfo* list : lists) {
        LNode* q = list->head;
        while (q != nullptr) {
            LNode* next = q->next;
            free(q);
            q = next;
        }
    }

    return 0;
}
*/



