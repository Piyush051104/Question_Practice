#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007LL;
const ll INF = (ll)4e18;
const int LIM = 60;

ll lenA[LIM + 1], blockProd[LIM + 1], fullProd[LIM + 1];

ll prefT(ll r) {
    if (r <= 0) return 1;
    int m = 63 - __builtin_clzll((unsigned long long)(r + 1));
    ll used = (1LL << m) - 1;
    ll res = fullProd[m];
    ll rem = r - used;
    if (rem == 0) return res;
    return res * ((m + 1LL) % MOD) % MOD * prefT(rem - 1) % MOD;
}

ll prefA(ll x, ll k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    if (x <= LIM && k >= lenA[x]) return blockProd[x];
    return (x % MOD) * prefT(k - 1) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    lenA[0] = 0;
    lenA[1] = 1;

    fullProd[0] = 1;
    blockProd[1] = 1;
    fullProd[1] = 1;

    for (int i = 2; i <= LIM; i++) {
        lenA[i] = min(INF, lenA[i - 1] * 2);
        blockProd[i] = (i % MOD) * fullProd[i - 1] % MOD;
        fullProd[i] = fullProd[i - 1] * blockProd[i] % MOD;
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> a(n);
        for (auto &x : a) cin >> x;
        sort(a.begin(), a.end());

        ll ans = 1;
        ll rem = k;

        for (ll x : a) {
            if (rem == 0) break;

            if (x <= LIM && rem >= lenA[x]) {
                ans = ans * blockProd[x] % MOD;
                rem -= lenA[x];
            } else {
                ans = ans * prefA(x, rem) % MOD;
                rem = 0;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}