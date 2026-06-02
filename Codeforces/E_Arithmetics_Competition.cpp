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
void solve(){
    ll n,m,q;cin >> n >> m >> q;
    vector<ll>v1(n + 1);
    vector<ll>v2(m + 1);
    v1[0] = LLONG_MAX;
    v2[0] = LLONG_MAX;
    vector<pair<ll,ll>>temp;
    for(ll i = 1 ;i <= n;i++){
        cin >> v1[i];
        temp.push_back({v1[i],1});
    }
    for(ll i = 1 ;i <= m;i++){
        cin >> v2[i];
        temp.push_back({v2[i],0});
    }
    temp.push_back({LLONG_MAX,0});
    sort(all(v1));
    reverse(all(v1));
    sort(all(v2));
    reverse(all(v2));
    sort(all(temp));
    reverse(all(temp));
    vector<ll>pref1(n + 1,0),pref2(m + 1,0);
    vector<pair<ll,ll>>pref(n + m + 1,{0,0});
    for(ll i = 1 ;i <= n + m;i++){
        pref[i].first = temp[i].first + pref[i - 1].first;
        pref[i].second = temp[i].second + pref[i - 1].second;
    }
    for(ll i = 1 ;i <= n;i++){
        pref1[i] = v1[i] + pref1[i - 1];
    }
    for(ll i = 1; i<= m;i++){
        pref2[i] = v2[i] + pref2[i  - 1];
    }
    for(ll i = 0 ;i < q;i++){
        ll a,b,c; cin >> a >> b >> c;
        ll sum = pref[c].first;
        ll a1 = pref[c].second;
        ll b1 = c - a1;
        if(a1 <= a && b1 <= b){
            cout << sum << endl;
            continue;
        }
        if(a1 > a){
            ll extra =  a1 - a;
            ll need = c - a;
            cout << pref2[need] + pref1[a] << endl;
            continue;
        }
        if(b1 > b){
            ll extra =  b1 - b;
            ll need = c - b;
            cout << pref2[b] + pref1[need] << endl;
            continue;
        }
    }
    
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}