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
const ll INF = (ll)9e18;

ll findans(ll i, ll h, ll x, vector<pair<ll,ll>>& v, vector<vector<ll>>& dp){
    
    if(h == 0) return 0;       
    if(i == 0) return INF;     
    if(dp[i][h] != -1) return dp[i][h];

    
    ll res = findans(i - 1, h, x, v, dp);

    
    ll cost = v[i - 1].first;
    int happy = (int)v[i - 1].second;
    if(h >= happy){
        ll prevCost = findans(i - 1, h - happy, x, v, dp);
        ll avail = (i - 1) * x; 
        if(prevCost != INF && prevCost + cost <= avail){
            res = min(res, prevCost + cost);
        }
    }

    dp[i][h] = res;
    return res;
}

ll solve(){
    
    ll n,x;cin >> n >> x;
    vector<pair<ll,ll>> v(n);
    ll happ = 0;
    loop(i,n){
        ll a,b;cin >> a >> b;
        v[i] = {a,b};
        happ += b;
    }

    
    vector<vector<ll>> dp(n + 1, vector<ll>(happ + 1, -1));

    
    for(ll h = happ; h >= 0; --h){
        ll need = findans(n, h, x, v, dp);
        if(need != INF) return h;
    }
    return 0; 
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
