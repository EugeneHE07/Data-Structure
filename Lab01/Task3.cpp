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

int ListLength(const SListInfo& L) {
    return L.length;
}

bool ListEmpty (const SListInfo& L) {
    return L.length == 0;
}

Status ClearList(SListInfo& L) {
    if (L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;

    while (p != nullptr) {
        LNode* q = p;
        p = p->next;
        free(q);
    }
    L.head->next = nullptr;
    L.tail = L.head;
    L.length = 0;

    return OK;
}

Status DestroyList(SListInfo& L) {
    if(L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* temp = L.head;
    free(temp);

    L.head = nullptr;
    L.tail = nullptr;
    L.length = 0;

    return OK;
}

Status InsertElem(SListInfo& L, int position, ElemType e) {
    if (L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    if (position < 1 || position > L.length + 1){
        cout << "Invalid position." << endl;
        return ERROR;
    }

    LNode* NewNode = (LNode*)malloc(sizeof(LNode));
    if (!NewNode) {
        cout << "Memory allocation failed." << endl;
        return ERROR;
    }

    NewNode->data = e;
    NewNode->next = nullptr;

    LNode* p = L.head;

    while (--position) {
        p = p->next;
    }

    NewNode->next = p->next;
    p->next = NewNode;

    if (NewNode->next == nullptr) {
        L.tail = NewNode;
    }

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
*/

Status RemoveDuplicatesSorted(SListInfo& L) {
    if (L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;
    LNode* prev = L.head;

    while (p != nullptr) {
        if(p->data == prev->data) {
            prev->next = p->next;
            if(p == L.tail) {
                L.tail = prev; 
            }

            LNode* temp = p;
            p = p->next;

            free(temp);
            L.length--;
        }else {
            prev = p;
            p = p->next;
        }
    }
    return OK;
}

Status RemoveDuplicatesUnsorted(SListInfo& L) {
    if(L.head == nullptr) {
        cout << "List is not initialized." << endl;
        return ERROR;
    }

    LNode* p = L.head->next;

    while ( p != nullptr) {
        LNode* prev = p;
        LNode* curr = p->next;

        while (curr != nullptr) {
            if(curr->data == p->data) {
                prev->next = curr->next;
                if(curr == L.tail) {
                    L.tail = prev;
                }

                free(curr);
                L.length--;
                curr = prev->next;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
        p = p->next;
    }

    return OK;
}

/*
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

    cout << "Remove: "
         << (RemoveDuplicatesUnsorted(L) == OK) << endl;

    cout << "After (" << ListLength(L) << "): ";
    ListTraverse(L);

    // 2. 检查尾指针及当前指针是否有效
    cout << "Tail: " << L.tail->data << endl;
    cout << "Tail/Cur valid: "
         << (L.tail->next == nullptr) << endl;

    // 3. 再次去重，验证结果不变
    RemoveDuplicatesUnsorted(L);
    cout << "Remove Again Length: "
         << ListLength(L) << endl;

    // 4. 清空并销毁
    cout << "Clear: " << (ClearList(L) == OK) << endl;
    cout << "Empty: " << ListEmpty(L) << endl;
    cout << "Destroy: " << (DestroyList(L) == OK) << endl;

    return 0;
}
*/
