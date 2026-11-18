#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
using namespace std;

typedef int TElemType;
typedef int Status;
const Status OK = 1;
const Status ERROR = 0;

struct BiTNode {
    TElemType data;
    BiTNode *lchild, *rchild;
};
using BiTree = BiTNode*;

struct SeqQueue {
    BiTree *data;
    int front, rear, maxSize;
};

// 1.初始化二叉树
Status InitQueue(SeqQueue &Q) {
    Q.maxSize = 100;
    Q.data = (BiTree*)malloc(Q.maxSize * sizeof(BiTree));
    if (!Q.data) return ERROR;
    Q.front = Q.rear = 0;
    return OK;
}

// 2.判断队列是否为空
Status QueueEmpty(SeqQueue Q) {
    return Q.front == Q.rear ? OK : ERROR;
}

// 3.入队
Status EnQueue(SeqQueue &Q, BiTree e) {
    if ((Q.rear + 1) % Q.maxSize == Q.front) return ERROR; // 队列满
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % Q.maxSize;
    return OK;
}

// 4.出队
Status DeQueue(SeqQueue &Q, BiTree &e) {
    if (QueueEmpty(Q)) return ERROR; // 队列空
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % Q.maxSize;
    return OK;
}

// 1.创建二叉树
Status InitBiTree(BiTree &T) {
    if (T != nullptr) return ERROR;
    T = nullptr;
    return OK;
}

// 2.销毁二叉树
Status DestroyBiTree(BiTree &T) {
    if (T == nullptr) return ERROR;
    if (T) {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free (T) ;
        T = nullptr;
    }
    return OK;
}

// 3.创建二叉树
Status CreateBiTree(BiTree &T) {
    char ch;
    cin >> ch;
    if (ch == '#') {
        T = nullptr;
    }else {
        T = (BiTree)malloc(sizeof(BiTree));
        T->data = ch - '0';
        T->lchild = nullptr; T->rchild = nullptr;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

// 4.判断二叉树是否为空
Status BiTreeEmpty(BiTree T) {
    return (T == nullptr ? OK : ERROR);
}

// 5.求二叉树的深度
int BiTreeDepth(BiTree T) {
    if (T == nullptr) {
        return 0;
    }else {
        int ld = BiTreeDepth(T->lchild);
        int rd = BiTreeDepth(T->rchild);
        return max(ld, rd) + 1;
    }
}

// 6.求二叉树的根节点
Status Root(BiTree &T, TElemType &e) {
    if( T == nullptr) return ERROR;
    e = T->data;
    return OK;
}

// 7.求二叉树的某个节点的值
Status Value(BiTree &cur_p, TElemType &e) {
    if(cur_p == nullptr) return ERROR;
    e = cur_p->data;
    return OK;
}

// 8.求二叉树的某个节点的父节点
BiTree Parent(BiTree &T, BiTree &cur_p) {
    if (!T || T == cur_p) return nullptr;
    if (T->lchild == cur_p || T->rchild == cur_p) {
        return T;
    }
    BiTree p = Parent(T->lchild, cur_p);
    return p ? p : Parent(T->rchild, cur_p);
}

// 9.求二叉树的某个节点的左孩子
BiTree LeftChild(BiTree &cur_p) {
    return cur_p ? cur_p->lchild : nullptr;
}

// 10.求二叉树的某个节点的右孩子
BiTree RightChild(BiTree &cur_p) {
    return cur_p ? cur_p->rchild : nullptr;
}

// 11.求二叉树的某个节点的左兄弟
BiTree LeftSibling(BiTree &T, BiTree & cur_p){
    BiTree p = Parent(T, cur_p);
    return (p && p->lchild != cur_p) ? p->lchild : nullptr;
}

// 12.求二叉树的某个节点的右兄弟
BiTree RightSibling(BiTree &T, BiTree & cur_p){
    BiTree p = Parent(T, cur_p);
    return (p && p->rchild != cur_p) ? p->rchild : nullptr;
}

// 13.修改二叉树的某个节点的值
Status Assign(BiTree &cur_p, TElemType value) {
    if(cur_p == nullptr) {
        return ERROR;
    }
    cur_p->data = value;
    return OK;
}

// 14.寻找二叉树中值为e的节点
BiTree FindNode(BiTree &T, TElemType e) {
    if (!T) return nullptr;
    if (T->data == e) return T;
    BiTree p = FindNode(T->lchild, e);
    return p ? p : FindNode(T->rchild, e);
}

// 15.插入子树
Status InsertChild(BiTree & cur_p, int LR, BiTree &c) {
    if (!cur_p || !c) return ERROR;
    if(LR == 0) {
        c->rchild = cur_p->lchild;
        cur_p->lchild = c;
    } else {
        c->rchild = cur_p->rchild;
        cur_p->rchild = c;
    }
    return OK;
}

// 16.删除子树
Status DeleteChild(BiTree &cur_p, int LR) {
    if(!cur_p) return ERROR;
    BiTree &child = (LR == 0) ? cur_p->lchild : cur_p->rchild;
    if(child) {
        DestroyBiTree(child);
        child = nullptr;
    }
    return OK;
}

// 17.前序遍历
void PreOrderTraverse( BiTree  T ) { 
    if( T!=NULL ) { 
        printf("%d ",T->data);
        PreOrderTraverse( T->lchild );
        PreOrderTraverse( T->rchild );
    } 
}

// 18.中序遍历
void InOrderTraverse(BiTree T) {
    if(T != nullptr) {
        InOrderTraverse(T->lchild);
        printf("%d ", T->data);
        InOrderTraverse(T->rchild);
    }
}

// 19.后序遍历
void PostOrderTraverse(BiTree T) {
    if (T != nullptr) {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%d ", T->data);
    }
}
 
// 20.层序遍历
#define MAX_SIZE 256
void LevelOrderTraverse(BiTree T) {
    if (T == nullptr) return;
    BiTNode* p;
    SeqQueue Q;
    InitQueue(Q);
    EnQueue(Q, T);
    while(!QueueEmpty(Q)) {
        DeQueue(Q, p);
        printf("%d ", p->data);
        if(p->lchild != nullptr) {
            EnQueue(Q,p->lchild);
        }
        if(p->rchild != nullptr) {
            EnQueue(Q,p->rchild);
        }
    }
    free(Q.data);
}

void PrintTraversals(BiTree T) {
    cout << "先序: "; PreOrderTraverse(T); cout << '\n';
    cout << "中序: "; InOrderTraverse(T); cout << '\n';
    cout << "后序: "; PostOrderTraverse(T); cout << '\n';
    cout << "层序: "; LevelOrderTraverse(T); cout << '\n';
}


int main() {
    BiTree T = nullptr;
    TElemType e;
    BiTree p = nullptr;

    // 1. 初始化及空树测试
    cout << "InitBiTree: " << InitBiTree(T) << '\n';
    cout << "Empty: " << BiTreeEmpty(T) << '\n';
    cout << "Depth: " << BiTreeDepth(T) << '\n';
    cout << "Root(empty): " << Root(T, e) << '\n';

    // 2. 先序创建二叉树，# 表示空结点
    // 主树：124##5##36##7##
    // 后续插入的子树：8## 和 9##
    istringstream input("124##5##36##7## 8## 9##");
    streambuf* oldBuf = cin.rdbuf(input.rdbuf());

    cout << "\nCreateBiTree: " << CreateBiTree(T) << '\n';
    cout << "Empty: " << BiTreeEmpty(T) << '\n';
    cout << "Depth: " << BiTreeDepth(T) << '\n';
    PrintTraversals(T);

    // 3. 根结点、结点值和双亲测试
    BiTree p2 = FindNode(T, 2);
    BiTree p4 = FindNode(T, 4);
    BiTree p5 = FindNode(T, 5);

    Root(T, e);
    cout << "\nRoot: " << e << '\n';

    Value(p4, e);
    cout << "Value(4): " << e << '\n';

    p = Parent(T, p4);
    cout << "Parent(4): " << (p ? p->data : -1) << '\n';

    p = Parent(T, T);
    cout << "Parent(root): " << (p ? p->data : -1) << '\n';

    // 4. 左右孩子及左右兄弟测试
    p = LeftChild(p2);
    cout << "LeftChild(2): " << (p ? p->data : -1) << '\n';

    p = RightChild(p2);
    cout << "RightChild(2): " << (p ? p->data : -1) << '\n';

    p = LeftSibling(T, p5);
    cout << "LeftSibling(5): " << (p ? p->data : -1) << '\n';

    p = RightSibling(T, p4);
    cout << "RightSibling(4): " << (p ? p->data : -1) << '\n';

    p = LeftSibling(T, p4);
    cout << "LeftSibling(4): " << (p ? p->data : -1) << '\n';

    p = RightSibling(T, p5);
    cout << "RightSibling(5): " << (p ? p->data : -1) << '\n';

    // 5. 查找和赋值测试
    cout << "\nFindNode(5): "
         << (FindNode(T, 5) ? OK : ERROR) << '\n';
    cout << "FindNode(8): "
         << (FindNode(T, 8) ? OK : ERROR) << '\n';

    cout << "Assign(5->0): " << Assign(p5, 0) << '\n';
    cout << "FindNode(0): "
         << (FindNode(T, 0) ? OK : ERROR) << '\n';

    cout << "After Assign: ";
    PreOrderTraverse(T);
    cout << '\n';

    // 6. 插入左子树
    BiTree c1 = nullptr;
    InitBiTree(c1);
    CreateBiTree(c1);  // 读取 8##

    cout << "\nInsertLeft: "
         << InsertChild(p2, 0, c1) << '\n';

    // 插入后 c1 已属于 T，不能单独销毁
    c1 = nullptr;

    cout << "After InsertLeft: ";
    PreOrderTraverse(T);
    cout << '\n';

    // 7. 插入右子树
    BiTree c2 = nullptr;
    InitBiTree(c2);
    CreateBiTree(c2);  // 读取 9##

    cout << "InsertRight: "
         << InsertChild(p2, 1, c2) << '\n';

    c2 = nullptr;

    cout << "After InsertRight:\n";
    PrintTraversals(T);

    // 8. 删除左右子树
    cout << "\nDeleteRight: "
         << DeleteChild(p2, 1) << '\n';
    cout << "After DeleteRight: ";
    PreOrderTraverse(T);
    cout << '\n';

    cout << "DeleteLeft: "
         << DeleteChild(p2, 0) << '\n';
    cout << "After DeleteLeft: ";
    PreOrderTraverse(T);
    cout << '\n';

    cout << "Depth: " << BiTreeDepth(T) << '\n';

    // 9. 销毁二叉树
    cout << "\nDestroyBiTree: " << DestroyBiTree(T) << '\n';
    cout << "Empty: " << BiTreeEmpty(T) << '\n';
    cout << "Depth: " << BiTreeDepth(T) << '\n';

    cin.rdbuf(oldBuf);
    return 0;
}
