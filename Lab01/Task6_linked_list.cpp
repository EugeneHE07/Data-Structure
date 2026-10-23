
#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Status;
const int OK = 1;
const int ERROR = 0;

struct LNode {
    int data;
    LNode* next;
};

struct SListInfo {
    LNode* head = nullptr;
    int length = 0;
};

/*
Status InitList(SListInfo& L) {
    L.head = (LNode*)malloc(sizeof(LNode));
    if (L.head == nullptr)
        return ERROR;

    L.head->next = nullptr;
    L.length = 0;
    return OK;
}

Status CreateList(SListInfo& L, int n) {
    if (L.head == nullptr)
        return ERROR;

    LNode* tail = L.head;

    for (int i = 1; i <= n; i++) {
        LNode* p = (LNode*)malloc(sizeof(LNode));
        if (p == nullptr)
            return ERROR;

        p->data = i;
        p->next = nullptr;

        tail->next = p;
        tail = p;
        L.length++;
    }

    return OK;
}
*/

Status MoveStudent(SListInfo& L, int p, int q) {
    if (L.head == nullptr)
        return ERROR;

    LNode* prev = L.head;
    int pos = 0;

    while (prev->next != nullptr &&
           prev->next->data != p) {
        prev = prev->next;
        pos++;
    }

    if (prev->next == nullptr)
        return ERROR;

    LNode* target = prev->next;
    prev->next = target->next;

    int newPos = pos + q;

    LNode* insertPrev = L.head;

    for (int i = 0; i < newPos; i++) {
        insertPrev = insertPrev->next;
    }

    target->next = insertPrev->next;
    insertPrev->next = target;

    return OK;
}

/*void ListTraverse(const SListInfo& L) {
    LNode* p = L.head->next;

    while (p != nullptr) {
        cout << p->data;
        if (p->next != nullptr)
            cout << " ";
        p = p->next;
    }

    cout << endl;
}

void DestroyList(SListInfo& L) {
    LNode* p = L.head;

    while (p != nullptr) {
        LNode* next = p->next;
        free(p);
        p = next;
    }

    L.head = nullptr;
    L.length = 0;
}*/

/*
int main() {
    int n, m;
    cin >> n >> m;

    SListInfo L;

    if (InitList(L) != OK)
        return 1;

    if (CreateList(L, n) != OK) {
        DestroyList(L);
        return 1;
    }

    for (int i = 0; i < m; i++) {
        int p, q;
        cin >> p >> q;
        MoveStudent(L, p, q);
    }

    ListTraverse(L);

    DestroyList(L);
    return 0;
}
*/