#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 60);
const ll MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, ll>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }

    vector<ll> dist(n + 1, INF), ways(n + 1, 0), mn(n + 1, INF), mx(n + 1, 0);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[1] = 0;
    ways[1] = 1;
    mn[1] = 0;
    mx[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (auto [v, c] : g[u]) {
            ll nd = d + c;

            if (nd < dist[v]) {
                dist[v] = nd;
                ways[v] = ways[u];
                mn[v] = mn[u] + 1;
                mx[v] = mx[u] + 1;
                pq.push({nd, v});
            } else if (nd == dist[v]) {
                ways[v] = (ways[v] + ways[u]) % MOD;
                mn[v] = min(mn[v], mn[u] + 1);
                mx[v] = max(mx[v], mx[u] + 1);
            }
        }
    }

    cout << dist[n] << ' ' << ways[n] << ' ' << mn[n] << ' ' << mx[n] << '\n';
    return 0;
}