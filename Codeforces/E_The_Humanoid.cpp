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
    ll n,initalpower;
    cin >> n >> initalpower;
    vector<ll>v(n);
    loop(i,n) cin >> v[i];
    sort(all(v));

    ll ans1 = 0;
    ll cnt1 = 0;
    ll h1 = initalpower;
    for(ll i = 0 ;i < n;i++){
        if(v[i] < h1){
            ll add = v[i]/2;
            h1 += add;
            ans1++;
        }
        else if(cnt1 == 0){
            h1 *= 3;
            i--;
            cnt1++;
            continue;
        }
        else if(cnt1 == 1){
            h1 *= 2;
            i--;
            cnt1++;
            continue;
        }
        else if(cnt1 == 2){
            h1 *= 2;
            i--;
            cnt1++;
            continue;
        }
        else{
            break;
        }
    }
    ll ans2 = 0;
    ll h2 = initalpower;
    ll cnt2 = 0;

    for(ll i = 0 ;i < n;i++){
        if(v[i] < h2){
            ll add = v[i]/2;
            h2 += add;
            ans2++;
        }
        else if(cnt2 == 0){
            h2 *= 2;
            i--;
            cnt2++;
            continue;
        }
        else if(cnt2 == 1){
            h2 *= 2;
            i--;
            cnt2++;
            continue;
        }
        else if(cnt2 == 2){
            h2 *= 3;
            i--;
            cnt2++;
            continue;
        }
        else{
            break;
        }
    }
    ll ans3 = 0;
    ll h3 = initalpower;
    ll cnt3 = 0;

    for(ll i = 0 ;i < n;i++){
        if(v[i] < h3){
            ll add = v[i]/2;
            h3 += add;
            ans3++;
        }
        else if(cnt3 == 0){
            h3 *= 2;
            i--;
            cnt3++;
            continue;
        }
        else if(cnt3 == 1){
            h3 *= 3;
            i--;
            cnt3++;
            continue;
        }
        else if(cnt3 == 2){
            h3 *= 2;
            i--;
            cnt3++;
            continue;
        }
        else{
            break;
        }
    }

    return max({ans1,ans2,ans3});

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