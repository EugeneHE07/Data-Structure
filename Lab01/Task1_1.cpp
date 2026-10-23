#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

/**
 * 顺序表结构
 */
struct SqList {
  int *data = nullptr;
  int length = 0;
  int capacity = 0;
};

// 初始化顺序表 L，分配内存空间并设置初始长度和容量
bool init_list(SqList &L) {
  if (L.data != nullptr) {
    return false;
  }

  L.data = new int[MAX_SIZE];
  L.capacity = MAX_SIZE;
  L.length = 0;
  return true;
}

// 销毁顺序表 L，释放其占用的内存空间
void destroy_list(SqList &L) {
  if (L.data != nullptr) {
    delete[] L.data;
    L.data = nullptr;
    L.length = 0;
    L.capacity = 0;
  }
}

// 清空顺序表 L 中的所有元素
void clear_list(SqList &L) {
  if (L.data != nullptr) {
    L.length = 0;
  }
}

// 判断顺序表 L 是否为空
bool list_empty(SqList &L) {
  if (L.data != nullptr) {
    return (L.length == 0);
  }
  return false;
}

// 获取顺序表 L 的长度
int list_length(SqList &L) {
  if (L.data != nullptr) {
    return L.length;
  }
  return -1;
}

// 获取顺序表 L 中第 i 个元素的值，并将其赋给 e
bool get_elem(const SqList &L, int i, int &e) {
  if (L.data != nullptr && i >= 1 && i <= L.length) {
    e = L.data[i - 1];
    return true;
  }
  return false;
}

// 找到元素 e 在顺序表 L 中的位置，若存在则返回其位置（从 1 开始），否则返回 0。
int locate_elem(const SqList &L, int e) {
  if (L.data == nullptr) {
    return 0;
  }

  for (int i = 0; i < L.length; i++) {
    if (L.data[i] == e) {
      return i + 1;
    }
  }
  return 0;
}

// 将顺序表 L 中第 i 个元素的值修改为 e，并将原值赋给 e
bool set_elem(SqList &L, int i, int &e) {
  if (L.data != nullptr && i >= 1 && i <= L.length) {
    int old_value = L.data[i - 1];
    L.data[i - 1] = e;
    e = old_value;
    return true;
  }
  return false;
}

// 找到顺序表 L 中元素 cur_e 的前驱元素，若存在则返回 true 并将前驱元素赋给 pre_e
bool prior_elem(const SqList &L, int cur_e, int &pre_e) {
  int pos = locate_elem(L, cur_e);
  if (pos > 1) {
    pre_e = L.data[pos - 2];
    return true;
  }
  return false;
}

// 找到顺序表 L 中元素 cur_e 的后继元素，若存在则返回 true 并将后继元素赋给 next_e
bool next_elem(const SqList &L, int cur_e, int &next_e) {
  int pos = locate_elem(L, cur_e);

  if (pos > 0 && pos < L.length) {
    next_e = L.data[pos];
    return true;
  }
  return false;
}

// 遍历顺序表 L 中的所有元素并打印
void list_traverse(const SqList &L) {
  if (L.data == nullptr) {
    cout << "List is not initialized." << endl;
    return;
  }

  for (int i = 0; i < L.length; i++) {
    cout << L.data[i] << endl;
  }

  cout << endl;
}

// 在顺序表 L 的第 i 个位置插入元素 e
bool insert_elem(SqList &L, int i, int e) {
  if (L.data != nullptr && i >= 1 && i <= L.length + 1 &&
      L.length + 1 <= L.capacity) {
    for (int j = L.length; j >= i; j--) {
      L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = e;
    L.length++;
    return true;
  }
  return false;
}

int main() {
  SqList L;

  init_list(L);

  cout << "初始化: " << endl;
  cout << list_empty(L) << " " << int(list_length(L)) << endl;

  // 初始化线性表
  L.data[0] = 10;
  L.data[1] = 20;
  L.length = 2;

  int values[] = {10, 20, 30, 40, 50};

  cout << "初始化后: " << endl;
  cout << list_empty(L) << " " << int(list_length(L)) << endl;

  int e1 = -1;
  cout << get_elem(L, 2, e1) << " " << e1 << endl;
  cout << get_elem(L, 3, e1) << " " << e1 << endl;

  clear_list(L);

  cout << "清除后: " << endl;
  cout << list_empty(L) << " " << int(list_length(L)) << endl;

  for (int i = 0; i < 5; i++) {
    L.data[i] = values[i];
  }
  L.length = 5;

  cout << locate_elem(L, 20) << endl;
  cout << locate_elem(L, 50) << endl;
  cout << locate_elem(L, 99) << endl;

  int e2;
  cout << "查找前驱和后继:" << endl;

  if (prior_elem(L, 30, e2)) {
    cout << "30前驱: " << e2 << endl;
  } else {
    cout << "错误" << endl;
  }

  if (next_elem(L, 30, e2)) {
    cout << "30后继: " << e2 << endl;
  } else {
    cout << "错误" << endl;
  }

  list_traverse(L);

  int e = 99;

  if (set_elem(L, 2, e)) {
    cout << "修改后: " << e << endl;
  }

  list_traverse(L);

  destroy_list(L);

  SqList L2;
  init_list(L2);

  insert_elem(L2, 1, 10);
  insert_elem(L2, 2, 20);
  insert_elem(L2, 3, 30);
  insert_elem(L2, 4, 40);

  list_traverse(L2);

  insert_elem(L2, 3, 99);

  list_traverse(L2);
  cout << "长度: " << list_length(L2) << endl;

  cout << "状态: " << endl;
  cout << (L.data == nullptr) << " " << L2.length << " " << L2.capacity << endl;

  return 0;
}