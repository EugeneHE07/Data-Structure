
#include <cstdlib>
#include <iostream>

using namespace std;

typedef int Status;
const int OK = 1;
const int ERROR = 0;

struct LNode {
  int id;
  int x1, y1, x2, y2;
  LNode *next;
};

struct SListInfo {
  LNode *head = nullptr;
  LNode *tail = nullptr;
  int length = 0;
};

Status InitList(SListInfo &L) {
  if (L.head != nullptr)
    return ERROR;

  L.head = (LNode *)malloc(sizeof(LNode));
  if (L.head == nullptr)
    return ERROR;

  L.head->next = nullptr;
  L.tail = L.head;
  L.length = 0;
  return OK;
}

Status InsertWindow(SListInfo &L, int id, int x1, int y1, int x2, int y2) {
  LNode *p = (LNode *)malloc(sizeof(LNode));
  if (p == nullptr)
    return ERROR;

  p->id = id;
  p->x1 = x1;
  p->y1 = y1;
  p->x2 = x2;
  p->y2 = y2;

  p->next = L.head->next;
  L.head->next = p;

  if (L.length == 0)
    L.tail = p;

  L.length++;
  return OK;
}

int ClickWindow(SListInfo &L, int x, int y) {
  LNode *pre = L.head;
  LNode *p = L.head->next;

  while (p != nullptr) {
    if (x >= p->x1 && x <= p->x2 && y >= p->y1 && y <= p->y2) {

      if (pre != L.head) {
        pre->next = p->next;

        if (p == L.tail)
          L.tail = pre;

        p->next = L.head->next;
        L.head->next = p;
      }

      return p->id;
    }

    pre = p;
    p = p->next;
  }

  return -1;
}

Status DestroyList(SListInfo &L) {
  LNode *p = L.head;

  while (p != nullptr) {
    LNode *q = p;
    p = p->next;
    free(q);
  }

  L.head = nullptr;
  L.tail = nullptr;
  L.length = 0;
  return OK;
}

int main() {
  int N, M;
  cin >> N >> M;

  SListInfo L;
  if (InitList(L) == ERROR)
    return 0;

  for (int i = 1; i <= N; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    if (InsertWindow(L, i, x1, y1, x2, y2) == ERROR) {
      DestroyList(L);
      return 0;
    }
  }

  for (int i = 0; i < M; i++) {
    int x, y;
    cin >> x >> y;

    int result = ClickWindow(L, x, y);

    if (result == -1)
      cout << "IGNORED" << endl;
    else
      cout << result << endl;
  }

  DestroyList(L);
  return 0;
}
