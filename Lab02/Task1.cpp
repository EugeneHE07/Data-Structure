
#include <iostream>
#include <cstdlib>
#include <random>
using namespace std;

using ElemType = int;
using Status = int;

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

/*
Status InitList(SListInfo& L) {
    if (L.head != nullptr)
        return ERROR;

    L.head = (LNode*)malloc(sizeof(LNode));
    if (L.head == nullptr)
        return ERROR;

    L.head->next = nullptr;
    L.tail = L.head;
    L.length = 0;
    return OK;
}

Status AppendElem(SListInfo& L, ElemType e) {
    if (L.head == nullptr)
        return ERROR;

    LNode* p = (LNode*)malloc(sizeof(LNode));
    if (p == nullptr)
        return ERROR;

    p->data = e;
    p->next = nullptr;
    L.tail->next = p;
    L.tail = p;
    ++L.length;

    return OK;
}

Status ListTraverse(const SListInfo& L, int maxCount = -1) {
    if (L.head == nullptr)
        return ERROR;

    LNode* p = L.head->next;
    int shown = 0;

    while (p != nullptr && (maxCount < 0 || shown < maxCount)) {
        if (shown > 0)
            cout << " ";

        cout << p->data;
        p = p->next;
        ++shown;
    }

    if (p != nullptr)
        cout << " ...";

    return OK;
}

Status DestroyList(SListInfo& L) {
    if (L.head == nullptr)
        return ERROR;

    LNode* p = L.head;
    while (p != nullptr) {
        LNode* next = p->next;
        free(p);
        p = next;
    }

    L.head = nullptr;
    L.tail = nullptr;
    L.length = 0;
    return OK;
}
*/


// !选择排序
Status SelectionSort(SListInfo& L) {
    if (L.head == nullptr)
        return ERROR;

    for (LNode* p = L.head->next; p != nullptr; p = p->next) {
        LNode* minNode = p;

        for (LNode* q = p->next; q != nullptr; q = q->next) {
            if (q->data < minNode->data) {
                minNode = q;
            }
        }

        if (minNode != p) {
            // 交换数据
            ElemType temp = p->data;
            p->data = minNode->data;
            minNode->data = temp;
        }
    }

    return OK;
}

// !冒泡排序
Status BubbleSort(SListInfo& L) {
    if (L.head == nullptr)
        return ERROR;

    for (int i = 0; i < L.length - 1; ++i) {
        bool swapped = false;
        LNode* p = L.head->next;

        for (int j = 0; j < L.length - 1 - i; ++j) {
            if(p->data > p->next->data) {
                ElemType temp = p->data;
                p->data = p->next->data;
                p->next->data = temp;
                swapped = true;
            }

            p = p->next;
        }

        if (!swapped)
            break;
    }

    return OK;
}

/*
// 测试辅助函数：检查升序和原始元素是否全部保留
bool VerifySorted(const SListInfo& L, const int original[], int n) {
    if (L.head == nullptr || L.length != n)
        return false;

    int count[100] = {};
    for (int i = 0; i < n; ++i)
        ++count[original[i]];

    int visited = 0;
    int previous = -1;

    for (LNode* p = L.head->next; p != nullptr; p = p->next) {
        if (p->data < 0 || p->data >= 100 ||
            p->data < previous || --count[p->data] < 0)
            return false;

        previous = p->data;
        ++visited;
    }

    if (visited != n)
        return false;

    for (int c : count)
        if (c != 0)
            return false;

    return true;
}

int main() {
    SListInfo A{}, B{}, E{};
    cout << boolalpha;

    // 1. 初始化三条链表
    if (InitList(A) != OK) return 1;
    if (InitList(B) != OK) {
        DestroyList(A);
        return 1;
    }
    if (InitList(E) != OK) {
        DestroyList(A);
        DestroyList(B);
        return 1;
    }
    cout << "Init: true" << endl;

    // 2. 两条链表使用相同的100个随机整数
    mt19937 rng(2026);
    int values[100];
    bool appendOK = true;

    for (int i = 0; i < 100; ++i) {
        values[i] = static_cast<int>(rng() % 100);

        if (AppendElem(A, values[i]) != OK ||
            AppendElem(B, values[i]) != OK) {
            appendOK = false;
            break;
        }
    }

    cout << "Append 100: " << appendOK << endl;

    if (!appendOK) {
        DestroyList(A);
        DestroyList(B);
        DestroyList(E);
        return 1;
    }

    cout << "Input Lengths: " << A.length
         << " / " << B.length << endl;

    cout << "Original first 10: ";
    ListTraverse(A, 10);
    cout << endl;

    // 3. 执行两种排序并检查结果
    bool selectionOK = SelectionSort(A) == OK;
    bool bubbleOK = BubbleSort(B) == OK;

    cout << "Selection Correct: "
         << (selectionOK && VerifySorted(A, values, 100)) << endl;

    cout << "Bubble Correct: "
         << (bubbleOK && VerifySorted(B, values, 100)) << endl;

    cout << "Selection first 10: ";
    ListTraverse(A, 10);
    cout << endl;

    cout << "Bubble first 10: ";
    ListTraverse(B, 10);
    cout << endl;

    // 4. 检查长度和尾指针
    cout << "Tail Valid: "
         << (A.length == 100 && B.length == 100 &&
             A.tail->next == nullptr && B.tail->next == nullptr)
         << endl;

    // 5. 空链表和单结点链表边界测试
    cout << "Empty Sorts: "
         << (SelectionSort(E) == OK &&
             BubbleSort(E) == OK && E.length == 0) << endl;

    bool singleOK = AppendElem(E, 42) == OK;
    singleOK = singleOK &&
               SelectionSort(E) == OK &&
               BubbleSort(E) == OK;

    cout << "Single Sorts: "
         << (singleOK && E.length == 1 &&
             E.head->next->data == 42 &&
             E.tail == E.head->next) << endl;

    // 6. 释放全部内存
    bool destroyed = DestroyList(A) == OK;
    destroyed = (DestroyList(B) == OK) && destroyed;
    destroyed = (DestroyList(E) == OK) && destroyed;

    cout << "Destroy: " << destroyed << endl;

    return 0;
}
*/
