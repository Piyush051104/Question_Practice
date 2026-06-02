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
    ll n;cin >> n;
    vector<ll>v(n);
    bool flag1 = false,flag2 = false;
    loop(i,n){
        cin >> v[i];
        if(v[i] > 0) flag1 = true;
        if(v[i] < 0) flag2 = true;
    }
    if(flag1 == false || flag2 == false){
        cout << 0 << endl;
        cout << endl;
        return;
    }
    vector<ll>sum1(n,0);
    vector<ll>sum2(n,0);
    ll sum = 0;
    for(ll i = 0; i < n;i++){
        sum += abs(v[i]);
        sum1[i] = sum;
    }
    sum = 0;
    for(ll i = n - 1;i >= 0;i--){
        sum += v[i];
        sum2[i] = sum;
    }
    ll in = 0;
    ll maxi = sum;
    for(ll i = 0 ;i < n;i++){
        if(v[i] > 0){
            ll a = -v[i];
            if(i + 1 <= n - 1) a += sum2[i + 1];
            if(i - 1 >= 0) a += sum1[i - 1];

            if(a > maxi){
                maxi = a;
                in = i;
            }
        }
    }
    if(in == 0){
        cout << 0 << endl;
        cout << endl;
        return;
    }
    vector<ll>ans;
   
    for(ll i = 0; i < in;i++){
        
        if(v[i] > 0){
            
            if(i == in - 1){
                ans.push_back(i);
                ans.push_back(i - 1);
            }
            else if(v[i + 1] < 0){
                ans.push_back(i);
                if(i - 1 >= 0){
                    ans.push_back(i - 1);
                }
            }
            else{
                ans.push_back(i + 1);
                if(i - 1 >= 0) ans.push_back(i - 1);
                i++;
            }
        }
    }
    ans.push_back(in);
    cout << ans.size() << endl;
    for(auto &i:ans){
        cout << i + 1 << " ";
    }
    cout << endl;
    return;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}