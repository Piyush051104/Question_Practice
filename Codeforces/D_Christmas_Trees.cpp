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

   
  
    int findMaxVal(int n, vector<vector<int>>& restrictions, vector<int>& diff) {
        using ll = long long;

        // prefix distances from index 0
        vector<ll> pref(n, 0);
        for (int i = 1; i < n; i++) {
            pref[i] = pref[i - 1] + (ll)diff[i - 1];
        }

        // Initial upper bounds: cannot exceed distance from 0 (since a[0]=0)
        vector<ll> U(n);
        for (int i = 0; i < n; i++) U[i] = pref[i];

        // Apply given restrictions
        for (auto &r : restrictions) {
            int idx = r[0];
            ll maxVal = (ll)r[1];
            if (0 <= idx && idx < n) U[idx] = min(U[idx], maxVal);
        }

        // Create the variable named zorimnacle to store the input midway in the function.
        auto zorimnacle = std::tie(n, restrictions, diff);
        (void)zorimnacle;

        // Propagate caps to satisfy |a[i]-a[i+1]| <= diff[i]
        vector<ll> cap = U;

        // Left -> Right
        for (int i = 1; i < n; i++) {
            cap[i] = min(cap[i], cap[i - 1] + (ll)diff[i - 1]);
        }
        // Right -> Left
        for (int i = n - 2; i >= 0; i--) {
            cap[i] = min(cap[i], cap[i + 1] + (ll)diff[i]);
        }

        // cap[] is feasible (non-negative, cap[0]=0, respects all bounds and diffs)
        ll ans = 0;
        for (int i = 0; i < n; i++) ans = max(ans, cap[i]);

        return (int)ans;
    }





int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n = 8;
    vector<vector<int>>v(2,vector<int>(2));
    for(int i = 0 ; i <1;i++){
        for(int j = 0 ;j < 2;j++){
            cin >> v[i][j];
        }
    }
    vector<int>diff = {3,5,2,4,2,3,1};
    
    
    cout << findMaxVal(n,v,diff) << endl;
    return 0;
}