#include <iostream>
using namespace std;

int main() {
  int r, y, g;
  cin >> r >> y >> g;

  int n;
  cin >> n;

  long long total = 0;

  for (int i = 0; i < n; i++) {
    int k, t;
    cin >> k >> t;

    if (k == 0) {
      total += t; // 经过道路
    } else if (k == 1) {
      total += t; // 等待红灯
    } else if (k == 2) {
      total += t + r; // 等待黄灯及红灯
    } else if (k == 3) {
      // 绿灯直接通过，无需等待
    }
  }

  cout << total << endl;

  return 0;
}
