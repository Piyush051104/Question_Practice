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
    ll n,k;cin >> n >> k;
    vector<ll>v(n);
    set<ll>st;
    map<ll,ll>mp;
    loop(i,n){
        cin >> v[i];
        st.insert(v[i]);
        mp[v[i]]++;
    }
    ll start = 0;
    for(auto i:st){
        if(i != start){
            break;
        }
        else{
            start++;
        }
    }
    vector<ll>v1(n);
    loop(i,n){
        mp[v[i]]--;
        if(v[i] > start) v1[i] = start;
        else if(mp[v[i]] == 0) v1[i] = v[i];
        else{
            v1[i] = start;
        }
        mp[v[i]]++;
    }
    if(k == 1){
        ll sum = 0;
        for(ll i = 0  ;i < n;i++){
            sum += v1[i];
        }
        return sum;
    }



    vector<ll>v2(n);
    mp.clear();
    st.clear();
    loop(i,n){
        mp[v1[i]]++;
        st.insert(v1[i]);
    }
    start = 0;
    for(auto i:st){
        if(i != start){
            break;
        }
        else{
            start++;
        }
    }
    loop(i,n){
        mp[v1[i]]--;
        if(v1[i] > start) v2[i] = start;
        else if(mp[v1[i]] == 0) v2[i] = v1[i];
        else{
            v2[i] = start;
        }
        mp[v1[i]]++;
    }
    if(k % 2 == 0){
        ll sum = 0;
        for(ll i = 0  ;i < n;i++){
            sum += v2[i];
        }
        return sum;
    }




    
    vector<ll>v3(n);
    mp.clear();
    st.clear();
    loop(i,n){
        mp[v2[i]]++;
        st.insert(v2[i]);
    }
    start = 0;
    for(auto i:st){
        if(i != start){
            break;
        }
        else{
            start++;
        }
    }
    loop(i,n){
        mp[v2[i]]--;
        if(v2[i] > start) v3[i] = start;
        else if(mp[v2[i]] == 0) v3[i] = v2[i];
        else{
            v3[i] = start;
        }
        mp[v2[i]]++;
    }
    //cout << "true" << endl;
    ll sum = 0;
    for(ll i = 0 ; i < n;i++){
        sum += v3[i];
    }
    return sum;
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