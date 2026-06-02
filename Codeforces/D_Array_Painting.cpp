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
    vector<ll>v(n);
    loop(i,n) cin >> v[i];
    vector<ll>temp;
    ll ans = 0;
    for(ll i  = 0 ;i < n;i++){
        if(v[i] == 0) temp.push_back(v[i]);
        else if(v[i] == 1){
            if(temp.size() == 0) temp.push_back(1);
            else{
                if(temp.back() == 0) temp.push_back(1);
            }
        }
        else{
            if(temp.size() == 0) temp.push_back(2);
            else{
                if(temp.back() == 2) continue;
                else if(temp.back() == 0) temp.push_back(2);
                else{
                    if(i == n - 1){
                        temp.pop_back();
                        temp.push_back(2);
                    }
                    else{
                        if(v[i + 1] == 0){
                            temp.pop_back();
                            temp.push_back(2);
                        }
                        else{
                            ans--;
                            temp.push_back(1);
                        }
                    }
                } 

            }
        }
    }
    
    for(ll i = 0 ;i < temp.size();i++){
        //cout << temp[i] << " ";
        if(temp[i] != 0) ans++;
    }
    for(ll i = 0 ;i < temp.size();i++){
        if(temp[i] == 0){
            if(i - 1 >= 0){
                if(temp[i - 1] > 0) continue;
            }
            if(i + 1 <= temp.size() - 1){
                if(temp[i + 1] > 0){
                    temp[i + 1]--;
                    i++;
                    continue;
                }
            }
            ans++;
        }
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; t = 1;
    while(t--){
        ll ans = solve();
        cout << ans << endl;
    }
    return 0;
}