#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  int a[1004];
  for (int i = 0; i < n; i++) {
    a[i] = i + 1;
  }

  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;

    int pos = 0;
    for (int j = 0; j < n; j++) {
      if (a[j] == x) {
        pos = j;
        break;
      }
    }

    if (y > 0) {
      for (int j = pos; j < pos + y; j++) {
        swap(a[j], a[j + 1]);
      }
    } else {
      for (int j = pos; j > pos + y; j--) {
        swap(a[j], a[j - 1]);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      cout << " ";
    }
    cout << a[i];
  }

  return 0;
}