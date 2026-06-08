#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        ll sum = 0, sq = 0;
        for (int i = 0; i < n; i++) {
            ll x;
            cin >> x;
            x %= MOD;
            sum = (sum + x) % MOD;
            sq = (sq + x * x) % MOD;
        }

        ll pair_sum = (sum * sum % MOD - sq + MOD) % MOD;
        pair_sum = pair_sum * modpow(2, MOD - 2) % MOD;

        ll total_pairs = 1LL * n * (n - 1) / 2;
        ll ans = pair_sum * modpow(total_pairs % MOD, MOD - 2) % MOD;

        cout << ans << '\n';
    }
}