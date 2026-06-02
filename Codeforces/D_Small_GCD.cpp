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
vector<ll> build_spf(ll N) {
    vector<ll> spf(N+1);
    for (ll i = 0; i <= N; ++i) spf[i] = i;
    for (ll i = 2; (ll)i * i <= N; ++i) {
        if (spf[i] == i) {
            for (ll j = i * i; j <= N; j += i)
                if (spf[j] == j) spf[j] = i;
        }
    }
    return spf;
}
vector<pair<ll,ll>> factorize(ll x, const vector<ll>& spf) {
    vector<pair<ll,ll>> res;
    while (x > 1) {
        ll p = spf[x];
        ll cnt = 0;
        while (x % p == 0) {
            x /= p;
            ++cnt;
        }
        res.emplace_back(p, cnt);
    }
    return res;
}
void gen_divs_dfs(ll idx, ll cur, const vector<pair<ll,ll>>& fac, vector<ll>& out) {
    if (idx == (ll)fac.size()) {
        out.push_back((ll)cur);
        return;
    }
    ll p = fac[idx].first;
    ll e = fac[idx].second;
    ll val = cur;
    for (ll i = 0; i <= e; ++i) {
        gen_divs_dfs(idx+1, val, fac, out);
        val *= p;
    }
}
vector<ll> get_divisors(ll x, const vector<ll>& spf) {
    if (x == 1) return {1};
    auto fac = factorize(x, spf);
    vector<ll> out;
    gen_divs_dfs(0, 1, fac, out);
    return out;
}


ll solve(vector<ll>&spf){
    ll n;cin >> n ;
    vector<ll>v(n);
    ll maxi = 1;
    for(ll i = 0 ;i < n;i++){
        cin >> v[i];
        maxi = max(maxi,v[i]);
    }
    sort(all(v));
    vector<vector<ll>>divisor(maxi+1);
    for(ll i = 0 ;i < n;i++){
        vector<ll>div = get_divisors(v[i],spf);
        for(auto &j:div){
            divisor[j].push_back(v[i]);
        }
    }
    
    vector<ll>mul(maxi + 1,0);
    for(ll i = 1 ;i <= maxi;i++){
        map<ll,ll>mp;
        sort(all(divisor[i]));
        for(ll j = 0 ; j < divisor[i].size();j++){
           
            ll in = lower_bound(all(v), divisor[i][j]) - v.begin();
            
            ll right = n - 1 - in - mp[divisor[i][j]];
            ll left = j;
            mul[i] += left * right;
            mp[divisor[i][j]]++;
        }
        
    }
    

    vector<ll>fin(maxi + 1,0);
    for(ll i = maxi ; i>= 1;i--){
        ll curr = mul[i];
        for(ll j = i + i; j <= maxi;j += i){
            curr -= fin[j];
        }
        fin[i] = curr;
    }
    ll ans = 0;
    for(ll i = 1 ;i <= maxi;i++){
        ans += (i * fin[i]);
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    ll MAXA = 100000;
    vector<ll> spf = build_spf(MAXA);
    while(t--){
        ll ans = solve(spf);
        cout << ans << endl;
    }
    return 0;
}