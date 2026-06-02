#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void dfs(int u, int p,vector<vector<int>>& g,vector<ll>& L,vector<ll>& R,vector<array<ll,2>>& dp) {
    dp[u][0] = dp[u][1] = 0;
    for (int v : g[u]) if (v != p) {
        dfs(v, u, g, L, R, dp);
        ll takeL = max(dp[v][0] + llabs(L[u] - L[v]),dp[v][1] + llabs(L[u] - R[v]));
        ll takeR = max(dp[v][0] + llabs(R[u] - L[v]),dp[v][1] + llabs(R[u] - R[v]));
        dp[u][0] += takeL;
        dp[u][1] += takeR;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; 
    if(!(cin >> t)) return 0;
    while(t--){
        int n; cin >> n;
        vector<ll> L(n+1), R(n+1);
        for (int i = 1; i <= n; ++i) cin >> L[i] >> R[i];
        vector<vector<int>> g(n+1);
        for (int i = 0; i < n-1; ++i){
            int u,v; cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<array<ll,2>> dp(n+1);
        dfs(1, 0, g, L, R, dp);
        cout << max(dp[1][0], dp[1][1]) << '\n';
    }
    return 0;
}
