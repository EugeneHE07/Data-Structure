#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include <cstring>
using namespace std;

typedef int TElemType;
typedef int Status;
const Status OK = 1;
const Status ERROR = 0;

struct BiTNode {
    TElemType data;
    BiTNode* lchild, *rchild;
};

struct SeqQueue {
    BiTNode** data;
    int front, rear, maxSize;
};

Status InitQueue(SeqQueue& Q) {
    Q.maxSize = 100;
    Q.data = (BiTNode**)malloc(Q.maxSize * sizeof(BiTNode*));
    if (!Q.data) return ERROR;
    Q.front = Q.rear = 0;
    return OK;
}

Status QueueEmpty(SeqQueue Q) {
    return Q.front == Q.rear ? OK : ERROR;
}

Status EnQueue(SeqQueue& Q, BiTNode* e) {
    if ((Q.rear + 1) % Q.maxSize == Q.front) return ERROR;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % Q.maxSize;
    return OK;
}

Status DeQueue(SeqQueue& Q, BiTNode*& e) {
    if (QueueEmpty(Q)) return ERROR;
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % Q.maxSize;
    return OK;
}

Status DestroyQueue(SeqQueue& Q) {
    free(Q.data);
    Q.data = nullptr;
    Q.front = Q.rear = Q.maxSize = 0;
    return OK;
}

using BiTree = BiTNode*;

Status InitBiTree(BiTree& T) {
    if (T != nullptr) return ERROR;
    T = nullptr;
    return OK;
}

Status DestroyBiTree(BiTree& T) {
    if (T == nullptr) return OK;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T = nullptr;
    return OK;
}

int BiTreeDepth(BiTree& T) {
    if(!T) return 0;
    return max(BiTreeDepth(T->lchild),BiTreeDepth(T->rchild))+1;
}

void PreOrderTraverse(BiTree& T) {
    if (!T) return;
    cout << T->data << ' ';
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

void InOrderTraverse(BiTree& T) {
    if (!T) return;
    InOrderTraverse(T->lchild);
    cout << T->data << ' ';
    InOrderTraverse(T->rchild);
}

void PostOrderTraverse(BiTree& T) {
    if (!T) return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    cout << T->data << ' ';
}

void PreOrderTraverse_NonRecursion(BiTree& T) {
    stack<BiTree> S;
    BiTree p = T;
    while (p || !S.empty()) {
        while (p) {
            cout << p->data << ' ';
            S.push(p);
            p = p->lchild;
        }
        if (!S.empty()) {
            p = S.top(); S.pop();
            p = p->rchild;
        }
    }
}

void InOrderTraverse_NonRecursion(BiTree T) {
    stack<BiTree> S;
    BiTree p = T;
    while (p || !S.empty()) {
        while (p) {
            S.push(p);
            p = p->lchild;
        }
        if (!S.empty()) {
            p = S.top(); S.pop();
            cout << p->data << ' ';
            p = p->rchild;
        }
    }
}

void PostOrderTraverse_NonRecursion(BiTree T) {
    struct Frame { BiTree ptr; int tag; };
    stack<Frame> S;
    BiTree p = T;
    while (p || !S.empty()) {
        while (p) {
            S.push({p, 0});
            p = p->lchild;
        }
        if (S.top().tag == 0) {
            S.top().tag = 1;
            p = S.top().ptr->rchild;
        } else {
            cout << S.top().ptr->data << ' ';
            S.pop();
        }
    }
}

void TraverseBiTree_NonRecursion(BiTree T, const char order[]) {
    if (!T || !order) return;
    if (strlen(order) != 3) return;
    string check = order;
    sort(check.begin(), check.end());
    if (check != "LRr") return;

    struct Frame { BiTree ptr; int tagIndex; };
    stack<Frame> S;
    S.push({T, 0});
    while (!S.empty()) {
        Frame x = S.top(); S.pop();
        if (x.tagIndex + 1 < 3)
            S.push({x.ptr, x.tagIndex + 1});
        switch (order[x.tagIndex]) {
            case 'L':
                if (x.ptr->lchild) S.push({x.ptr->lchild, 0});
                break;
            case 'R':
                if (x.ptr->rchild) S.push({x.ptr->rchild, 0});
                break;
            case 'r':
                cout << x.ptr->data << ' ';
                break;
        }
    }
}

void LevelOrderTraverse(BiTree T) {
    if (!T) return;
    SeqQueue Q;
    if (!InitQueue(Q)) return;
    EnQueue(Q, T);
    BiTree p;
    while (!QueueEmpty(Q)) {
        DeQueue(Q, p);
        cout << p->data << ' ';
        if (p->lchild && !EnQueue(Q, p->lchild)) break;
        if (p->rchild && !EnQueue(Q, p->rchild)) break;
    }
    DestroyQueue(Q);
}