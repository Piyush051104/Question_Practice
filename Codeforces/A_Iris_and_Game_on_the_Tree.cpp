#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

using ll = long long;

bool isPrime(ll n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int getAns(int N, vector<int>& A) {
    vector<unordered_map<ll, int>> dp(N + 1);
    vector<vector<ll>> states(N + 1);

    dp[0][0] = 1;
    states[0].push_back(0);

    int maxLen = 0;

    for (int x : A) {
        for (int l = maxLen; l >= 0; --l) {
            ll add = 1LL * x * (l + 1);

            for (ll w : states[l]) {
                ll nw = w + add;
                int val = dp[l][w];

                auto it = dp[l + 1].find(nw);
                if (it == dp[l + 1].end()) {
                    dp[l + 1][nw] = val;
                    states[l + 1].push_back(nw);
                } else {
                    it->second += val;
                    if (it->second >= MOD) it->second -= MOD;
                }
            }
        }
        if (maxLen < N) ++maxLen;
    }

    long long ans = 0;
    for (int l = 1; l <= N; ++l) {
        for (ll w : states[l]) {
            if (isPrime(w)) {
                ans += dp[l][w];
                if (ans >= MOD) ans %= MOD;
            }
        }
    }

    return (int)(ans % MOD);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    cout << getAns(N, A) << '\n';
    return 0;
}