#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define loop(i,n) for(ll i=0;i<n;i++)

void dfs(ll node,ll par,vector<vector<ll>>&graph,vector<ll>&dis,vector<ll>&parent){
    parent[node] = par;
    for(auto &child:graph[node]) if(child != par){
        dis[child] = 1 + dis[node];
        dfs(child,node,graph,dis,parent);
    }
}

void solve(){
    ll n;cin >> n;
    vector<vector<ll>>graph(n + 1);
    vector<ll>degree(n + 1);
    loop(i,n - 1){
        ll u,v;cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
    ll root = 1;
    for(ll i = 1 ;i <= n;i++) if(degree[i] == 1){ root = i; break; }
    vector<ll>dis(n + 1,0);
    vector<ll>parent(n + 1,-1);
    dfs(root,-1,graph,dis,parent);
    ll cnt = 0;
    set<ll> st1;
    for(ll i = 1 ; i <= n;i++){
        if(degree[i] == 1){
            cnt++;
            for(auto v: graph[i]) if(degree[v] > 1) st1.insert(v);
        }
    }
    ll mini = 1;
    for(ll i = 1 ;i <= n;i++) if(degree[i] == 1) if(dis[i] & 1) mini = 3;
    ll maxi = (n - 1) - cnt + (ll)st1.size();
    cout << mini << " " << maxi << "\n";
}

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    solve();
    return 0;
}
