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

bool check(ll mid,ll n,ll m,vector<pair<ll,ll>>&temp,vector<ll>&power){
    ll num = n;
    for(ll i = 0 ;i < temp.size();i++){
        ll val = power[temp[i].first];
        val *= mid;
        num -= val;
        if(num < 0) break;
    }
    return num <= 0;
}
ll solve(vector<ll>&power){
    ll n,m;cin >> n >> m;
    string s1 = bitset<64>(n).to_string();
    s1 = s1.substr(s1.find('1'));
    string s2 = bitset<64>(m).to_string();
    s2 = s2.substr(s2.find('1'));

    ll l1 = s1.length();
    ll l2 = s2.length();
    set<ll>st;
    for(ll i = 0 ;i < s2.length();i++){
        if(s2[i] == '1'){
         
            st.insert(l2 - 1 - i);
        }
    }
    map<ll,ll>mp;
    for(ll i = 0 ;i < s1.length();i++){
        if(s1[i] == '1'){
            ll i1 = l1 - 1 - i;
            if(st.find(i1) != st.end()){
               
                mp[i1]++;
            }
            else{
                auto it = st.lower_bound(i1);
                if(it == st.begin()) return -1;
                else{
                    --it;
                    ll nu = *it;
                    ll diff = i1 - nu;
                   
                    mp[nu] += (power[diff]); 
                }
            }
        }
    }
    vector<pair<ll,ll>>temp;
    ll low = 1,high = LLONG_MIN;
    for(auto &i:mp){
        temp.push_back({i.first,i.second});
        high = max(high,i.second);
    }
    
    ll ans = low;
    while(low <= high){
        ll mid = (low + high)/2;
        bool flag = check(mid,n,m,temp,power);
        if(flag){
            high = mid - 1;
            ans = mid;
        }
        else low = mid + 1;
    }
    return ans;
    
    
    
   

}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    vector<ll>power(65,1);
    for(ll i = 1 ;i <= 64;i++){
        power[i] = 2 * power[i - 1];
    }
    
    while(t--){
        ll ans = solve(power);
        cout << ans << endl;
    }
    return 0;
}