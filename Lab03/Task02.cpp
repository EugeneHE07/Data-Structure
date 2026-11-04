#include <iostream>
#include <cstdlib>
#include <random>
using namespace std;

typedef int ElemType;
typedef int Status;

const int ERROR = 0;
const int OK = 1;

struct QNode {
    ElemType data;
    QNode* next; 
};

struct LinkQueue {
    QNode* front = nullptr;
    QNode* rear = nullptr;
};

Status InitQueue(LinkQueue& Q) {
    if (Q.front != nullptr || Q.rear != nullptr) {
        return ERROR;
    }

    Q.front = (QNode*)malloc(sizeof(QNode));
    if (Q.front == nullptr) {
        return ERROR;
    }

    Q.rear = Q.front;
    Q.front->next = nullptr;

    return OK;
}

Status DestroyQueue(LinkQueue& Q) {
    if (Q.front == nullptr || Q.rear == nullptr) {
        return ERROR;
    }

    while (Q.front != nullptr) {
        QNode *temp = Q.front;
        Q.front = Q.front->next;
        free(temp);
    }

    Q.rear = nullptr;
    return OK;
}

Status ClearQueue(LinkQueue& Q) {
    if (Q.front == nullptr || Q.rear == nullptr) {
        return ERROR;
    }

    QNode* p = Q.front->next;
    while (p != nullptr) {
        QNode* temp = p;
        p = p->next;
        free(temp);
    }

    Q.front->next = nullptr;
    Q.rear = Q.front;

    return OK;
}

bool QueueEmpty(LinkQueue& Q) {
    if(Q.front == nullptr || Q.rear == nullptr) {
        return ERROR;
    }

    return Q.front == Q.rear;
}

int QueueLength(LinkQueue& Q) {
    int length = 0;
    QNode* p = Q.front->next;

    while (p != nullptr) {
        length++;
        p = p->next;
    }

    return length;
}

Status GetHead(LinkQueue& Q, ElemType& e) {
    if (Q.front == nullptr || Q.rear == nullptr || Q.front == Q.rear) {
        return ERROR;
    }

    e = Q.front->next->data;
    return OK;
}

Status QueueTraverse(LinkQueue& Q) {
    if (Q.front == nullptr || Q.rear == nullptr) {
        return ERROR;
    }

    QNode* p = Q.front->next;

    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }

    cout << endl;
    return OK;
}

Status EnQueue(LinkQueue& Q, ElemType e) {
    if (Q.front == nullptr || Q.rear == nullptr) {
        return ERROR;
    }

    QNode* p = (QNode*)malloc(sizeof(QNode));

    if (p == nullptr) {
        return ERROR;
    }
    p->data = e;
    p->next = nullptr;
    Q.rear->next = p;
    Q.rear = p;

    return OK;
}

Status DeQueue(LinkQueue& Q,ElemType& e) {
    if (Q.front == nullptr || Q.rear == nullptr || Q.front == Q.rear) {
        return ERROR;
    }

    QNode* p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;

    if (Q.rear == p) {
        Q.rear = Q.front;
    }

    free(p);
    return OK;
}

/*int main() {
    LinkQueue Q;
    ElemType e = -1;

    // 测试1：初始化、重复初始化及空队列操作
    cout << "InitQueue: " << InitQueue(Q) << endl;
    cout << "Init again: " << InitQueue(Q) << endl;
    cout << "Empty initially: " << QueueEmpty(Q) << endl;
    cout << "Length initially: " << QueueLength(Q) << endl;
    cout << "GetHead(empty): " << GetHead(Q, e) << endl;
    cout << "DeQueue(empty): " << DeQueue(Q, e) << endl;
    cout << "Traverse empty: ";
    QueueTraverse(Q);

    // 测试2：正常入队、读取队头及出队
    cout << "EnQueue 10: " << EnQueue(Q, 10) << endl;
    cout << "EnQueue 20: " << EnQueue(Q, 20) << endl;
    cout << "EnQueue 30: " << EnQueue(Q, 30) << endl;
    cout << "Traverse: ";
    QueueTraverse(Q);
    cout << "Length after insert: " << QueueLength(Q) << endl;
    cout << "Empty after insert: " << QueueEmpty(Q) << endl;

    Status result = GetHead(Q, e);
    cout << "GetHead: " << result << ", value: " << e << endl;
    cout << "Length after GetHead: " << QueueLength(Q) << endl;

    // 测试3：删除队头，验证队列顺序
    result = DeQueue(Q, e);
    cout << "DeQueue first: " << result << ", value: " << e << endl;
    cout << "Traverse after first dequeue: ";
    QueueTraverse(Q);
    cout << "Rear value: " << Q.rear->data << endl;

    // 测试4：删除剩余元素，验证队尾指针复位
    DeQueue(Q, e);
    result = DeQueue(Q, e);
    cout << "DeQueue last: " << result << ", value: " << e << endl;
    cout << "Empty after all dequeues: " << QueueEmpty(Q) << endl;
    cout << "Rear reset: " << (Q.rear == Q.front) << endl;
    cout << "DeQueue again: " << DeQueue(Q, e) << endl;

    // 测试5：队列变空后重新入队与清空
    cout << "EnQueue after empty: " << EnQueue(Q, 40) << endl;
    cout << "Traverse after reuse: ";
    QueueTraverse(Q);

    QNode* oldFront = Q.front;
    cout << "ClearQueue: " << ClearQueue(Q) << endl;
    cout << "Empty after clear: " << QueueEmpty(Q) << endl;
    cout << "Length after clear: " << QueueLength(Q) << endl;
    cout << "Head preserved: " << (Q.front == oldFront) << endl;
    cout << "Head next null: " << (Q.front->next == nullptr) << endl;
    cout << "Rear after clear: " << (Q.rear == Q.front) << endl;
    cout << "GetHead after clear: " << GetHead(Q, e) << endl;
    cout << "Clear again: " << ClearQueue(Q) << endl;

    // 测试6：50个随机整数入队
    mt19937 rng(2026);
    ElemType values[50];
    bool enqueued = true;

    for (int i = 0; i < 50; i++) {
        values[i] = (ElemType)(rng() % 1000);

        if (EnQueue(Q, values[i]) != OK) {
            enqueued = false;
            break;
        }
    }

    cout << "50 enqueues succeeded: " << enqueued << endl;
    cout << "Random queue: ";
    QueueTraverse(Q);
    cout << "Length after random enqueues: "
         << QueueLength(Q) << endl;

    if (!enqueued) {
        DestroyQueue(Q);
        return 1;
    }

    result = GetHead(Q, e);
    cout << "GetHead after random enqueues: " << result
         << ", value matches first: " << (e == values[0]) << endl;
    cout << "Rear matches last: "
         << (Q.rear->data == values[49]) << endl;

    // 测试7：连续出队50次，验证先进先出
    bool fifo = true;

    for (int i = 0; i < 50; i++) {
        if (DeQueue(Q, e) != OK || e != values[i]) {
            fifo = false;
            break;
        }
    }

    cout << "FIFO check: " << fifo << endl;
    cout << "Length after 50 dequeues: "
         << QueueLength(Q) << endl;
    cout << "Empty after 50 dequeues: "
         << QueueEmpty(Q) << endl;
    cout << "Rear reset after 50 dequeues: "
         << (Q.rear == Q.front) << endl;
    cout << "DeQueue after empty: " << DeQueue(Q, e) << endl;

    // 测试8：销毁非空队列及销毁后的非法操作
    cout << "EnQueue 77: " << EnQueue(Q, 77) << endl;
    cout << "EnQueue 88: " << EnQueue(Q, 88) << endl;
    cout << "DestroyQueue: " << DestroyQueue(Q) << endl;
    cout << "Pointers null: "
         << (Q.front == nullptr && Q.rear == nullptr) << endl;
    cout << "Destroy again: " << DestroyQueue(Q) << endl;
    cout << "Clear after destroy: " << ClearQueue(Q) << endl;
    cout << "GetHead after destroy: " << GetHead(Q, e) << endl;
    cout << "DeQueue after destroy: " << DeQueue(Q, e) << endl;
    cout << "EnQueue after destroy: " << EnQueue(Q, 99) << endl;
    cout << "Traverse after destroy: " << QueueTraverse(Q) << endl;

    // 测试9：重新初始化并最终销毁
    cout << "Reinit: " << InitQueue(Q) << endl;
    cout << "Empty after reinit: " << QueueEmpty(Q) << endl;
    cout << "Length after reinit: " << QueueLength(Q) << endl;
    cout << "Final destroy: " << DestroyQueue(Q) << endl;

    return 0;
}*/