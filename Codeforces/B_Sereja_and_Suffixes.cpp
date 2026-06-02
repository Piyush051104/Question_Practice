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
void solve(){
    ll n,m;cin >> n >> m;
    vector<ll>v(n + 2);
    loop1(1,n + 1) cin >> v[i];
    set<ll>st;
    vector<ll>freq(n + 2);
    for(ll i = n ;i >= 1;i--){
        st.insert(v[i]);
        freq[i] = st.size();
    }
    loop(i,m){
        ll in;cin >> in;
        cout << freq[in] << endl;
    }
    return;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; t = 1;
    while(t--){
        solve();
    }
    return 0;
}