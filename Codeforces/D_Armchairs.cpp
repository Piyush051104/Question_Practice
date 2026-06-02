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
ll find(ll i1,ll i2,ll n1,ll n2,vector<ll>&v1,vector<ll>&v2,vector<vector<ll>>&dp){
    if(i1 >= n1) return 0;
    if(i2 >= n2){
        return LLONG_MAX;
    }
    

    if(dp[i1][i2] != -1) return dp[i1][i2];


    ll ans = LLONG_MAX;
    ll val = find(i1 + 1,i2 + 1,n1,n2,v1,v2,dp);
    if(val != LLONG_MAX) ans = abs(v1[i1] - v2[i2]) + val;

    

    ans = min(ans,find(i1,i2 + 1,n1,n2,v1,v2,dp));

    dp[i1][i2] = ans;
    return dp[i1][i2] = ans;

}
ll solve(){
    ll n;cin >> n;
    vector<ll>v(n),v1,v2;
    loop(i,n) cin >> v[i];
    loop(i,n){
        if(v[i] == 1) v1.push_back(i);
        else v2.push_back(i);
    }
    if(v1.size() == 0) return 0;
    sort(all(v1));
    sort(all(v2));
    ll n1 = v1.size();
    ll n2 = v2.size();
    vector<vector<ll>>dp(n1 + 1,vector<ll>(n2 + 1,-1));
    ll ans = find(0,0,n1,n2,v1,v2,dp);
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