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
bool solve(ll &cnt){
    ll n;cin >> n;
    vector<ll>v(n);
    loop(i,n) cin >> v[i];
    ll curr = -1;
    for(ll i = 1 ;i < n;i++){
        if(v[i] < v[i - 1]){
            ll need = v[i - 1] - v[i];
            curr = max(curr,need);
        }
    }
    for(ll i = 1 ;i < n;i++){
        if(v[i] < v[i - 1]){
            v[i] += curr;
        }
    }
    for(ll i = 1 ;i < n;i++){
        if(v[i] < v[i - 1]){
            return false;
        }
    }
    
    return true;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    ll cnt = 0;
    while(t--){
        cnt++;
        bool ans = solve(cnt);
        if(ans) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}