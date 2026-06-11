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
ll find(ll in,ll state,vector<pair<char,ll>>&v, vector<vector<ll>>&dp){
    if(in >= v.size()) return 0;

    if(dp[in][state] != -1) return dp[in][state];
    
    ll ans = find(in + 1,state,v,dp);
    if(state == 0){
        if(v[in].first == 'a'){
            ans = max(ans,v[in].second + find(in + 1,state,v,dp));
        }
        if(v[in].first == 'b'){
            ans = max(ans,v[in].second + find(in + 1,1,v,dp));
        }
    }
    if(state == 1){
        if(v[in].first == 'a'){
            ans = max(ans,v[in].second + find(in + 1,2,v,dp));
        }
        if(v[in].first == 'b'){
            ans = max(ans,v[in].second + find(in + 1,1,v,dp));
        }
    }
    if(state == 2){
        if(v[in].first == 'a'){
            ans = max(ans,v[in].second + find(in + 1,2,v,dp));
        }
    }
    dp[in][state] = ans;
    return ans;
}
ll solve(){
    string s;cin >> s;
    ll n = s.length();
    vector<pair<char,ll>>v;
    ll cnt = 1;
    char ch = s[0];
    for(ll i = 1 ;i < n;i++){
        if(s[i] != s[i - 1]){
            v.push_back({ch,cnt});
            cnt = 1;
            ch = s[i];
        }
        else{
            cnt++;
        }
    }

    v.push_back({ch,cnt});

    n = v.size();

    vector<vector<ll>>dp(n + 1,vector<ll>(4,-1));
    ll ans = find(0,0,v,dp);
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