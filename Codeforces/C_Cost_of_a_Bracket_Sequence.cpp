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
// clang-format off
template<typename T, typename V> bool ckmax(T &a, V b) { return (long long) a < (long long) b ? a = b, 1: 0; }
template<typename T, typename V> bool ckmin(T &a, V b) { return (long long) a > (long long) b ? a = b, 1: 0; }
template <typename T> ostream &operator<<(ostream &out, const vector<T> &v) { for (const auto &x : v) out << x << ' '; return out; }
template <typename T> istream &operator>>(istream &in, vector<T> &v) { for (auto &x : v) in >> x; return in; }
void solve(){
    ll n,k;cin >> n >> k;
    string s;cin >> s;
    vector<bool>ans;
    ll currlen = LLONG_MAX;
    for(ll i = 0 ;i <= k;i++){
        ll pref  = i;
        ll suff = k - i;
        vector<bool>check(n,false);
        set<ll>st;
        for(ll j = 0 ;j < n;j++){
            if(s[j] == '(' && pref > 0){
                check[j] = true; 
                pref--;
            }
        }
        for(ll j = n - 1;j >= 0 ;j--){
            if(s[j] == ')' && suff > 0){
                check[j] = true;
                suff--;
            }
        }
        string temp = "";
        for(ll j = 0 ;j < n;j++){
            if(check[j] == false){
                temp += s[j];
            }
        }
        
        ll cnt = 0;
        ll len = 0;
        for(auto &j:temp){
            if(j == '(') cnt++;
            if(j == ')'){
                if(cnt > 0){
                    cnt--;
                    len += 2;
                }
                
            }
        }
       
        if(len < currlen){
            currlen = len;
            ans = check;
        }
    }

    for(ll i =  0; i < n;i++){
        if(ans[i] == false){
            cout << 0;
        }
        else cout << 1;
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