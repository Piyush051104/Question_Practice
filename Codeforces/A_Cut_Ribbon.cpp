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

ll n,a,b,c;
ll find(ll in,vector<ll>&dp){
    
    ll rem = n - in;
    if(rem == 0) return 0;
    if(rem < a && rem < b && rem < c) return LLONG_MIN;
    if(in >= n) return 0;

    

    if(dp[in] != -1) return dp[in];

    ll ans = LLONG_MIN;

    if(in + a <= n){
        ll val = find(in + a,dp);
        if(val != LLONG_MIN) ans = max(ans,1 + val);
    }
    if(in + b <= n){
        ll val = find(in + b,dp);
        if(val != LLONG_MIN) ans = max(ans,1 + val);
    }
    if(in + c <= n){
        ll val = find(in + c,dp);
        if(val != LLONG_MIN) ans = max(ans,1 + val);
    }

    dp[in] = ans;
    return dp[in];
    
}
ll solve(){
    cin >> n >> a >> b >> c;
    vector<ll>dp(n + 1,-1);

    ll ans = find(0,dp);
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