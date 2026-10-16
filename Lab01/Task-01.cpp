#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

struct SqList {
  int *data = nullptr;
  int length = 0;
  int capacity = 0;
};

bool init_list(SqList &L) {
  if (L.data != nullptr) {
    return false;
  }

  L.data = new int[MAX_SIZE];
  L.capacity = MAX_SIZE;
  L.length = 0;
  return true;
}

void destroy_list(SqList &L) {
  if (L.data != nullptr) {
    delete[] L.data;
    L.data = nullptr;
    L.length = 0;
    L.capacity = 0;
  }
}

void clear_list(SqList &L) {
  if (L.data != nullptr) {
    L.length = 0;
  }
}

bool list_empty(SqList &L) {
  if (L.data != nullptr) {
    return (L.length == 0);
  }
  return false;
}

int list_length(SqList &L) {
  if (L.data != nullptr) {
    return L.length;
  }
  return -1;
}

bool get_elem(const SqList &L, int i, int &e) {
  if (L.data != nullptr && i >= 1 && i <= L.length) {
    e = L.data[i - 1];
    return true;
  }
  return false;
}

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

bool set_elem(SqList &L, int i, int &e) {
  if (L.data != nullptr && i >= 1 && i <= L.length) {
    int old_value = L.data[i - 1];
    L.data[i - 1] = e;
    e = old_value;
    return true;
  }
}

bool prior_elem(const SqList &L, int cur_e, int &pre_e) {
  int pos = locate_elem(L, cur_e);
  if (pos > 1) {
    pre_e = L.data[pos - 2];
    return true;
  }
  return false;
}

bool next_elem(const SqList &L, int cur_e, int &next_e) {
  int pos = locate_elem(L, cur_e);

  if (pos > 0 && pos < L.length) {
    next_e = L.data[pos];
    return true;
  }
  return false;
}

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

  cout << "初始化后：" << endl;
  cout << list_empty(L) << " " << int(list_length(L)) << endl;

  // 临时加入两个元素用于测试
  L.data[0] = 10;
  L.data[1] = 20;
  L.length = 2;

  int values[] = {10, 20, 30, 40, 50};

  cout << "加入两个元素后：" << endl;
  cout << list_empty(L) << " " << int(list_length(L)) << endl;

  int e1 = -1;
  cout << get_elem(L, 2, e1) << " " << e1 << endl;
  cout << get_elem(L, 3, e1) << " " << e1 << endl;

  clear_list(L);

  cout << "清空后：" << endl;
  cout << list_empty(L) << " " << int(list_length(L)) << endl;

  for (int i = 0; i < 5; i++) {
    L.data[i] = values[i];
  }
  L.length = 5;

  cout << locate_elem(L, 20) << endl;
  cout << locate_elem(L, 50) << endl;
  cout << locate_elem(L, 99) << endl;

  int e2;

  if (prior_elem(L, 30, e2)) {
    cout << "30的前驱：" << e2 << endl;
  } else {
    cout << "前驱不存在" << endl;
  }

  if (next_elem(L, 30, e2)) {
    cout << "30的后继：" << e2 << endl;
  } else {
    cout << "后继不存在" << endl;
  }

  list_traverse(L);

  int e = 99;

  if (set_elem(L, 2, e)) {
    cout << "修改成功！原值：" << e << endl;
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
  cout << "当前长度：" << list_length(L2) << endl;

  cout << "销毁后：" << endl;
  cout << (L.data == nullptr) << " " << L2.length << " " << L2.capacity << endl;

  return 0;
}