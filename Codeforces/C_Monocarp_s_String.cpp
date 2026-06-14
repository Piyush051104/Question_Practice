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
    ll n;cin >> n;
    string s;cin >> s;
    
    ll cnta = 0,cntb = 0;
    for(auto &i:s){
        if(i == 'a') cnta++;
        else cntb++;
    }
    if(cnta == cntb) return 0;
    if(cnta > cntb){
        ll ans = n;
        map<ll,ll>mp;
        mp[cnta - cntb] = -1;
        ll rema = cnta,remb = cntb;
        for(ll i = 0 ;i < n;i++){
            if(s[i] == 'a') rema--;
            else remb--;

            mp[rema - remb] = i;

            ll val = cnta - cntb + rema - remb;
           
            if(mp.find(val) != mp.end()){
                ans = min(ans,i - mp[val]);
            }
        }
        if(ans == n) ans = -1;
        return ans;  
    }
    else{
        ll ans = n;
        map<ll,ll>mp;
        mp[cntb - cnta] = -1;
        ll rema = cnta,remb = cntb;
        for(ll i = 0 ;i < n;i++){
            if(s[i] == 'a') rema--;
            else remb--;

            mp[remb - rema] = i;
             
            ll val = cntb - cnta + remb - rema;
            //if(i == 2) cout << val << " ";
            if(mp.find(val) != mp.end()){
                ans = min(ans,i - mp[val]);
            }
        }
        if(ans == n) ans = -1;
        return ans;  
    }
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