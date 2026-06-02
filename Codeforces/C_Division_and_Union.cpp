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
bool comp(pair<int,int>p1, pair<int,int>p2){
    if(p1.first != p2.first) return p1.first < p2.first ;
    else return p1.second < p2.second ;
}
void solve(){
    int n; cin >> n;
    vector<int>ans;
    vector<pair<int,int>>v(n);
    for(int i = 0 ; i < n ;i++){
        int a , b; cin >> a >> b;
        v[i] = {a,b};
    }
    vector<pair<int,int>>temp = v;
    sort(all(v) , comp);
    int l = v[0].first , r = v[0].second ;
    int point = -1 ;
    for( int i = 1 ; i < n; ++i){
        int a = v[i].first ;
        int b = v[i].second;
        if (a > r){
            point = a;
            break;
        }
        else{
            if(a >= l && a <=r && b >= r) r = b;
        }
    }
    if(point == -1){
        cout << -1 << endl;
        return;
    }
    for(int i = 0; i < n; ++i){
        if(temp[i].first >= point) cout << 2 << " ";
        else cout << "1" <<" ";
    }
    cout << endl;
    return ;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}