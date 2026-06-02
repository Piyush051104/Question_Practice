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
template<const int mod>
struct mint {
    int val;
    constexpr mint(long long x = 0) : val((x % mod + mod) % mod) {}
    explicit operator int() const { return val; }
    mint& operator+=(const mint &b) { val = (val + 1LL * b.val) % mod; return *this; }
    mint& operator-=(const mint &b) { val -= b.val; if (val < 0) val += mod; return *this; }
    mint& operator*=(const mint &b) { val = 1LL * val * b.val % mod; return *this; }
    mint& operator/=(const mint &b) { return *this *= b.inv(); }
    mint inv() const { return powermod(val, mod - 2, mod); }
    mint power(int b) const { mint a = *this, res(1); for (; b; a *= a, b /= 2) if (b & 1) res *= a; return res; }
    mint operator-() const { return val == 0 ? 0 : mod - val; }
    friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
    friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
    friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
    friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
    friend ostream& operator<<(ostream &os, const mint &a) { return os << a.val; }
};
using Mint = mint<MOD>;
class SegmentTree{
public:
    ll n;
    vector<ll>tree,lazy;
    SegmentTree(ll n){
        tree.resize(4*n);
        lazy.resize(4*n);
    }
    void build(ll node,ll l,ll r,vector<ll>&v){
        if(l == r){
            tree[node] = v[l];
            return;
        }
        ll mid = (l + r)/2;
        build(2*node,l,mid,v);
        build(2*node + 1,mid + 1,r,v);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }
    void push(ll node,ll l,ll r){
        if(lazy[node]){
            tree[node] += (r - l + 1) * lazy[node];
            if(l!=r){
                lazy[2*node] += lazy[node];
                lazy[2*node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void pointupdate(ll idx,ll val,ll l,ll r,ll node){
        push(node,l,r);
        if(idx < l || idx > r) return;
        if(l == r){
            tree[node] = val;
            return;
        }
        ll mid = (l + r)/2;
        pointupdate(idx,val,l,mid,2*node);
        pointupdate(idx,val,mid + 1,r,2*node + 1);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }
    void rangeupdate(ll node,ll lq,ll rq,ll l,ll r,ll val){
        push(node,l,r);
        if(lq > r  || l > rq) return ;
        if(l >= lq && r <= rq){
            lazy[node] += val;
            push(node,l,r);
            return;
        }
        ll mid = (l + r)/2;
        rangeupdate(2*node,lq,rq,l,mid,val);
        rangeupdate(2*node + 1,lq,rq,mid + 1,r,val);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }
    ll query(ll lq,ll rq,ll l ,ll r,ll node){
        push(node,l,r);
        if(lq > r  || l > rq) return 0;
        if(l >= lq && r <= rq) return tree[node];
        ll mid = (l + r)/2;
        return query(lq,rq,l,mid,2*node) + query(lq,rq,mid + 1,r,2*node + 1);
    }
};
void dijskrts(ll node,vector<ll>&dis,vector<vector<pair<ll,ll>>>&graph){
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>>pq;
    pq.push({0,node});
    dis[node] = 0;
    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();

        ll node = top.second;
        ll distance = top.first;
        if(dis[node] != distance) continue;
        for(auto &child:graph[node]){
            if(distance + child.second < dis[child.first]){
                dis[child.first] = distance + child.second;
                pq.push({distance + child.second,child.first});
            }
        }
    }
}
ll solve(){
    ll n,m,h;cin >> n >> m >> h;
    vector<ll>ishorse(n + 1,0);
    loop(i,h){
        ll a;cin >> a;
        ishorse[a] = 1;
    }
    vector<vector<pair<ll,ll>>>graph(2 * n + 1);
    loop(i,m){
        ll u,v,w;cin >> u >> v >> w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});

        graph[u + n].push_back({v + n,w/2});
        graph[v + n].push_back({u + n,w/2});
    }
    loop1(1,n + 1){
        if(ishorse[i] == 1){
            graph[i].push_back({i + n,0});
            graph[i + n].push_back({i,0});
        }
    }
    vector<ll>dis1(2 * n + 1,LLONG_MAX);
    vector<ll>dis2(2 * n + 1,LLONG_MAX);
    dijskrts(1,dis1,graph);
    if(min(dis1[n],dis1[2*n]) == LLONG_MAX) return -1;
    dijskrts(n,dis2,graph);
    ll ans = LLONG_MAX;
    for(ll i = 1 ; i <= n;i++){
        ll d1 = min(dis1[i],dis1[i + n]);
        ll d2 = min(dis2[i],dis2[i + n]);
        ans = min(ans,max(d1,d2));
    }
    return ans;


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