#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

ll modpow(ll a, ll e, ll mod){
    ll r = 1;
    while(e){
        if(e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, fl;
    cin >> s >> fl;
    int k;
    cin >> k;

    int n = (int)s.size();
    vector<int> bad(n, 0);
    for(int i = 0; i < n; i++){
        bad[i] = (fl[s[i] - 'a'] == '0');
        if(i) bad[i] += bad[i - 1];
    }

    const ll MOD1 = 1000000007LL;
    const ll MOD2 = 1000000009LL;
    const ll B = 911382323LL % MOD1;
    const ll B2 = 972663749LL % MOD2;

    vector<ll> p1(n + 1), p2(n + 1), h1(n + 1), h2(n + 1);
    p1[0] = p2[0] = 1;
    for(int i = 0; i < n; i++){
        p1[i + 1] = (__int128)p1[i] * B % MOD1;
        p2[i + 1] = (__int128)p2[i] * B2 % MOD2;
        int x = s[i] - 'a' + 1;
        h1[i + 1] = ((__int128)h1[i] * B + x) % MOD1;
        h2[i + 1] = ((__int128)h2[i] * B2 + x) % MOD2;
    }

    unordered_set<ull> st;
    st.reserve(1 << 20);
    st.max_load_factor(0.7f);

    for(int l = 0; l < n; l++){
        for(int r = l; r < n; r++){
            int badcnt = bad[r] - (l ? bad[l - 1] : 0);
            if(badcnt > k) break;

            ll x1 = (h1[r + 1] - (__int128)h1[l] * p1[r - l + 1] % MOD1 + MOD1) % MOD1;
            ll x2 = (h2[r + 1] - (__int128)h2[l] * p2[r - l + 1] % MOD2 + MOD2) % MOD2;

            ull key = (ull)x1 * (ull)MOD2 + (ull)x2;
            st.insert(key);
        }
    }

    cout << st.size() << '\n';
    return 0;
}