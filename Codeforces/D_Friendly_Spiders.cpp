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
// clang-format off
template<typename T, typename V> bool ckmax(T &a, V b) { return (long long) a < (long long) b ? a = b, 1: 0; }
template<typename T, typename V> bool ckmin(T &a, V b) { return (long long) a > (long long) b ? a = b, 1: 0; }
template <typename T> ostream &operator<<(ostream &out, const vector<T> &v) { for (const auto &x : v) out << x << ' '; return out; }
template <typename T> istream &operator>>(istream &in, vector<T> &v) { for (auto &x : v) in >> x; return in; }
// clang-format on
template<const int mod>
struct mint {
    int val;
    constexpr mint(long long x = 0) : val((x % mod + mod) % mod) {}
    explicit operator int() const { return val; }
    mint& operator+=(const mint &b) { 
        val = (val + 1LL * b.val) % mod;
        return *this; 
    }
    mint& operator-=(const mint &b) { 
        val -= b.val; 
        if (val < 0) val += mod; 
        return *this; 
    }
    mint& operator*=(const mint &b) { 
        val = 1LL * val * b.val % mod; 
        return *this; 
    }
    mint& operator/=(const mint &b) { 
        return *this *= b.inv(); 
    }
    mint inv() const { 
        return powermod(val, mod - 2, mod);
    }
    mint power(int b) const { 
        mint a = *this, res(1);
        for (; b; a *= a, b /= 2)
            if (b & 1) res *= a; 
        return res; 
    }
    mint operator-() const { return val == 0 ? 0 : mod - val; }
    mint& operator++() { val = val == mod - 1 ? 0 : val + 1; return *this; }
    mint& operator--() { val = val == 0 ? mod - 1 : val - 1; return *this; }
    mint operator++(int32_t) { mint before = *this; ++*this; return before; }
    mint operator--(int32_t) { mint before = *this; --*this; return before; }
    friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
    friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
    friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
    friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
    friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
    friend bool operator!=(const mint &a, const mint &b) { return a.val != b.val; }
    friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }
    friend istream& operator>>(istream &in, mint &a) { return in >> a.val; }
    friend ostream& operator<<(ostream &os, const mint &a) { return os << a.val; }
};
using Mint = mint<MOD>;
/*bool isPrime(ll num) {
       if(num <= 1) return false;
        if (num <= 3)  return true; 
        ll range = sqrt(num);
        if (num % 2 == 0 || num % 3 == 0) 
            return false;
        for (ll i = 5; i <= range; i += 6) 
            if (num % i == 0 || num % (i + 2) == 0) 
                return false; 
        return true;
 }*/
/*ll gcd(ll a, ll b)
    for (;;)
    {
        if (a==0) return b;
        b%=a;
        if (b==0) return a;
        a%=b;
    }
}
ll lcm(ll a, ll b)
{
    ll temp = gcd(a,b);
    return temp ? (a/temp*b):0;
}*/
//string a=  bitset<32>(x).to_string();
//ACII 0-48,9-57 a-97 z-122 A-65 Z-90
const ll MAXN = 3000000;

vector<ll> spf(MAXN + 1);

void build_spf() {
    for (ll i = 0; i <= MAXN; i++) spf[i] = i;

    for (ll i = 2; i * i <= MAXN; i++) {
        if (spf[i] == i) {
            for (ll j = i * i; j <= MAXN; j += i) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}
vector<ll> factorize_distinct(ll n) {
    vector<ll> res;
    while (n > 1) {
        ll p = spf[n];
        res.push_back(p);
        while (n % p == 0) {
            n /= p;
        }
    }
    return res;
}
void solve(){
    ll n;cin >> n;
    vector<ll>v(n + 1);
    vector<bool>flag(3*1e6 + 1,false);
    map<ll,ll>mp;
    ll maxi = 0;
    loop1(1,n + 1){
        cin >> v[i];
        flag[v[i]] = true;
        maxi = max(maxi,v[i]);
        mp[v[i]] = i;
    }
    ll st,end;cin >> st >> end;
    if(st == end){
        cout << 1 << endl;
        cout << st << endl;
        return;
    }
    if(v[st] == v[end]){
        if(v[st] == 1){
            cout << -1 << endl;
            return;
        }
        cout << 2 << endl;
        cout << st << " " << end << endl;
        return;
    }
    vector<vector<ll>>graph(n + 1);

    for(auto &i:mp){
        ll val = i.first;

        ll i1 = i.second;
        auto ve = factorize_distinct(val);
        for(auto &k:ve){
            for(ll j = k;j <= maxi ;j += k){
                if(flag[j] == true){
                    ll i2 = mp[j];
                    graph[i1].push_back(i2);
                    graph[i2].push_back(i1);
                }
            }
        }
        
    }

    vector<ll>dis(n + 1,LLONG_MAX);
    vector<ll>par(n + 1,LLONG_MAX);

    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;

    dis[st] = 0;
    pq.push({0,st});
    par[st] = st;
    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();

        if(dis[top.second] != top.first) continue;

        for(auto &child:graph[top.second]){

            if(dis[child] > dis[top.second] + 1){
                par[child] = top.second;
                dis[child] = dis[top.second] + 1;
                pq.push({dis[top.second] + 1,child});
            }
        }
    }
    
    if(dis[end] == LLONG_MAX){
        cout << -1 << endl;
        return;
    }
    
    vector<ll>ans;
    ans.push_back(end);
    ll node = end;
    while(par[node] != node){
       
        ans.push_back(par[node]);
        node = par[node];
    }

    reverse(all(ans));
    cout << ans.size() << endl;
    for(auto &i:ans){
        cout << i << " ";
    }
    cout << endl;


}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    build_spf();
    ll t; t = 1;
    while(t--){
        solve();
    }
    return 0;
}