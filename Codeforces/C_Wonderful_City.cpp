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
ll n;
vector<ll>rowop,colop;
vector<vector<ll>>v;
vector<vector<ll>>dp1,dp2;


ll find1(ll in,ll prev){
    if(in >= n + 1) return 0;

    if(dp1[in][prev] != -1) return dp1[in][prev];


    ll ans = LLONG_MAX;

    bool flag1 = false,flag2 = false;
    for(ll j = 1 ;j <= n;j++){
        if(v[in][j] == v[in - 1][j] + prev){
            flag1 = true;
        }
        if(v[in][j] + 1 == v[in - 1][j] + prev){
            flag2 = true;
        }
    }
    if(flag1 == true && flag2 == true){
        dp1[in][prev] = LLONG_MAX;
        return ans;
    }
    if(flag2 == false){
        ll val = find1(in + 1,1);
        if(val != LLONG_MAX){
            ans = min(ans,rowop[in] + val);
        }
    }
    if(flag1 == false){
        ans = min(ans,find1(in + 1,0));
    }
    

    dp1[in][prev] = ans;
    return ans;  
}

ll find2(ll in,ll prev){
    if(in >= n + 1) return 0;

    if(dp2[in][prev] != -1) return dp2[in][prev];


    ll ans = LLONG_MAX;

    bool flag1 = false,flag2 = false;
    for(ll j = 1 ;j <= n;j++){
        if(v[j][in] == v[j][in - 1] + prev){
            flag1 = true;
        }
        if(v[j][in] + 1 == v[j][in - 1] + prev){
            flag2 = true;
        }
    }
    if(flag1 == true && flag2 == true){
        dp2[in][prev] = LLONG_MAX;
        return ans;
    }
    if(flag2 == false){
        ll val = find2(in + 1,1);
        if(val != LLONG_MAX){
            ans = min(ans,colop[in] + val);
        }
    }
    if(flag1 == false){
        ans = min(ans,find2(in + 1,0));
    }
    

    dp2[in][prev] = ans;
    return ans;  
}
ll solve(){
    cin >> n;
    rowop.assign(n + 1,0);
    colop.assign(n + 1,0);
    v.assign(n + 1,vector<ll>(n + 1,0));
    dp1.assign(n + 2,vector<ll>(2,-1));
    dp2.assign(n + 2,vector<ll>(2,-1));
    loop1(1,n + 1){
        for(ll j = 1;j <= n;j++){
            ll a;cin >> a;
            v[i][j] = a;
        }
    }
    loop1(1,n + 1){
        ll a;cin >> a;
        rowop[i] = a;
    }
    loop1(1,n + 1){
        ll a;
        cin >> a;
        colop[i] = a;
    }
    ll ans1 = find1(2,0);

    ll temp = find1(2,1);
    if(temp != LLONG_MAX) ans1 = min(ans1, rowop[1] + temp);

    ll ans2 = find2(2,0);

    temp = find2(2,1);
    if(temp != LLONG_MAX) ans2 = min(ans2, colop[1] + temp);

    if(ans1 == LLONG_MAX || ans2 == LLONG_MAX) return -1;

    return ans1 + ans2;

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