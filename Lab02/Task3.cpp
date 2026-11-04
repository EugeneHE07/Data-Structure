#include <iostream>
#include <cstdlib>
using namespace std;

typedef int ElemType;
typedef int Status;

const Status OK = 1;
const Status ERROR = 0;

struct LNode {
    ElemType data;
    LNode* next;
};

struct SListInfo {
    LNode* head = nullptr;
    LNode* tail = nullptr;
    int length = 0;
};

/*Status InitList(SListInfo& L) {
    if (L.head != nullptr) {
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

Status AppendElem(SListInfo& L, ElemType e) {
    if (L.head == nullptr) {
        return ERROR;
    }

    LNode* node = (LNode*)malloc(sizeof(LNode));
    if (node == nullptr) {
        return ERROR;
    }

    node->data = e;
    node->next = nullptr;
    L.tail->next = node;
    L.tail = node;
    ++L.length;
    return OK;
}

Status DestroyList(SListInfo& L) {
    if (L.head == nullptr) {
        return ERROR;
    }

    LNode* current = L.head->next;
    for (int count = 0; count < L.length; ++count) {
        LNode* next = current->next;
        free(current);
        current = next;
    }

    free(L.head);
    L.head = nullptr;
    L.tail = nullptr;
    L.length = 0;
    return OK;
}*/

Status Josephus(SListInfo& L, int m) {
    if (L.head == nullptr || L.length == 0 || m <= 0) {
        return ERROR;
    }

    L.tail->next = L.head->next;

    LNode* previous = L.tail;
    LNode* current = L.head->next;

    cout << "出列顺序：";
    while (L.length > 0) {
        for (int count = 1; count < m; ++count) {
            previous = current;
            current = current->next;
        }

        cout << current->data;
        if (L.length > 1) {
            cout << " ";
        }

        previous->next = current->next;
        if (current == L.tail) {
            L.tail = previous;
        }

        LNode* removed = current;
        current = current->next;
        free(removed);
        --L.length;
    }
    cout << endl;

    L.head->next = nullptr;
    L.tail = L.head;
    return OK;
}

/*int main() {
    int n, m;
    cin >> n >> m;

    if (n <= 0 || m <= 0 || m >= n) {
        cerr << "输入错误：n、m 应满足 n > m > 0。" << endl;
        return 1;
    }

    SListInfo people;
    if (InitList(people) != OK) {
        cerr << "链表初始化失败。" << endl;
        return 1;
    }

    for (int i = 1; i <= n; ++i) {
        if (AppendElem(people, i) != OK) {
            cerr << "结点分配失败。" << endl;
            DestroyList(people);
            return 1;
        }
    }

    if (Josephus(people, m) != OK) {
        cerr << "约瑟夫环执行失败。" << endl;
        DestroyList(people);
        return 1;
    }

    DestroyList(people);
    return 0;
}*/
