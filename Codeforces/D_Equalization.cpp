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
vector<ll>powertwo;
vector<vector<vector<ll>>>dp1(61,vector<vector<ll>>(61,vector<ll>(61,-1)));
ll find(ll rem1,ll rem2,ll k,vector<vector<vector<ll>>>&dp){
    if(rem1 == 0 && rem2 == 0) return 0;

    if(k > 60) return LLONG_MAX;


    if(dp[rem1][rem2][k] != -1) return dp[rem1][rem2][k];

    ll ans = LLONG_MAX;

    ll val = LLONG_MAX;
    if(rem1 - k >= 0){
        val = find(rem1 - k,rem2,k + 1,dp);

        if(val != LLONG_MAX) ans = powertwo[k] + val;
    }
    if(rem2 - k >= 0){
        val = find(rem1,rem2 - k,k + 1,dp);
        if(val != LLONG_MAX){
            ll add = powertwo[k] + val;
            ans = min(ans,add);
        }
    }
    ans = min(ans,find(rem1,rem2,k + 1,dp));

    return dp[rem1][rem2][k] = ans;
}

ll solve(){
    ll x,y;cin >> x >> y;
    if(x == y) return 0;
    vector<ll>temp1,temp2;
    ll a = x,b = y;
    while(a > 0){
        temp1.push_back(a % 2);
        a /= 2;
    }
    while(b > 0){
        temp2.push_back(b % 2);
        b /= 2;
    }
    if(temp1.size()) reverse(all(temp1));
    if(temp2.size()) reverse(all(temp2));
    ll cnt = 0;
    for(ll i = 0 ;i < min(temp1.size(),temp2.size());i++){
        if(temp1[i] != temp2[i]) break;
        else cnt++;
    }
    ll rem1 = temp1.size() - cnt;
    ll rem2 = temp2.size() - cnt;

    //cout << rem1 << " " << rem2 << endl;
    if(rem1 == 1 && rem2 == 1){
        if(temp1.size() == 2 && temp2.size() == 2) return 12;
        if(temp1.size() == 3 && temp2.size() == 2) return 12;
        if(temp1.size() == 2 && temp2.size() == 3) return 12;
        return 14;
    }
    if(rem2 == 2 && rem1 == 2){
        return 14;
    } 
    
    
    
    ll ans = LLONG_MAX;
    for (ll i = rem1; i <= temp1.size(); i++) {
        for (ll j = rem2; j <= temp2.size() ; j++) {
            if ((x >> i) == (y >> j)) {
                ans = min(ans, dp1[i][j][1]);
            }
        }
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    powertwo.resize(65);
    powertwo[0] = 1;
    for(ll i = 1 ;i <= 61;i++){
        powertwo[i] = powertwo[i - 1] * 2;
    }
    for (ll i = 0; i <= 60; i++) {
        for (ll j = 0; j <= 60; j++) {
            find(i, j, 1, dp1);
        }
    }
    ll t; cin >> t;
    while(t--){
        ll ans = solve();
        cout << ans << endl;
    }
    return 0;
}