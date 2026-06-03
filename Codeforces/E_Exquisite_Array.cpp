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
template<typename T, typename V> bool ckmax(T &a, V b) { return (long long) a < (long long) b ? a = b, 1: 0; }
template<typename T, typename V> bool ckmin(T &a, V b) { return (long long) a > (long long) b ? a = b, 1: 0; }
template <typename T> ostream &operator<<(ostream &out, const vector<T> &v) { for (const auto &x : v) out << x << ' '; return out; }
template <typename T> istream &operator>>(istream &in, vector<T> &v) { for (auto &x : v) in >> x; return in; }
class DSU{
    public:
    vector<ll>par,size;

    DSU(ll n){
        par.resize(n);
        size.resize(n);
        for(ll i = 0; i < n;i++){
            par[i] = i;
            size[i] = 1;
        }
    }

    ll findpar(ll node){
        if(par[node] != node) return par[node] = findpar(par[node]);
        else return node;
    }
    ll value(ll x){
        return (x*(x + 1))/2;
    }
    

    void ubs(ll u,ll v,ll &cnt){
        ll up = findpar(u);
        ll vp = findpar(v);


        if(up == vp) return;
        cnt -= value(size[vp]);
        cnt -= value(size[up]);
        if(size[up] > size[vp]){
            par[vp] = up;
            size[up] += size[vp];
            cnt += value(size[up]);
            
        }
        else{
            par[up] = vp;

            size[vp] += size[up];
            cnt += value(size[vp]);
        }

    }
};

void solve() {
    ll n;
    cin >> n;
    vector<ll> v(n);
    loop(i, n) cin >> v[i];

    if (n == 1) {
        cout << "\n";
        return;
    }

    vector<ll> diff;
    for (ll i = 1; i < n; i++) diff.push_back(abs(v[i] - v[i - 1]));

    ll sz = diff.size();
    vector<vector<ll>> mp(n);
    for (ll i = 0; i < sz; i++) mp[diff[i]].push_back(i);

    vector<ll>active(sz,0);
    ll curr = 0;
    vector<ll>ans;

    DSU ds(sz);
    ll cnt = 0;
    for(ll i = n - 1 ;i >= 1;i--){
        if(mp[i].size() == 0){
            if(ans.size() == 0) ans.push_back(0);
            else{
                ll ba = ans.back();
                ans.push_back(ba);
            }
        }
        else{
            
            for(auto &j:mp[i]){
                active[j] = 1;
                ds.size[j] = 1;
                cnt += 1;
                if(j - 1 >= 0 && active[j - 1] == 1){
                    ds.ubs(j,j - 1,cnt);
                }
                if(j + 1 < sz && active[j + 1] == 1){
                    ds.ubs(j,j + 1,cnt);
                }
                
            }
            ans.push_back(cnt);
        } 
    }
    reverse(all(ans));
    for(auto &i:ans){
        cout << i << " ";
    }
    cout << endl;
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) solve();
    return 0;
}