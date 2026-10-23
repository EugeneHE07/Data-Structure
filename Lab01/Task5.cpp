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
      total += t;
    } else if (k == 1) {
      total += t; 
    } else if (k == 2) {
      total += t + r; 
    } else if (k == 3) {
    }
  }

  cout << total << endl;

  return 0;
}
