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
bool check(ll mid,ll n,ll k,vector<ll>&freq){
    

    ll cnt = 0;
    for(ll i = 0 ;i < 27;i++){
        if(freq[i] & 1){
            cnt += (freq[i] - 1);
        }
        else{
            cnt += freq[i];
        }
    }
    // if(mid == 3){
    //     cout << cnt << " ";
    // }
    if(mid & 1){
        ll cnt2 = 0;
        for(ll i = 0 ;i < 27;i++){
            if(freq[i] & 1){
                cnt2++;
            }
        }

        if((mid - 1) * k <= cnt){
            ll extra = (cnt - ((mid - 1) * k));

            if(extra + cnt2 >= k) return true;
            else return false;
        }
        else return false;
    }
    else{
        if(mid * k <= cnt) return true;
        else return false;
    }

}
ll solve(){
    ll n,k;cin >> n >> k;
    string s;cin >> s;
    vector<ll>freq(27,0);
    for(auto &i:s){
        freq[i - 'a']++;
    }

    ll st = 1,end = n,ans = st;
    while(st <= end){
        ll mid = (st + end)/2;

        bool flag = check(mid,n,k,freq);

        if(flag){
            ans = mid;
            st = mid + 1;
        }
        else{
            end = mid - 1;
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