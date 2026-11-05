#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  sort(a.begin(), a.end());

  int mid = a[n / 2];
  int smaller = 0, larger = 0;

  for (int i = 0; i < n; i++) {
    if (a[i] < mid)
      smaller++;
    else if (a[i] > mid)
      larger++;
  }

  if (smaller == larger)
    cout << mid << endl;
  else
    cout << -1 << endl;

  return 0;
}
