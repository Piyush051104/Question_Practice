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
ll find(ll in,ll prev,ll cnteven,ll cntodd,vector<ll>&v, vector<vector<vector<vector<ll>>>>&dp){
    if(in >= v.size()) return 0;


    if(dp[in][cnteven][cntodd][prev + 1] != -1)  return dp[in][cnteven][cntodd][prev + 1];


    ll ans = LLONG_MAX;

    
    
    if(prev == -1){
        if(v[in] == 0){
            if(cnteven > 0){
                ans = find(in + 1,0,cnteven - 1,cntodd,v,dp);
            }
            if(cntodd > 0){
                ans = min(ans,find(in + 1,1,cnteven,cntodd - 1,v,dp));
            }
        }
        else{
            if(v[in] & 1){
                ans = find(in + 1,1,cnteven,cntodd,v,dp);
            }
            else ans = min(ans,find(in + 1,0,cnteven,cntodd,v,dp)); 
        }  
    }
    else{
        if(v[in] == 0){
            if(cnteven > 0){
                if(prev == 0) ans = find(in + 1,0,cnteven - 1,cntodd,v,dp);
                else{
                    ll val = find(in + 1,0,cnteven - 1,cntodd,v,dp);
                    if(val != LLONG_MAX) ans = min(ans,1 + val);
                }
            }
            if(cntodd > 0){
                if(prev == 1) ans = min(ans,find(in + 1,1,cnteven,cntodd - 1,v,dp));
                else{
                    ll val = find(in + 1,1,cnteven,cntodd - 1,v,dp);
                    if(val != LLONG_MAX) ans = min(ans,1 + val);
                }
            }
        }
        else{
            if(v[in] & 1){
                if(prev == 1 ) ans = find(in + 1,1,cnteven,cntodd,v,dp);
                else{
                    ll val = find(in + 1,1,cnteven,cntodd,v,dp);
                    if(val != LLONG_MAX) ans = min(ans,1 + val);
                }
            }
            else{
                if(prev == 0)ans = min(ans,find(in + 1,0,cnteven,cntodd,v,dp));
                else{
                    ll val = find(in + 1,0,cnteven,cntodd,v,dp);
                    if(val != LLONG_MAX) ans = min(ans,1 + val);
                }
            } 
        }
    }
    dp[in][cnteven][cntodd][prev + 1] = ans;
    return dp[in][cnteven][cntodd][prev + 1]; 
}
ll solve(){
    ll n ;cin >> n;
    vector<ll>v(n);
    vector<bool>flag(n + 1,false);
    loop(i,n){
        cin >> v[i];
        flag[v[i]] = true;
    }
    ll cnteven = 0,cntodd = 0;
    for(ll i = 1 ;i <= n;i++){
        if(flag[i] == false){
            if(i & 1) cntodd++;
            else cnteven++;
        }

    }
    for(ll i = 0 ;i < n;i++){
        if(v[i] & 1) v[i] = 1;
        else{
            if(v[i] != 0) v[i] = 2;
        }
    }
    vector<vector<vector<vector<ll>>>> dp(n + 1,vector<vector<vector<ll>>>(101,vector<vector<ll>>(101,vector<ll>(3,-1))));

    ll ans = find(0,-1,cnteven,cntodd,v,dp);
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