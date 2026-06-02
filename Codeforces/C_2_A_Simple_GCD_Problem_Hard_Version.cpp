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
ll solve(){
    ll n;cin >> n;
    vector<ll>v1(n),v2(n);
    loop(i,n) cin >> v1[i];
    loop(i,n) cin >> v2[i];

    vector<ll>pp = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};


    vector<vector<ll>>dp(n + 1,vector<ll>(60 + 1,0));

    vector<bool>flag(n,false);

    for(ll i = 0 ;i < n;i++){
        ll lc = 1;
        if(i > 0) lc = lcm(__gcd(v1[i],v1[i - 1]),lc);
        if(i < n - 1) lc = lcm(__gcd(v1[i],v1[i + 1]),lc);

        if(lc != v1[i] && lc <= v2[i]){
            v1[i] = lc;
            flag[i] = true;
        }

    }

    for(ll i = 0 ;i < n;i++){
        ll lc = 1;
        if(i > 0) lc = lcm(lc,__gcd(v1[i],v1[i - 1]));
        if(i < n - 1) lc = lcm(lc,__gcd(v1[i],v1[i + 1]));

        ll best = 0;
        if(i > 0){
            for(auto k:pp){
                if(__gcd(v1[i],k*v1[i - 1]) == __gcd(v1[i],v1[i - 1])){
                    best = max(best,dp[i - 1][k]);
                }
            }
        }

        if(lc > v2[i]){
            dp[i][1] = best;
            continue;
        }
        if(flag[i]){
            dp[i][1] = best + 1;
            continue;
        }

        for(auto j:pp){
            if(j*v1[i] > v2[i]) continue;
            if(i > 0){
                if(__gcd(j*v1[i],v1[i - 1]) != __gcd(v1[i],v1[i - 1])) continue;
            }
            ll val = 0;
            if(i > 0){
                for(auto k:pp){
                    if(__gcd(j*v1[i],k*v1[i - 1]) == __gcd(v1[i],v1[i - 1])){
                        val = max(val,dp[i - 1][k]);
                    }
                }
            }
            dp[i][j] = val;
            if(j > 1) dp[i][j]++;
        }
    }

    return (*max_element(dp[n - 1].begin(),dp[n -1].end()));

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