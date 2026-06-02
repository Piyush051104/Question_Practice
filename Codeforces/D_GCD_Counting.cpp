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
const int MAXN = 200000 + 5;
const int MAXA = 200000 + 5;

ll n;
vector<ll> adj[MAXN];

ll spf[MAXA];                 
vector<ll> prime[MAXA]; 

bool present[MAXN];            
bool used[MAXN];              
ll dist[MAXN];      
void build_spf(ll limit) {
    for (ll i = 2; i <= limit; ++i) spf[i] = 0;
    for (ll i = 2; i <= limit; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            if (1LL * i * i <= limit) {
                for (ll j = i * i; j <= limit; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }
    }
}

ll solve(){
    ll n;cin >> n;
    vector<ll>v(n + 1);
    loop1(1,n + 1) cin >> v[i];
    vector<vector<ll>>graph(n + 1);
    loop(i,n - 1){
        ll u,v;cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    ll maxi = 0;
    for (int i = 1; i <= n; ++i) maxi = max(maxi, v[i]);

   
    build_spf(maxi);
    set<ll>st;
    for(ll i = 1; i <= n; ++i) {
        ll x = v[i];
        ll last = -1;
        while (x > 1) {
            ll p = spf[x];
            if (p != last) {
                st.insert(p);
                prime[p].push_back(i);
                last = p;
            }
            while (x % p == 0) x /= p;
        }
    }
    ll ans = 0;
    
    for(auto &i:st){
        auto &node = prime[i];
        if(node.size() == 0) continue;
        for(auto &j :node){
            present[j] = true;
            used[j] = false;
        }

        for(auto &j:node){
            if(used[j]) continue;

            vector<ll> comp;
            queue<ll> q;
            used[j] = true;
            q.push(j);
            comp.push_back(j);

            while (!q.empty()) {
                ll k = q.front(); q.pop();
                for (ll u : graph[k]) {
                    if (present[u] && !used[u]) {
                        used[u] = true;
                        q.push(u);
                        comp.push_back(u);
                    }
                }
            }
            for(auto &k:comp) dist[k] = -1;
            dist[comp[0]] = 0;
            ll a = comp[0];
            queue<ll>qu;
            qu.push(a);
            while(!qu.empty()){
                ll no = qu.front();
                qu.pop();
                if(dist[no] > dist[a]) a = no;
                for(auto &child:graph[no]){
                    if(present[child] && dist[child] == -1){
                        qu.push(child);
                        dist[child] = dist[no] + 1;
                    }
                }
            }
            for(auto &k:comp) dist[k] = -1;
            dist[a] = 0;
            qu.push(a);
            ll nod = a;
            while(!qu.empty()){
                int no = qu.front(); qu.pop();
                if (dist[no] > dist[nod]) nod = no;
                for (auto &child : graph[no]) {
                    if (present[child] && dist[child] == -1) {
                        dist[child] = dist[no] + 1;
                        qu.push(child);
                    }
                }
            }
            ans = max(ans, dist[nod] + 1);
        }
        for(auto &j:node){
            present[j] = false;
        }
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; t = 1;
    while(t--){
        ll ans = solve();
        cout << ans << endl;
    }
    return 0;
}