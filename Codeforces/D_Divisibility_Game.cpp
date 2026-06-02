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
// --- Sieve (SPF) based divisor generation ---
// Build SPF up to maxN (inclusive). Assumes maxN >= 1 and reasonably sized for memory.
vector<ll> build_spf(ll maxN){
    vector<ll> spf(maxN + 1);
    for (ll i = 0; i <= maxN; ++i) spf[i] = i;
    if (maxN >= 0) spf[0] = 0;
    if (maxN >= 1) spf[1] = 1;
    for (ll i = 2; (ll)i * i <= maxN; ++i){
        if (spf[i] == i){
            for (ll j = 1LL * i * i; j <= maxN; j += i){
                if (spf[(ll)j] == (ll)j) spf[(ll)j] = i;
            }
        }
    }
    return spf;
}

// Generate divisors using prime factorization with SPF
vector<ll> get_divisors_with_spf(ll n, const vector<ll>& spf){
    vector<pair<ll,ll>> fac;
    if (n == 1){
        return vector<ll>{1};
    }
    while (n > 1){
        ll p = spf[(ll)n];
        ll cnt = 0;
        while (n % p == 0){
            n /= p;
            ++cnt;
        }
        fac.emplace_back(p, cnt);
    }
    vector<ll> divs;
    function<void(ll, ll)> gen = [&](ll idx, ll cur){
        if (idx == (ll)fac.size()){
            divs.push_back(cur);
            return;
        }
        ll p = fac[idx].first;
        ll e = fac[idx].second;
        ll v = 1;
        for (ll i = 0; i <= e; ++i){
            gen(idx + 1, cur * v);
            v *= p;
        }
    };
    gen(0, 1LL);
    sort(divs.begin(), divs.end());
    return divs;
}
bool solve(vector<ll>& spf){   
    ll n, m; cin >> n >> m;
    vector<ll> v1(n);
    set<ll> st;
    ll max1 = 0;
    for(ll i = 0; i < n; i++){
        cin >> v1[i];
        st.insert(v1[i]);
        if(v1[i] > max1) max1 = v1[i];
    }
    
    vector<ll> v2(m);
    ll max2 = 0;
    for(ll i = 0; i < m; i++){
        cin >> v2[i];
        if(v2[i] > max2) max2 = v2[i];
    }
    
    ll overall_max = max(max1, max2);
    vector<int> div_count(overall_max + 1, 0);
    
    for(ll x : st){
        for(ll multiple = x; multiple <= overall_max; multiple += x){
            div_count[multiple]++;
        }
    }
    
    ll cnt1 = 0, cnt2 = 0, cnt3 = 0;
    for(ll i = 0; i < m; i++){
        ll cnt = div_count[v2[i]];
        if(cnt == (ll)st.size()) cnt3++;
        else if(cnt == 0) cnt2++;
        else cnt1++;
    }
    
    ll alice = (cnt1 + 1) / 2;
    ll bob = cnt2 + (cnt1 - alice);
    alice += cnt3;
    return alice > bob;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    vector<ll> spf = build_spf(2*1e6 + 1);
    
    ll t; cin >> t;
    while(t--){
        bool ans = solve(spf);
        if(ans) cout << "Alice" << endl;
        else cout << "Bob" << endl;
    }
    return 0;
}