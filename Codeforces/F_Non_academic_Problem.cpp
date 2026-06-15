#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<long long, long long> pll;
typedef priority_queue<ll> pq;
typedef priority_queue<ll, vector<ll>, greater<ll>> pqr;
#define all(a) (a).begin(), (a).end()
#define fixed(n) fixed << setprecision(n)
#define MOD 1000000007
#define loop(i,n) for(ll i=0;i<n;i++)
#define loop1(a,n) for(ll i=a;i<n;i++)
#define sum_vector(v) accumulate(v.begin(),v.end(),0LL)
#define min_value(v) *min_element(v.begin(),v.end())
#define max_value(v) *max_element(v.begin(),v.end())
ll powermod(ll x, ll y, ll p){ll res = 1;x = x % p;if (x == 0) return 0;while (y > 0){if (y & 1)res = (res*x) % p;y = y>>1;x = (x*x) % p;}return res;}
vector<vector<ll>>graph;
ll n,m;
vector<ll>tin;
vector<ll>low;
ll timer = 0;
vector<ll>vis1,vis2;
vector<ll>subtreesize;
ll ans = 0;
ll x = 0,y = 0;
void findbridges(ll node,ll par){
    vis1[node] = true;
    tin[node] = low[node] = timer;
    timer++;

    for(auto &child:graph[node]){
        if(child == par) continue;

        if(vis1[child]){
            low[node] = min(low[node],tin[child]);
        }
        else{
            findbridges(child,node);

            low[node] = min(low[node],low[child]);

            if(tin[node] < low[child]){

                ll downsize = subtreesize[child] + 1;
                ll upsize = n - downsize;
                
                if(downsize * upsize > ans){
                    ans = downsize * upsize;
                    x = upsize;
                    y = downsize;
                }
            }
        }
    }
}
void dfs(ll node, ll par){
    vis2[node] = true;
    for(auto &child: graph[node]){
        if(child == par || vis2[child]) continue;
        dfs(child, node);
        subtreesize[node] = 1 + subtreesize[node] + subtreesize[child];
    }
}
ll solve(){
    cin >> n >> m;
    graph.assign(n + 1,{});
    low.assign(n + 1,-1);
    tin.assign(n + 1,-1);
    vis1.assign(n + 1,false);
    vis2.assign(n + 1,false);
    subtreesize.assign(n + 1,0);
    timer = 0;
    ans = 0;
    x = 0;
    y = 0;
    loop(i,m){
        ll u,v;cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1,-1);
    findbridges(1,-1);
    
    if(ans == 0){
        return(n * (n - 1))/2;
    }
    ll val1 = (x * (x - 1))/2;
    ll val2 = (y * (y - 1))/2;
    return val1 + val2;

}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        ll ans = solve();
        cout << ans << endl;
    }
    return 0;
}