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
ll wait_to_next_zero(ll n, int k) {
    ll B = 1LL << k;            
    ll r = n & (2*B - 1);        
    if (r >= B) {                
        return 2*B - r;        
    } else {                     
        if (r < B - 1) return 1; 
        else return B + 1;      
    }
}
ll solve(vector<ll>&power,ll &cnt){
    ll n,k;cin >> n >> k;
    // if(cnt == 272){
    //     cout <<n << "," << k ;
    //     return -1;
    // }
    if(k > n) return -1;
    if(n == k) return n;
    if(k & 1) return -1;
    ll in = upper_bound(all(power),n) - power.begin();
    
    if(k == 0) return power[in];
    if( k < power[in  - 1]) return -1;
    string a =  bitset<64>(n).to_string();
    string b =  bitset<64>(k).to_string();
    for(ll i = 0 ;i < 64;i++){
        if(b[i] == '1' && a[i] == '0') return -1;
    }
    
    vector<ll>temp;
    bool flag = false;
    for(ll i = 0 ;i < 64 ;i++){
        if(flag){
            if(b[i] == '1') return -1;
            temp.push_back(0);
            continue;
        }
        if(a[i] == '1' && b[i] == '0'){
            
            if(temp.size() == 0 || temp.back() == 1) return -1;
            temp.pop_back();
            temp.push_back(1);
            temp.push_back(0);
            flag = true;
            continue;
        }
        temp.push_back(a[i] - '0');
    }
    ll ans = 0;
    for(ll i = 0 ;i < temp.size();i++){
        if(temp[i] == 1) ans += power[temp.size() - 1 - i];  
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    //vector<ll>power(65,1);
    vector<unsigned long long> power(64,1);
    for(int i = 1 ; i < 64 ; i++){
        power[i] = 2ULL * power[i - 1];
    }
    ll cnt = 0;
    while(t--){
        cnt++;
        ll ans = solve(reinterpret_cast<vector<ll>&>(power),cnt);
        cout << ans << endl;
    }
    return 0;
}