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
void dfs(ll node,ll parent,vector<vector<ll>>&graph,ll &cnt,vector<ll>&par,vector<ll>&degree){
    bool ischild = true;
    for(auto child:graph[node]){
        if(child != parent){
            degree[node]++;
            par[child] = node;
            ischild = false;
            dfs(child,node,graph,cnt,par,degree);
        }
    }
    if(ischild) cnt++;
}
ll solve(){
    ll n;cin >> n;
    vector<vector<ll>>graph(n + 1);
    loop(i,n - 1){
        ll u,v;cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    if(n < 3) return powermod(2,n,MOD);
    ll cnt = 0;
    vector<ll>par(n + 1,0);
    vector<ll>degree(n + 1,0);
    vector<ll>depth(n + 1,0);
    ll de = 0;
    dfs(1,0,graph,cnt,par,degree);
    if(cnt > 2) return 0;
    if(cnt == 1){
         ll ans = powermod(2, n, MOD);
         return ans;
    }
    else{
        ll cnt1 = 0,cnt2 = 0;
        ll n1 = -1 , n2 = -1;
        ll node = -1;
        for(ll i = 2 ;i <= n;i++){
            if(degree[i] == 0 ){
                if(n1 == -1) n1 = i;
                else n2 = i;
            }
        }
        
        queue<ll>dq;
        ll height = 0;
  
        dq.push(1);
        depth[1] = 0;
        vector<ll>visited(n + 1,false);
        visited[1] = true;
        while(!dq.empty()){
            ll no = dq.front();
            dq.pop();
            for(auto child:graph[no]){
                if(visited[child] == false){
                    visited[child] = true;
                    dq.push(child);
                    depth[child] = depth[no] + 1;
                }
            }   
        }
        
        vector<char> seen(n + 1, 0);
        ll cur = n1;
        while(cur != 0){
            seen[cur] = 1;
            cur = par[cur];
        }
        cur = n2;
        while(cur != 0){
            if(seen[cur]){
                node = cur;
                break;
            }
            cur = par[cur];
        }
        if(node == -1) node = 1;

        
        ll dx = depth[n1], dy = depth[n2], dv = depth[node];
        if(dx > dy) swap(dx, dy);
        if(dx == dy){
            
            ll ans = powermod(2, dv, MOD);
            ans = (ans * 2) % MOD;
            return (ans * 2) % MOD;
        } else {
            ll diff = dy - dx;
            ll term = (powermod(2, diff, MOD) + powermod(2, diff - 1, MOD)) % MOD;
            ll ans = (powermod(2, dv, MOD) * term) % MOD;
            return (ans * 2) % MOD;
        }
        
    }

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
