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
    L.tail = L.head;;
    L.length = 0;

    return OK;
}

Status AppendElem(SListInfo& L, ElemType e) {
    if(L.head == nullptr) {
        cout << "List not initialized." << endl;
        return ERROR;
    }

    LNode* p = (LNode*)malloc(sizeof(LNode));
    if(p == nullptr) {
        cout << "Memory allocation failed." << endl;
        return ERROR;
    }

    p->data = e;
    p->next = nullptr;
    L.tail->next = p;
    L.tail = p;

    L.length++;

    return OK;
}

Status SortDescending(SListInfo& L) {
    if (L.head == nullptr) {
        cout << "List not initialized." << endl;
        return ERROR;
    }

    for (LNode* p = L.head->next; p != nullptr; p = p->next) {
        LNode* maxNode = p;

        for (LNode* q = p->next; q != nullptr; q = q->next) {
            if (q->data > maxNode->data) {
                maxNode = q;
            }
        }

        ElemType temp = p->data;
        p->data = maxNode->data;
        maxNode->data = temp;
    }
    
    return OK;
}

Status ListTraverse(const SListInfo& L){
    if(L.head == nullptr) {
        cout << "List not initialized." << endl;
        return ERROR;
    }

    LNode*p = L.head->next;
    while(p != nullptr) {
        cout << p->data;

        if (p->next != nullptr) {
            cout << " ";
        }
        p = p->next;
    }

    return OK;
}

Status MergeUnion (SListInfo& A, SListInfo& B) {
    if(A.head == nullptr || B.head == nullptr) {
        cout << "One or both lists not initialized." << endl;
        return ERROR;
    }

    LNode* p = A.head->next;
    LNode* q = B.head->next;
    LNode* r = A.head;
    A.length = 0;

    while(p != nullptr || q != nullptr) {
        LNode* node;

        if (q == nullptr || (p != nullptr && p->data >= q->data)) {
            node = p;
            p = p->next;
        }else {
            node = q;
            q = q->next;
        }

        if (r != A.head && r->data == node->data) {
            free(node);
        } else {
            r->next = node;
            r = node;
            A.length++;
        }
    }

    r->next = nullptr;
    A.tail = r;
    B.head = nullptr;
    B.tail = B.head;
    B.length = 0;

    return OK;
}

Status ClearList(SListInfo& L) {
    if ( L.head == nullptr) {
        cout << "List not initialized." << endl;
        return ERROR;
    }

    LNode* p =L.head->next;
    while(p != nullptr) {
        LNode* temp = p;
        p = p->next;
        free(temp);
    }

    L.head->next =nullptr;
    L.tail = L.head;
    L.length = 0;

    return OK;
}

Status DestroyList(SListInfo& L) {
    if (L.head == nullptr) {
        cout << "List not initialized." << endl;
        return ERROR;
    }

    ClearList(L);
    free(L.head);
    L.head = nullptr;
    L.tail = nullptr;
    L.length = 0;

    return OK;
}

int main() {
    // 第一组：固定数据测试，覆盖全部已实现的函数。
    SListInfo X, Y;
    if (InitList(X) != OK || InitList(Y) != OK) return 1;

    int x[] = {7, 2, 9, 7, 5};
    int y[] = {3, 9, 10, 3, 7};
    for (int v : x) if (AppendElem(X, v) != OK) return 1;
    for (int v : y) if (AppendElem(Y, v) != OK) return 1;

    SortDescending(X);
    SortDescending(Y);
    cout << "Fixed test:" << endl;
    cout << "A: "; ListTraverse(X); cout << endl;
    cout << "B: "; ListTraverse(Y); cout << endl;
    MergeUnion(X, Y);
    cout << "C: "; ListTraverse(X); cout << endl;
    cout << "B length after merge: " << Y.length << endl;

    SListInfo A, B;
    if (InitList(A) != OK || InitList(B) != OK) return 1;
    srand(1);
    bool appeared[100] = {};
    for (int i = 0; i < 30; i++) {
        int v = rand() % 100;
        appeared[v] = true;
        if (AppendElem(A, v) != OK) return 1;
    }
    for (int i = 0; i < 50; i++) {
        int v = rand() % 100;
        appeared[v] = true;
        if (AppendElem(B, v) != OK) return 1;
    }
    cout << "Random test:" << endl;
    cout << "Input lengths: " << A.length << " " << B.length << endl;
    SortDescending(A);
    SortDescending(B);
    MergeUnion(A, B);

    int distinct = 0;
    for (bool flag : appeared) if (flag) distinct++;
    bool correct = (A.length == distinct && B.length == 0);
    int previous = 100;
    for (LNode* p = A.head->next; p != nullptr; p = p->next) {
        if (p->data < 0 || p->data >= 100 || p->data >= previous || !appeared[p->data]) {
            correct = false;
            break;
        }
        previous = p->data;
    }
    cout << "Union correct: " << (correct ? "YES" : "NO") << endl;

    SListInfo* lists[] = {&X, &Y, &A, &B};
    for (SListInfo* L : lists) {
        LNode* p = L->head;
        while (p != nullptr) {
            LNode* next = p->next;
            free(p);
            p = next;
        }
        L->head = L->tail = nullptr;
        L->length = 0;
    }
    return 0;
}


