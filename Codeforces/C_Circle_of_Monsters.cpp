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
ll solve(){
    ll n;cin >> n;
    vector<pair<ll,ll>>v(n);
    loop(i,n){
        ll a,b;cin >> a >> b;
        v[i] = {a,b};
    }
    vector<ll>breaks(n,0);
    for(ll i = 1 ;i < n;i++){
        if(v[i].first <= v[i - 1].second) continue;
        else{
            breaks[i] = v[i].first - v[i -1].second;
        }
    }
    if(v[0].first > v[n - 1].second){
        breaks[0] = v[0].first - v[n -1].second;
    }
    vector<ll>prefix(n);
    prefix[0] = breaks[0];
    for(ll i = 1; i < n;i++){
        prefix[i] += breaks[i];
        prefix[i] += prefix[i - 1];
    }
    ll ans = LLONG_MAX;
    for(ll i = 0 ;i < n;i++){
        ll val = v[i].first;
        ll right = prefix[n - 1] - prefix[i];

        if(i - 1 >= 0){
            right += prefix[i - 1];
        }
        val += right;
        ans = min(ans,val);
    }
    return ans;
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