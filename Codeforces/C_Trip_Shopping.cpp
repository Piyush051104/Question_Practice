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
bool comp(pair<ll,ll>p1,pair<ll,ll>p2){
    if(p1.first != p2.first) return p1.first < p2.first;
    else return p1.second < p2.second;
}
ll solve(){
    ll n,k;cin >> n >> k;
    vector<ll>v1(n),v2(n);
    loop(i,n) cin >> v1[i];
    loop(i,n) cin >> v2[i];
    vector<pair<ll,ll>>temp;
    loop(i,n){
        ll mini = min(v1[i],v2[i]);
        ll maxi = max(v1[i],v2[i]);
        temp.push_back({mini,maxi});
    }
    sort(all(temp),comp);
    ll sum = 0;
    for(auto i:temp){
        sum += abs(i.second - i.first);
    }
    if(k == 0){
        return sum;
    }
    ll diff = INT_MAX;
    ll in = 0;
    ll ans = 0;
    
    for(ll i = 0 ;i < n -1 ;i++){
        pair<ll,ll>p1 = temp[i];
        pair<ll,ll>p2 = temp[i + 1];
        
        ll a =p1.first, b = p1.second,c = p2.first ,d = p2.second; 
        ll dis1 =abs(b - a) + abs(d - c);
        vector<ll>so = {a,b,c,d};
        sort(all(so));
        ll d1 = so[3] - so[0];
        ll d2 = so[2] - so[1];
        ll dis = d1 + d2;
        diff = min(diff,abs(dis1 - dis));
        
    }
   
    sum+=diff;
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