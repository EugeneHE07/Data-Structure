#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct TimeInterval {
    int start;
    int end;
};

int main() {
    int n;
    cin >> n;

    vector<TimeInterval> h(n);
    vector<TimeInterval> w(n);

    for (TimeInterval& interval : h) {
        cin >> interval.start >> interval.end;
    }

    for (TimeInterval& interval : w) {
        cin >> interval.start >> interval.end;
    }

    long long chatTime = 0;
    int i = 0;
    int j = 0;

    while (i < n && j < n) {
        int overlapStart = max(h[i].start, w[j].start);
        int overlapEnd = min(h[i].end, w[j].end);

        if (overlapStart < overlapEnd) {
            chatTime += overlapEnd - overlapStart;
        }

        if (h[i].end < w[j].end) {
            ++i;
        } else {
            ++j;
        }
    }

    cout << chatTime << endl;
    return 0;
}