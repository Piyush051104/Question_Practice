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
ll findans(ll i,ll j,string &s,vector<string>&v,vector<vector<ll>>&dp){
    if(i >= s.length()) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    if(i + v[j].length() > s.length()) return LLONG_MAX;
    for(ll k = 0 ; k < v[j].length();k++){
        if(v[j][k] != s[i + k]) return LLONG_MAX;
    }
    ll ans = LLONG_MAX;
    for(ll k = 0 ; k < v[j].length();k++){
        for(ll l = 0 ; l < v.size();l++){
            ll val = findans(i + k + 1,l,s,v,dp);
            if(val != LLONG_MAX) val++;
            ans = min(ans,val);
        }
    }
    return dp[i][j] = ans; 
}
ll solve(){
    string s;cin >> s;
    ll n;cin >> n;
    vector<string>v(n);
    loop(i,n) cin >> v[i];
    ll len = s.length();
    vector<vector<ll>>dp(len + 1,vector<ll>(n + 1,-1));
    ll ans = LLONG_MAX;
    for(ll i = 0 ; i < n;i++){
        ans = min(ans,findans(0,i,s,v,dp));
    }
    if(ans == LLONG_MAX){
        cout << -1 << '\n';
        return -1;
    }
    for(int i = 0 ;i <= len ;i++){
        for(int j = 0 ;j <= n;j++){
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    int start_j = -1;
    for(ll j = 0; j < n; ++j){
        if(dp[0][j] == -1) dp[0][j] = findans(0, j, s, v, dp);
        if(dp[0][j] == ans){
            start_j = (int)j;
            break;
        }
    }
    if(start_j == -1){
        for(ll j = 0; j < n; ++j){
            if(findans(0, j, s, v, dp) == ans){ start_j = (int)j; break; }
        }
    }
    vector<pair<int,int>> result;
    int i = 0;
    int curj = start_j;
    while(i < (int)len){
        result.emplace_back(curj + 1, i + 1);
        
        bool moved = false;
        for(int k = 0; k < (int)v[curj].length() && !moved; ++k){
            int nexti = i + k + 1;
            for(int l = 0; l < (int)v.size() && !moved; ++l){
                ll nextval;
                if(nexti >= (int)len) nextval = 0;
                else {
                    if(dp[nexti][l] == -1) dp[nexti][l] = findans(nexti, l, s, v, dp);
                    nextval = dp[nexti][l];
                }
                if(nextval != LLONG_MAX && dp[i][curj] == nextval + 1){
                    i = nexti;
                    curj = l;
                    moved = true;
                }
            }
        }
        if(!moved) break;
    }
    cout << result.size() << '\n';
    for(auto &pr : result){
        cout << pr.first << ' ' << pr.second << '\n';
    }
    return (ll)result.size();
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
