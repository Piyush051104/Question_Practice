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
    ll n,m;cin >> n >> m;
    string s;cin >> s;
    vector<ll>forward(n + 2,n + 1);
    vector<ll>backward(n + 2,0);
    for(ll i = n - 1 ;i >= 0;i--){
        if(s[i] == '0') forward[i + 1] = forward[i + 2];
        else forward[i + 1] = i + 1;
    }
    for(ll i = 0 ;i < n;i++){
        if(s[i] == '1') backward[i + 1] = backward[i];
        else backward[i + 1] = i + 1;
    }
    set<pair<ll,ll>>st;
    for(ll i = 0 ;i < m;i++){
        ll l,r;cin >> l >> r;
        l = forward[l];
        r = backward[r];

        if(l >= r) st.insert({1,1});
        else st.insert({l,r});
    }
    return st.size();
    
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