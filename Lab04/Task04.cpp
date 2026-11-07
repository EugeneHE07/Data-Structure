#include <bits/stdc++.h>
using namespace std;

const int ROWS = 20;
const int COLS = 5;

int remain[ROWS];

void AllocateSeats(int p) {
    vector<int> ans;

    for (int i = 0; i < ROWS; i++) {
        if(remain[i] >= p) {
            int start = i * COLS+COLS-remain[i] + 1;

            for (int j = 0; j < p; j++) {
                ans.push_back(start + j);
            }
            remain[i] -= p;
            break;
        }
    }

    if(ans.empty()) {
        for (int i = 0; i < ROWS; i ++ && p > 0) {
            int take = min(p, remain[i]);
            int start = i * COLS + COLS -remain[i] + 1;
            for (int j = 0; j < take; j++) {
                ans.push_back(start + j);
            }
            remain[i] -= take;
            p-= take;
        }
    }

    for (int i = 0; i < (int)ans.size(); i++) {
        if( i > 0 ){
            cout << " ";
        }
        cout << ans[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> orders(n);

    for (int i = 0; i < n; i++) {
        cin >> orders[i];
    }

    fill(remain, remain + ROWS, COLS);

    for (int p : orders) {
        AllocateSeats(p);
    }

    return 0;
}