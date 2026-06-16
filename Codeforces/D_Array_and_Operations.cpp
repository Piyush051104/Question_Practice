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
    ll n,k;cin >> n >> k;
    vector<ll>v(n);
    map<ll,ll>mp;
    ll sum = 0;
    loop(i,n){
        cin >> v[i];
        sum += v[i];
        mp[v[i]]++;
    }
    if(k == 0) return sum;
    sort(v.rbegin(),v.rend());
    ll ans = 0;
    vector<ll>temp;
    for(ll i = 0 ;i < k;i++){
        temp.push_back(v[i]);
    }
    ll st = 0;
    for(ll i = k ; i < k + k ;i++){
        if(temp[st] == v[i]) ans++;
        st++;
    }
    for(ll i = 2*k;i < n;i++){
        ans += v[i];
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