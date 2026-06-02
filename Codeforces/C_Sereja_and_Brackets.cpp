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
    vector<pair<ll,pair<ll,ll>>>tree;
    SegmentTree(ll n){
        tree.resize(4*n);
        
    }
    void build(ll node,ll l,ll r,string &s){
        if(l == r){
            if(s[l] == '(') tree[node] = {0,{1,0}};
            else tree[node] = {0,{0,1}};
            return;
        }
        ll mid = (l + r)/2;
        build(2*node,l,mid,s);
        build(2*node + 1,mid + 1,r,s);
        ll sum = tree[2*node].first + tree[2*node + 1].first;
        ll mini = min(tree[2*node].second.first,tree[2*node + 1].second.second);
        ll first = tree[2*node].second.first - mini + tree[2*node + 1].second.first;
        ll second = tree[2*node].second.second  + tree[2*node + 1].second.second - mini;
        tree[node] = {sum + mini ,{first,second}};
    }
    pair<ll,pair<ll,ll>> query(ll lq,ll rq,ll l ,ll r,ll node){
        
        if(lq > r  || l > rq) return {0,{0,0}};
        if(l >= lq && r <= rq) return tree[node];
        ll mid = (l + r)/2;
        pair<ll,pair<ll,ll>>left = query(lq,rq,l,mid,2*node);
        pair<ll,pair<ll,ll>>right = query(lq,rq,mid + 1,r,2*node + 1);
        ll sum = left.first + right.first;
        ll mini = min(left.second.first,right.second.second);
        ll first = left.second.first - mini + right.second.first;
        ll second = left.second.second  + right.second.second - mini;
        return {sum + mini ,{first,second}};
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    string s;cin >> s;
    ll q; cin >> q;
    ll n = s.length();
    SegmentTree st(n);
    st.build(1,0,n - 1,s);
    // for(ll i = 1 ;i <= 14;i++){
    //     cout << st.tree[i].first <<" ";
    // }
    //cout << endl;
    loop(i,q){
        ll l,r;cin >> l >> r;
        cout << st.query(l - 1,r - 1,0,n - 1,1).first*2 << endl;
    }
}