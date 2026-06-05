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

class DSU{
public:
    vector<ll>parent,size;
    DSU(){
        parent.resize(27);
        size.resize(27);
        for(ll i = 0 ;i < 27;i++){
            parent[i] = i;
            size[i] = 1;
        }
    }

    ll findpar(ll node){
        if(parent[node] == node) return node;
        else return parent[node] = findpar(parent[node]);
    }

    void ubs(ll u,ll v,ll &cnt,vector<pair<ll,ll>>&ans){
        ll up = findpar(u);
        ll vp = findpar(v);

        if(up == vp) return;
        cnt++;
        ans.push_back({u,v});
        if(size[up] > size[vp]){
            size[up] += size[vp];
            parent[up] = parent[vp];
        }
        else{
            size[vp] += size[up];
            parent[vp] = parent[up];
        }
    }
};
void solve(){
    ll n;cin >> n;
    string s1,s2;
    cin >> s1 >> s2;
    vector<vector<ll>>graph(27);
    ll cnt = 0;
    vector<pair<ll,ll>>ans;
    DSU ds;
    for(ll i = 0 ;i < n;i++){
        if(s1[i] != s2[i]){
            ll u = s1[i] - 'a';
            ll v = s2[i] - 'a';

            ds.ubs(u,v,cnt,ans);
        }
    }
    cout << cnt << endl;
    if(cnt > 0){
        for(auto [u,v]:ans){
            cout << char(u + 'a') << " " << char(v + 'a') << endl;
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; t = 1;
    while(t--){
        solve();
    }
    return 0;
}