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
template<const int mod>
struct mint {
    int val;
    constexpr mint(long long x = 0) : val((x % mod + mod) % mod) {}
    explicit operator int() const { return val; }
    mint& operator+=(const mint &b) { val = (val + 1LL * b.val) % mod; return *this; }
    mint& operator-=(const mint &b) { val -= b.val; if (val < 0) val += mod; return *this; }
    mint& operator*=(const mint &b) { val = 1LL * val * b.val % mod; return *this; }
    mint& operator/=(const mint &b) { return *this *= b.inv(); }
    mint inv() const { return powermod(val, mod - 2, mod); }
    mint power(int b) const { mint a = *this, res(1); for (; b; a *= a, b /= 2) if (b & 1) res *= a; return res; }
    mint operator-() const { return val == 0 ? 0 : mod - val; }
    friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
    friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
    friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
    friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
    friend ostream& operator<<(ostream &os, const mint &a) { return os << a.val; }
};
using Mint = mint<MOD>;
class SegmentTree{
public:
    ll n;
    vector<ll>tree,lazy;
    SegmentTree(ll n){
        tree.resize(4*n);
        lazy.resize(4*n);
    }
    void build(ll node,ll l,ll r,vector<ll>&v){
        if(l == r){
            tree[node] = v[l];
            return;
        }
        ll mid = (l + r)/2;
        build(2*node,l,mid,v);
        build(2*node + 1,mid + 1,r,v);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }
    void push(ll node,ll l,ll r){
        if(lazy[node]){
            tree[node] += (r - l + 1) * lazy[node];
            if(l!=r){
                lazy[2*node] += lazy[node];
                lazy[2*node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void pointupdate(ll idx,ll val,ll l,ll r,ll node){
        push(node,l,r);
        if(idx < l || idx > r) return;
        if(l == r){
            tree[node] = val;
            return;
        }
        ll mid = (l + r)/2;
        pointupdate(idx,val,l,mid,2*node);
        pointupdate(idx,val,mid + 1,r,2*node + 1);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }
    void rangeupdate(ll node,ll lq,ll rq,ll l,ll r,ll val){
        push(node,l,r);
        if(lq > r  || l > rq) return ;
        if(l >= lq && r <= rq){
            lazy[node] += val;
            push(node,l,r);
            return;
        }
        ll mid = (l + r)/2;
        rangeupdate(2*node,lq,rq,l,mid,val);
        rangeupdate(2*node + 1,lq,rq,mid + 1,r,val);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }
    ll query(ll lq,ll rq,ll l ,ll r,ll node){
        push(node,l,r);
        if(lq > r  || l > rq) return 0;
        if(l >= lq && r <= rq) return tree[node];
        ll mid = (l + r)/2;
        return query(lq,rq,l,mid,2*node) + query(lq,rq,mid + 1,r,2*node + 1);
    }
};
pair<ll,pair<ll,ll>> find(ll st,ll end,vector<ll>&v,ll n){
    ll cnt = 0,twocnt = 0;
    for(ll i = st + 1 ; i < end;i++){
        if(v[i] < 0) cnt++;
        if(abs(v[i]) == 2) twocnt++;
    }
    if(cnt % 2 == 0){
        
        return {twocnt,{st,n - end}};
    }
    else{
        ll cnt1 = 0,in1 = 0,cnt2 = 0,in2 = 0;
        for(ll i = st + 1;i < end;i++){
            if(v[i] < 0){
                if(abs(v[i]) == 2) cnt1++;
                in1 = i;
                break;
            }
            else if(abs(v[i]) == 2) cnt1++;
        }
        for(ll i = end - 1;i > st;i--){
            if(v[i] < 0){
                if(abs(v[i]) == 2) cnt2++;
                in2 = i;
                break;
            }
            else if(abs(v[i]) == 2) cnt2++;
        }
        if(cnt1 <= cnt2){
            
            return {twocnt - cnt1 ,{in1,n - end}};
        }
        
        else return {twocnt - cnt2,{st,n - in2}};
    }
}
void solve(){
    ll n;cin >> n;
    vector<ll>v(n);
    ll cnt = 0;
    bool flag = false;
    loop(i,n){
        cin >> v[i];
        if(v[i] < 0) cnt++;
        if(v[i] == 0) flag = true;
    }
    if(cnt %2 == 0 && flag == false){
        cout << 0 << " " << 0 << endl;
        return;
    }
    else if(flag == false){
        ll cnt1 = 0,in1 = 0,cnt2 = 0,in2 = 0;
        for(ll i = 0;i < n;i++){
            if(v[i] < 0){
                if(abs(v[i]) == 2) cnt1++;
                in1 = i;
                break;
            }
            else if(abs(v[i]) == 2) cnt1++;
        }
        for(ll i = n - 1;i >= 0;i--){
            if(v[i] < 0){
                if(abs(v[i]) == 2) cnt2++;
                in2 = i;
                break;
            }
            else if(abs(v[i]) == 2) cnt2++;
        }

        if(cnt1 <= cnt2){
            cout << in1 + 1 << " " << 0 << endl;
        }
       
        else{
            ll reb = n - in2;
            cout << 0 << " " << reb << endl;
        }
        return;
    }
    else{
        vector<ll>temp;
        temp.push_back(-1);
        for(ll i = 0 ;i < n;i++){
            if(v[i] == 0) temp.push_back(i);
        }
        temp.push_back(n);
        ll ans1 = 0,ans2 = 0;
        ll twocnt = 0;
        for(ll i = 0 ;i < temp.size() - 1;i++){
            ll st = temp[i],end = temp[i + 1];
            //cout << st << " " << end << endl;
            auto ans = find(st,end,v,n);
            //cout << ans.first << " " << ans.second.first << " " << ans.second.second << endl;
            if(ans.first >= twocnt){
                ans1 = ans.second.first;
                ans2 = ans.second.second;
                twocnt = ans.first;
            }
        }
        cout << ans1 + 1 << " " << ans2 << endl;
        return;
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