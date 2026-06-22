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
ll find(ll in,ll lastnum,ll k,ll n,vector<vector<ll>>&dp){
    if(in >= k - 1) return 1;

    if(dp[in][lastnum] != -1) return dp[in][lastnum];

    ll ans = 0;
    ll cnt = 1;

    while(lastnum * cnt <= n){
        ans = (ans + find(in + 1,lastnum * cnt,k,n,dp) ) % MOD;
        cnt++;
    }
    dp[in][lastnum] = ans;
    return ans;

}
ll solve(){
    ll n,k;cin >> n >> k;
    vector<vector<ll>>dp(k + 1,vector<ll>(n + 1,-1));

    ll ans = 0;

    for(ll i = 1 ;i <= n;i++){
        ans = (ans + find(0,i,k,n,dp)) % MOD;
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; t = 1;
    while(t--){
        ll ans = solve();
        cout << ans << endl;
    }
    return 0;
}