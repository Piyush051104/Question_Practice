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
vector<ll>spf(1e6 + 1);
void buildspf(){
    for(ll i = 1 ;i <= 1e6;i++){
        spf[i] = i;
    }

    for(ll i = 2 ; i <= 1e6;i++){
        if(spf[i] == i){
            for(ll j = i * i ;j <= 1e6 ;j += i){
                if(spf[j] == j){
                    spf[j] = i;
                }
            }
        }
    }
}
ll getprimefactor(ll num){
    ll val = 1;
    while(num > 1){
        ll x = spf[num];
        ll cnt = 0;
        while(num % x == 0){
            num /= x;
            cnt++;
        }
        if(cnt % 2 != 0) val *= x;
    }
    return val;
}
void solve(){
    ll n;cin >> n;
    vector<ll>v(n);
    loop(i,n) cin >> v[i];

    ll q;cin >> q;

    ll cnt = 0;
    map<ll,ll>mp;
    for(ll i = 0 ;i < n;i++){
        ll val = getprimefactor(v[i]);
        
        if(val == 1){
            cnt++;
        }
        else{
            mp[val]++;
        }
    }

    ll maxi = 0;
    ll evencnt = 0;
    for(auto &i:mp){
        maxi = max(maxi,i.second);
        if(i.second % 2 == 0) evencnt += i.second;
    }
    
    for(ll i = 0 ;i < q;i++){
        ll w;cin >> w;
        if(w == 0){
            cout << max(maxi,cnt) << endl;
        }
        else{
            cout << max(maxi,cnt + evencnt) << endl;
        }
    }
    return;









}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    buildspf();
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}