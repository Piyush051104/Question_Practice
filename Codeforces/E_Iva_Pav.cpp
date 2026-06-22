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
class sgmt{
    public:
    vector<ll>tree;

    sgmt(ll n){
        tree.assign(4*n + 1,0);
    }


    void build(ll l,ll r,ll in,vector<ll>&v){
        if(l == r){
            tree[in] = v[l];
            return;
        }

        ll mid = (l + r)/2;

        build(l,mid,2*in,v);
        build(mid + 1,r,2*in + 1,v);

        tree[in] = ((tree[2*in]) & (tree[2*in + 1]));
    }

    ll query(ll l,ll r,ll lq,ll rq,ll in){
        if(l > rq || r < lq)  return (1LL << 30) - 1;
        if(l >= lq && r <= rq) return tree[in];
        ll mid = (l + r)/2;

        ll a = query(l,mid,lq,rq,2*in);
        ll b = query(mid + 1,r,lq,rq,2*in + 1);

        return a & b;

    }    
};
void solve(){
    ll n;cin >> n;
    vector<ll>v(n);
    loop(i,n){
        cin >> v[i];
    }
    ll q;cin >> q;
    sgmt st(n);
    st.build(0,n - 1,1,v);
    for(ll i = 0 ;i < q;i++){
        ll l,k;cin >> l >> k;
        l--;

        ll low = l,high = n - 1,ans = l - 1;
        while(low <= high){
            ll mid  = (low + high)/2;

            ll val = st.query(0,n - 1,l,mid,1);

            if(val >= k){
                ans = mid;
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }
        if(ans == l - 1) cout << -1 << " ";
        else cout << ans + 1 << " ";
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