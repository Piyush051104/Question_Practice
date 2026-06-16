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
ll get_key(ll x, ll y,ll base){
    if(x > y) swap(x, y);
    return x * base + y;
}
void solve(){
    ll n,q;cin >> n >> q;
    vector<ll>v(n + 1);
    loop1(1,n + 1) cin >> v[i];
    vector<ll>par(n + 1);
    par[1] = 0;
    for(ll i = 2 ;i <= n;i++){
        cin >> par[i];
    }
    unordered_map<ll,ll>mp;

    mp.reserve(4000000);
    mp.max_load_factor(0.7);
    for(ll i = 0 ;i < q;i++){
        ll x,y;cin >> x >> y;
        
        ll ans = 0;
        vector<pair<ll,ll>>temp;
        while(x!= 0 && y != 0){
            ll k  = get_key(x,y,n + 1);
            auto it = mp.find(k);
            if(it != mp.end()){
                ans = it->second;
                break;
            }
            temp.push_back({x,y});
            x = par[x];
            y = par[y];
            if(x > y) swap(x,y);
        }
        for(ll j = temp.size() - 1 ;j >= 0;j--){
            ll a = temp[j].first;
            ll b = temp[j].second;

            ll val1 = v[a];
            ll val2 = v[b];

            ans += (val1 * val2);
            mp[get_key(a,b,n + 1)] = ans;
        }
        cout << ans << endl;
    }
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; t = 1;
    while(t--){
        solve();
    }
    return 0;
}