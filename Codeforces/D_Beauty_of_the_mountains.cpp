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
long long gcd_all(const vector<long long>& a) {
    long long g = 0;
    for (long long x : a) g = std::gcd(g, llabs(x));
    return g;
}

bool possible(long long n, const vector<long long>& coeff) {
    long long g = gcd_all(coeff);
    return g != 0 && llabs(n) % g == 0;
}
bool solve(){
    ll n,m,k;cin >> n >> m >> k;
    vector<vector<ll>>v(n + 1,vector<ll>(m + 1));
    for(ll i = 1; i <= n;i++){
        for(ll j = 1 ;j <= m;j++){
            cin >> v[i][j];
        }
    }
    vector<string>s(n);
    loop(i,n) cin >> s[i];

    ll sum1 = 0,sum2 = 0;
    vector<vector<ll>>temp(n + 1,vector<ll>(m + 1));
    vector<vector<ll>>prefix(n + 1,vector<ll>(m + 1));
    for(ll i = 0 ;i < n;i++){
        for(ll j = 0 ; j < m;j++){
            if(s[i][j] == '1'){
                sum1+=v[i + 1][j + 1];
                temp[i + 1][j + 1] = 1;
            }
            else{
                sum2+= v[i + 1][j + 1];
                temp[i + 1][j + 1] = 0;
            }
        }
    }
    if(sum1 == sum2) return true;
    for(ll i = 1 ;i <= n;i++){
        for(ll j = 1 ;j <= m;j++){
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + temp[i][j];
        }
    }
    //cout << sum1 << " " << sum2 << " ";
    ll val = abs(sum1 - sum2);
    vector<ll>ch;
    for(ll i = 1 ;i <= n;i++){
        for(ll j = 1 ;j <= m;j++){
            if(i - k >= 0 && j - k >= 0){
                ll val1 = prefix[i][j] - prefix[i][j - k] - prefix[i - k][j] + prefix[i-k][j-k];;
                ll val2 = k * k - val1;

               
                ll freq = abs(val2 - val1);

                if(freq != 0) ch.push_back(freq);
            }
        }
    }
    bool flag = possible(val,ch);
    if(flag == true) return true;
    return false;



}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        bool ans = solve();
        if(ans) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}