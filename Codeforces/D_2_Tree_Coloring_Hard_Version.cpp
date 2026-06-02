#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define loop(i,n) for(ll i=0;i<n;i++)
void dfs(ll node,ll par,vector<vector<ll>>&graph,vector<ll>&depth,vector<ll>&parent){
    parent[node] = par;
    for(auto &child:graph[node]){
        if(child != par){
            depth[child] = depth[node] + 1;
            dfs(child,node,graph,depth,parent);
        }
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
    vector<ll>depth(n + 1);
    vector<ll>parent(n + 1);
    depth[1] = 0;
    dfs(1,-1,graph,depth,parent);
    ll maxdep = 0;
    for(ll i = 1 ;i <= n;i++) maxdep = max(maxdep,depth[i]);
    vector<vector<ll>>temp(maxdep + 1);
    for(ll i = 1 ;i <= n;i++) temp[depth[i]].push_back(i);
    ll val1 = 0;
    for(ll i = 0;i<=maxdep;i++) val1 = max(val1, (ll)temp[i].size());
    ll val2 = 0;
    for(ll i = 1 ;i <= n;i++){
        if(i != 1) val2 = max(val2,degree[i] - 1);
        else val2 = max(val2,degree[i]);
    }
    ll size = max(val1,val2 + 1);
    vector<vector<ll>>ans(size);
    unordered_map<ll,ll> mp1;
    mp1[-1] = -1;
    for(ll i = 0 ;i <= maxdep;i++){
        vector<pair<ll,ll>> vec;
        for(ll x: temp[i]) vec.push_back({ mp1.count(parent[x]) ? mp1[parent[x]] : -1, x });
        sort(vec.begin(), vec.end());
        ll m = vec.size();
        unordered_set<ll> forb;
        for(ll idx = 0; idx < m; ++idx){
            ll pc = vec[idx].first;
            if(pc != -1){
                ll val = ((pc - idx) % size + size) % size;
                forb.insert(val);
            }
        }
        ll delta = 0;
        for(ll d = 0; d < size; ++d){
            if(forb.find(d) == forb.end()){ delta = d; break; }
        }
        for(ll idx = 0; idx < m; ++idx){
            ll assigned = (idx + delta) % size;
            ans[assigned].push_back(vec[idx].second);
            mp1[vec[idx].second] = assigned;
        }
    }
    cout << size << '\n';
    for(ll i = 0 ; i < (ll)ans.size(); i++){
        cout << ans[i].size() << " ";
        for(ll j = 0 ; j < (ll)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << '\n';
    }
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
