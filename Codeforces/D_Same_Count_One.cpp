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
    vector<vector<ll>>v(n,vector<ll>(m));
    
    ll cnt = 0;
    vector<ll>temp(n);
    loop(i,n){
        ll one = 0;
        loop(j,m){
            cin >> v[i][j];
            if(v[i][j] == 1){
                cnt++;
                one++;
            }
           
        }
        temp[i] = one;
    }
    
    if(cnt % n != 0){
        cout << -1 << endl;
        return;
    }
   
    ll eachrow = cnt / n;
    
    vector<ll>extra(n);
    vector<ll>needed(n);
    for(ll i = 0 ;i < n;i++){
        if(temp[i] <= eachrow) needed[i] = eachrow - temp[i];
        else{
            extra[i] = temp[i] - eachrow;
        }
    }
    ll ans = 0;
    vector<pair<pair<ll,ll>,ll>>toprint;
    vector<vector<ll>>one(m);
    vector<vector<ll>>zero(m);
    for(ll i = 0 ;i < n;i++){
        if(needed[i] > 0){
            for(ll j = 0 ;j < m;j++){
                if(v[i][j] == 0){
                    zero[j].push_back(i);;
                }
            }
        }
        if(extra[i] > 0){
            for(ll j = 0 ;j < m;j++){
                if(v[i][j] == 1){
                    one[j].push_back(i);;
                }
            }
        }
    }
    
    for(ll i = 0 ;i < n;i++){
        for(ll j = 0 ;j < m;j++){
            if(needed[i] > 0 && v[i][j] == 0){
                while(true){
                    if(one[j].size() == 0) break;
                    if(one[j].size() > 0 && extra[one[j].back()] > 0){
                        ans++;
                        toprint.push_back({{i,one[j].back()},j});
                        extra[one[j].back()]--;
                        one[j].pop_back();
                        needed[i]--;
                        break;
                    }
                    else one[j].pop_back();
                }
               
            }
        }
        
    }
    cout << ans << endl;
    for(ll i = 0 ;i < ans;i++){
        cout << toprint[i].first.first + 1 << " " << toprint[i].first.second + 1 << " " << toprint[i].second + 1<< endl;
    }
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}