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
    vector<ll>v(n);
    ll sum = 0;
    loop(i,n){
        cin >> v[i];
        sum += v[i];
    }

    sum -= v[n - 1];
    vector<ll>suff(n);
    ll mini = v[n - 1];
    suff[n - 1] = mini;
    for(ll i = n - 2 ;i >= 0;i--){
        mini = min(mini,v[i]);
        suff[i] = mini;
        sum -= mini;
    }

    ll curr = 1;
    ll maxi = 1;
    for(ll i = 1 ;i < n;i++){
        if(suff[i] == suff[i - 1]) curr++;
        else{
            curr = 1;
        }
        maxi = max(maxi,curr);
    }

    return sum + maxi - 1;
    



   


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