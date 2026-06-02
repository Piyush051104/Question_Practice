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
    string s;cin >> s;
    ll n = s.length();
    ll cnt1 = 0,cnt2 = 0;
    ll cnt3 = 0,cnt4 = 0;
    for(ll i = 0; i < n;i++){
        if(s[i] == '+'){
            if(cnt4 > 0) cnt4++;
            else cnt3++;
        }
        else if(s[i] == '-'){
            if(cnt4 > 0) cnt4--;
            else{
                if(cnt3 > 0) cnt3--;
                else cnt1--;
            }
        }
        else if(s[i] == '0'){
            if(cnt4 > 0) continue;
            else{
                
                if(cnt3 <= 1 && cnt1 == 0) return false;
                else if(cnt3 <= 0 && cnt1 > 0) return false;
                else{
                    cnt3--;
                    cnt4++;
                }
            }
        }
        else{
            if(cnt4 == 0) {
                cnt1 += cnt3;
                cnt3 = 0;
                continue;
            }
            else return false;
        }
    }
    for(ll i = 0; i < n - 1;i++){
        if(s[i] == '0'){
            if(s[i + 1] == '1') return false;
        }
        if(s[i] == '1'){
            if(s[i + 1] == '0') return false;
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