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
class DSU{
    public:
    vector<ll>parent,size;

    DSU(ll n){
        parent.resize(n + 1);
        size.resize(n + 1);
        for(ll i = 1 ;i <= n;i++){
            parent[i] = i;
            size[i] = 1;
        }
    }

    ll findpar(ll node){
        if(node == parent[node]) return node;
        else return parent[node] = findpar(parent[node]);
    }

    void unionbysize(ll u,ll v){
        ll up = findpar(u);
        ll vp = findpar(v);

        if(up == vp) return;

        else{
            if(size[up] > size[vp]){
                size[up] += size[vp];

                parent[vp] = up;
            }
            else{
                size[vp] += size[up];

                parent[up] = vp;
            }
        }
    }
};
ll solve(){
    ll n,m;cin >> n >> m;
    vector<vector<pair<ll,ll>>>v(11);
    vector<vector<pair<ll,ll>>>v1(11);
    loop(i,m){
        ll st,diff,k;cin >> st >> diff >> k;
        ll end = st + diff * k;
        if(st & 1) v[diff].push_back({st,min(end,n)});
        else v1[diff].push_back({st,min(end,n)});
    }

    for(ll i = 1 ;i <= 10;i++){
        sort(v[i].begin(),v[i].end(),[](pair<ll,ll>&p1,pair<ll,ll>&p2){
            if(p1.first != p2.first) return p1.first < p2.first;
            else return p1.second < p2.second;
        });
    }
    for(ll i = 1 ;i <= 10;i++){
        sort(v1[i].begin(),v1[i].end(),[](pair<ll,ll>&p1,pair<ll,ll>&p2){
            if(p1.first != p2.first) return p1.first < p2.first;
            else return p1.second < p2.second;
        });
    }

    DSU dsu(n);
    for(ll i = 1 ;i <= 10;i++){
        ll st = 0,end = 0;
        for(ll j = 0 ;j < v[i].size();j++){
            
           
            if(v[i][j].first > end){
                for(ll k = v[i][j].first ; k <= v[i][j].second ;k += i){
                    dsu.unionbysize(v[i][j].first ,k);
                }
                st = v[i][j].first;
                end = v[i][j].second;
            }
            else {
                for(ll k = end ; k <= v[i][j].second ;k += i){
                    dsu.unionbysize(end , k);
                }
                st = end;
                end = v[i][j].second;
            }
        }
    }

    for(ll i = 1 ;i <= 10;i++){
        ll st = 0,end = 0;
        for(ll j = 0 ;j < v1[i].size();j++){
            
           
            if(v1[i][j].first > end){
                for(ll k = v1[i][j].first ; k <= v1[i][j].second ;k += i){
                    dsu.unionbysize(v1[i][j].first ,k);
                }
                st = v1[i][j].first;
                end = v1[i][j].second;
            }
            else {
                for(ll k = end ; k <= v1[i][j].second ;k += i){
                    dsu.unionbysize(end , k);
                }
                st = end;
                end = v1[i][j].second;
            }
        }
    }
    ll cnt = 0;
    for(ll i = 1 ;i <= n;i++){
        if(dsu.findpar(i) == i){
            //cout << i << " ";
            cnt++;
        }
    }
    return cnt;

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