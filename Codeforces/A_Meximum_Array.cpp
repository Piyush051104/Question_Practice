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
vector<int> maximumMEX(vector<int>& v) {
    int n = v.size();
    vector<int>ans;
    set<int>st;
    for(auto &i:v) st.insert(i);
    int mex = 0;
    
    for(auto &i:st){
        if(i != mex){
            break;
        }
        else{
            mex++;
        }
    }
    map<int,int>mp;
    for(int i = 0 ;i < n;i++){
        mp[v[i]]++;
    }
    int newmex = mex;
    set<int>toch;
    for(int i = 0 ;i < n;i++){
        mp[v[i]]--;
        if(mp[v[i]] == 0){
            newmex = min(newmex,v[i]);
        }
        if(v[i] < mex){
            toch.insert(v[i]);
        }
        if(toch.size() == mex){
            ans.push_back(mex);
            mex = newmex;
            toch.clear();
        }
    }
    return ans;


}
void solve(){
    int n;cin >> n;
    vector<int>v(n);
    loop(i,n) cin >> v[i];
    vector<int>ans = maximumMEX(v);
    cout << ans.size() << endl;
    for(int i  = 0 ;i < ans.size();i++){
        cout << ans[i] << " ";
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