#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solve(){
    ll n; cin >> n;
    vector<int> v(n + 1);
    for (ll i = 1; i <= n; ++i) cin >> v[i];

    vector<vector<int>> pos(201);
    for (int i = 1; i <= n; ++i) pos[v[i]].push_back(i);

    ll ans = 1;
    for (int i = 1; i <= 200; ++i) ans = max(ans, (ll)pos[i].size());

    for (int i = 1; i <= 200; ++i) {
        int m = pos[i].size();
        for (int k = 1; k * 2 <= m; ++k) {
            int L = pos[i][k - 1] + 1;
            int R = pos[i][m - k] - 1;
            if (L > R) continue;
            int mx = 0;
            for (int j = 1; j <= 200; ++j) {
                if (pos[j].empty()) continue;
                int cnt = upper_bound(pos[j].begin(), pos[j].end(), R) -
                          lower_bound(pos[j].begin(), pos[j].end(), L);
                mx = max(mx, cnt);
            }
            ans = max(ans, (ll)mx + 2LL * k);
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;
    while(t--) cout << solve() << '\n';
    return 0;
}
