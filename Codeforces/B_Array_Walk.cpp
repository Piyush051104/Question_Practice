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
ll find(ll in,ll remleft,ll x,ll le,ll n,ll k,vector<ll>&v,vector<vector<vector<ll>>>&dp){
    if(in - 1 + 2*(x - remleft) == k) return 0;
    if(in < 0 || in >= n) return -1e18;
    if(remleft < 0) return -1e18;
    


    if(dp[in][remleft][le] != -1) return dp[in][remleft][le];

    ll ans = 0;
    if(le != 1 && in != 0){
        
        if(remleft > 0) ans = v[in] + find(in - 1,remleft - 1,x,1,n,k,v,dp);
        ans = max(ans,v[in] + find(in + 1,remleft,x,0,n,k,v,dp));
    }
    else{
        ans =  max(ans,v[in] + find(in + 1,remleft,x,0,n,k,v,dp));
    }

    dp[in][remleft][le] = ans;

    return ans;
}
ll solve(){
    ll n,k,x;cin >> n >> k >> x;
    vector<vector<vector<ll>>>dp(n + 3,vector<vector<ll>>(x + 1,vector<ll>(2,-1)));
    vector<ll>v(n);
    loop(i,n) cin >> v[i];


    ll ans = find(0,x,x,1,n,k,v,dp);

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