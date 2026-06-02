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
ll findans1(ll i,ll j,vector<vector<ll>>&dp,vector<vector<ll>>&v){
    if(i == 0 && j == 0) return dp[i][j] = v[0][0];

    if(dp[i][j] != -1) return dp[i][j];

    ll ans1 = 0, ans2 = 0;

    if( i - 1 >= 0){
        ans1 = v[i][j] + findans1(i - 1,j,dp,v);
    }
    if(j - 1 >= 0){
        ans2 = v[i][j] + findans1(i,j - 1,dp,v);
    }
    return dp[i][j] = max(ans1,ans2);
}
ll findans2(ll i,ll j,vector<vector<ll>>&dp,vector<vector<ll>>&v){
    if(i == v.size() - 1 && j == v[0].size() - 1 ) return dp[i][j] = v[v.size() - 1][v[0].size() - 1];

    if(dp[i][j] != -1) return dp[i][j];

    ll ans1 = 0, ans2 = 0;

    if( i + 1 < v.size()){
        ans1 = v[i][j] + findans2(i + 1,j,dp,v);
    }
    if(j + 1 < v[0].size()){
        ans2 = v[i][j] + findans2(i,j + 1,dp,v);
    }
    return dp[i][j] = max(ans1,ans2);
}
ll findans3(ll i,ll j,vector<vector<ll>>&dp,vector<vector<ll>>&v){
    if(i == v.size() - 1 && j == 0) return dp[i][j] = v[v.size() - 1][0];

    if(dp[i][j] != -1) return dp[i][j];

    ll ans1 = 0, ans2 = 0;

    if( i + 1 < v.size()){
        ans1 = v[i][j] + findans3(i + 1,j,dp,v);
    }
    if(j - 1 >= 0){
        ans2 = v[i][j] + findans3(i,j - 1,dp,v);
    }
    return dp[i][j] = max(ans1,ans2);
}
ll findans4(ll i,ll j,vector<vector<ll>>&dp,vector<vector<ll>>&v){
    if(i == 0 && j == v[0].size() - 1) return dp[i][j] = v[0][v[0].size() - 1];

    if(dp[i][j] != -1) return dp[i][j];

    ll ans1 = 0, ans2 = 0;

    if( i - 1 >= 0){
        ans1 = v[i][j] + findans4(i - 1,j,dp,v);
    }
    if(j + 1 < v[0].size()){
        ans2 = v[i][j] + findans4(i,j + 1,dp,v);
    }
    return dp[i][j] = max(ans1,ans2);
}
ll solve(){
    ll n,m;cin >> n >> m;
    vector<vector<ll>>v(n,vector<ll>(m));
    loop(i,n){
        loop(j,m) cin >> v[i][j];
    }
    vector<vector<ll>>dp1(n,vector<ll>(m,-1));
    vector<vector<ll>>dp2(n,vector<ll>(m,-1));
    vector<vector<ll>>dp3(n,vector<ll>(m,-1));
    vector<vector<ll>>dp4(n,vector<ll>(m,-1));
    findans1(n - 1,m - 1,dp1,v);
    findans2(0,0,dp2,v);
    findans3(0, m - 1,dp3,v);
    findans4(n - 1,0,dp4,v);

    ll ans = 0;
    for(ll i = 1 ;i < n - 1;i++){
        for(ll j = 1 ;j < m - 1;j++){
            ll val1 = dp3[i][j - 1] + dp4[i][j + 1] + dp1[i - 1][j] + dp2[i + 1][j];
            ll val2 = dp1[i][j - 1] + dp2[i][j + 1] + dp3[i + 1][j] +  dp4[i - 1][j];
            ans = max({ans,val1,val2});
        }
    }
    return ans;

}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
        ll ans = solve();
        cout << ans << endl;
    
}