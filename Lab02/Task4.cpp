#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n < 3) {
        // 少于 3 个数时，不可能存在折点
        for (int i = 0; i < n; ++i) {
            int value;
            cin >> value;
        }

        cout << 0 << endl;
        return 0;
    }

    int previous, current;
    cin >> previous >> current;

    int turningPoints = 0;

    for (int i = 2; i < n; ++i) {
        int next;
        cin >> next;

        if ((current > previous && current > next) ||
            (current < previous && current < next)) {
            ++turningPoints;
        }

        previous = current;
        current = next;
    }

    cout << turningPoints << endl;
    return 0;
}