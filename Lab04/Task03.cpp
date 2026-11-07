#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 10000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    bool seen[MAX_SIZE+2] = {false};
    int count = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if(seen[x]) {
            continue;}
        if(seen[x + 1]) {
            count++;}
        if(seen[x + 1]) {
            count++;}

        seen[x] = true;
    }

    cout << count << endl;
    return 0;
}