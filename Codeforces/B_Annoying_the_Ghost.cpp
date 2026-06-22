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
    vector<ll>v1(n),v2(n);
    loop(i,n) cin >> v1[i];
    loop(i,n) cin >> v2[i];

    ll ans = 0;
    for(ll i =  0 ;i < n;i++){

        if(v1[i] >  v2[i]){
            ll in = n;
            for(ll j = i + 1;j < n;j++){
                if(v1[j] <= v2[i]){
                    in = j;
                    break;
                }
            }
            if(in == n) return -1;

            for(ll j = in ;j >= i + 1; j--){
                swap(v1[j],v1[j - 1]);
                ans++;
            }
        }
    }
    return ans;
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