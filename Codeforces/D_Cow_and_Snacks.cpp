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
class DSU{
    public:
    vector<ll>par,size;
    

    DSU(ll n){
        par.resize(n + 1),size.resize(n + 1);
        for(ll i = 1 ;i <= n;i++){
            par[i] = i;
            size[i] = 1;
        }
    }

    ll findpar(ll node){
        if(par[node] != node) return par[node] = findpar(par[node]);
        else return node;
    }

    void ubs(ll u,ll v,ll &cnt){
        ll up = findpar(u);
        ll vp = findpar(v);

        if(up == vp){
            cnt++;
            return;
        }
        if(size[up] > size[vp]){
            size[up] += size[vp];
            par[vp] = up;
        }
        else{
            size[vp] += size[up];
            par[up] = vp;
        }
    }
};
ll solve(){
    ll n,k;cin >> n >> k;
    
    
    DSU dsu(n);
    ll cnt = 0;
    for(ll i = 0 ;i < k;i++){
        ll u,v;cin >> u >> v;
        dsu.ubs(u,v,cnt);
        
    }
    return cnt;

    

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