#include <bits/stdc++.h>
using namespace std;
int solve(int A){
    if (A <= 1) {
        return 0;
    }

    // dp[i] = minimum energy to reach exactly i lines
    vector<int> dp(A + 1, INT_MAX / 2);
    dp[1] = 0;

    for (int i = 2; i <= A; ++i) {
        for (int k = 1; k < i; ++k) {
            int d = i - k;

            for (int x = 1; x * x <= d; ++x) {
                if (d % x != 0) continue;
                int y = d / x;

                // Option 1: select block of size x
                if (x <= k) {
                    int selCost = (x == k ? 1 : x);
                    dp[i] = min(dp[i], dp[k] + selCost + y);
                }

                // Option 2: select block of size y
                if (y != x && y <= k) {
                    int selCost = (y == k ? 1 : y);
                    dp[i] = min(dp[i], dp[k] + selCost + x);
                }
            }
        }
    }

    return dp[A];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A;
    cin >> A;

    if (A <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    // dp[i] = minimum energy to reach exactly i lines
    vector<int> dp(A + 1, INT_MAX / 2);
    dp[1] = 0;

    for (int i = 2; i <= A; ++i) {
        for (int k = 1; k < i; ++k) {
            int d = i - k;

            for (int x = 1; x * x <= d; ++x) {
                if (d % x != 0) continue;
                int y = d / x;

                // Option 1: select block of size x
                if (x <= k) {
                    int selCost = (x == k ? 1 : x);
                    dp[i] = min(dp[i], dp[k] + selCost + y);
                }

                // Option 2: select block of size y
                if (y != x && y <= k) {
                    int selCost = (y == k ? 1 : y);
                    dp[i] = min(dp[i], dp[k] + selCost + x);
                }
            }
        }
    }

    cout << dp[A] << "\n";
    return 0;
}
