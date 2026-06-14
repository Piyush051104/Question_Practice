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
vector<ll> subtractVectors(vector<ll> v1, vector<ll> v2) {
    ll i = v1.size() - 1;
    ll j = v2.size() - 1;
    ll borrow = 0;
    vector<ll> ans;

    while (i >= 0 || j >= 0) {
        ll a = (i >= 0 ? v1[i] : 0);
        ll b = (j >= 0 ? v2[j] : 0);

        ll cur = a - borrow - b;
        if (cur < 0) {
            cur += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        ans.push_back(cur);
        i--;
        j--;
    }

    while (ans.size() > 1 && ans.back() == 0) ans.pop_back();

    reverse(ans.begin(), ans.end());
    return ans;
}
void solve(){
    ll n,k;cin >> n >> k;
    vector<ll>v;
    ll num = n;
    ll add = 0;
    while(num > 0){
        add += (num % 10);
        v.push_back(num % 10);
        num /= 10;
    }

    reverse(v.begin(),v.end());
    if(add <= k){
        cout << 0 << endl;
        return;
    }
    else if(add > k){
        ll sum = k;
        vector<ll>temp;
        bool flag = false;
        for(ll i = 0 ;i < v.size();i++){
            if(flag == true){
                temp.push_back(0);
                continue;
            }
            if(v[i] < sum && flag == false){
                sum -= v[i];
                temp.push_back(v[i]);
            }
            else{
                if(temp.empty()){
                    temp.push_back(1);
                    sum--;
                    temp.push_back(0);
                    flag = true;
                }
                else{
                    ll val = temp.back();
                    temp.pop_back();
                    temp.push_back(val + 1);
                    sum--;
                    temp.push_back(0);
                    flag = true;
                }
            }
        }
        vector<ll>ans = subtractVectors(temp,v);
        for(ll i = 0 ;i < ans.size();i++){
            cout << ans[i];
        }
        cout  << endl;
    }
    
    

}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}