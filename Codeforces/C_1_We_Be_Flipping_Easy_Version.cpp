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
void solve(){
    ll n;cin >> n;
    vector<ll>v(n);
    loop(i,n) cin >> v[i];
    vector<ll>ans;
    ll cnt = 0;
    for(ll i = n - 1 ;i >= 0;i--){
        if(v[i] < 0){
            if(cnt % 2 == 0) continue;
            else{
                ans.push_back(i + 1);
                cnt++;
            }
        }
        else{
            if(cnt % 2 == 0){
                ans.push_back(i + 1);
                cnt++;
            }
            else continue;
        }
    }
    cout << ans.size() << endl;
    for(auto &i:ans){
        cout << i << " ";
    }
    cout << endl;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}