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
ll find1(ll in,ll pr,ll n,vector<ll>&v,vector<vector<ll>>&dp1){
    if(in >= n){
        return 0;
    }

    if(dp1[in][pr + 1] != -1) return dp1[in][pr + 1];

    ll ans = 0;

    ll newpr = v[in] * pr;
    if(newpr == 1){
        ans += 1 + find1(in + 1,newpr,n,v,dp1);
    }
    else{
        ans += find1(in + 1,newpr,n,v,dp1);
    }
    dp1[in][pr + 1] = ans;
    return ans;
}
ll find2(ll in,ll pr,ll n,vector<ll>&v,vector<vector<ll>>&dp2){
    if(in >= n){
        return 0;
    }

    if(dp2[in][pr + 1] != -1) return dp2[in][pr + 1];

    ll ans = 0;

    ll newpr = v[in] * pr;
    if(newpr == -1){
        ans += 1 + find2(in + 1,newpr,n,v,dp2);
    }
    else{
        ans += find2(in + 1,newpr,n,v,dp2);
    }
    dp2[in][pr + 1] = ans;
    return ans;
}
void solve(){
    ll n;cin >> n;
    vector<ll>v(n);
    loop(i,n){
        ll a;cin >> a;
        if(a > 0) v[i] = 1;
        else v[i] = -1;
    }
    vector<vector<ll>>dp1(n + 1,vector<ll>(3,-1));
    vector<vector<ll>>dp2(n + 1,vector<ll>(3,-1));
    ll ans1 = 0;
    for(ll i = 0 ;i < n;i++){
        ans1 += find1(i,1,n,v,dp1);
    }
    ll ans2 = 0;
    for(ll i = 0 ;i < n;i++){
        ans2 += find2(i,1,n,v,dp2);
    }

    cout << ans2 << " " << ans1 << endl;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; t = 1;
    while(t--){
        solve();
    }
    return 0;
}