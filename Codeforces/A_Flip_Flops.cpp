#include <bits/stdc++.h>
using namespace std;

int get_max_clean(int N, string s) {
    int ans = 0;
    int i = 0;
    while (i < N) {
        if (s[i] == '0') {
            int j = i;
            while (j < N && s[j] == '0') j++;
            int len = j - i;
            // Only clean zeros that are strictly between two '1's
            if (i > 0 && j < N && s[i-1] == '1' && s[j] == '1') {
                ans += (len + 1) / 2;   // ceil(len/2)
            }
            i = j;
        } else {
            i++;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    string S;
    cin >> S;
    cout << get_max_clean(N, S) << endl;
    return 0;
}