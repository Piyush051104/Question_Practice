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
void solve(){
    ll n,m;cin >> n >> m;
    vector<ll>prog(n + m + 1),test(n + m + 1);
    loop(i,n + m + 1) cin >> prog[i];
    loop(i,n + m + 1) cin >> test[i];
    ll to = n + m + 1;
    vector<char>check(to);
    vector<ll>flag(to),forced(to);
    ll p = n,t = m;
    ll sum = 0;
    for(ll i = 0 ;i < to - 1 ;i++){
        if(p > 0 && t > 0){
            if(prog[i] > test[i]){
                check[i] = 'p';
                sum += prog[i];
                flag[i] = 1;
                p--;
            }
            else{
                check[i] = 't';
                sum += test[i];
                flag[i] = 1;
                t--;
            }
            forced[i] = 1;
        }
        else if(p > 0){
            check[i] = 'p';
            sum += prog[i];
            p--;
            if(prog[i] > test[i]) flag[i] = 1;
            else flag[i] = 0;
            forced[i] = 0;
        }
        else{
            check[i] = 't';
            sum += test[i];
            t--;
            if(test[i] > prog[i]) flag[i] = 1;
            else flag[i] = 0;
            forced[i] = 0;
        }
    }
    vector<ll>ans(to);
    ans[to - 1] = sum;
    ll pri = to - 1,tei = to - 1;
    for(ll i = to - 2 ;i >= 0;i--){
        if(forced[i] == 0){
            if(check[i] == 't'){
                ans[i] = sum - test[i] + test[to - 1];
            }
            else{
                ans[i] = sum - prog[i] + prog[to - 1];
            }
        }
        else{
            ll val = sum;
            if(check[i] == 't'){
                val -= test[i];
                val += test[tei];
                val -= prog[tei];
                val += prog[to - 1];
                ans[i] = val;
            }
            else{
                val -= prog[i];
                val += prog[pri];
                val -= test[pri];
                val += test[to - 1];

                ans[i] = val;
            }
        }

        if(flag[i] == 0){
            if(check[i] == 't'){
                pri = i;
            }
            else tei = i;
        }
    }
    for(ll i = 0 ;i < to ;i++){
        cout << ans[i] << " ";
    }
    cout << endl;

}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}