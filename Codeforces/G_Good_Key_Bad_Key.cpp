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

ll n,k;
vector<ll>a;
ll dp[100005][33];
bool vis[100005][33];

ll rec(ll i,ll d){
    if(i==n) return 0;
    if(d>32) d=32;
    if(vis[i][d]) return dp[i][d];
    vis[i][d]=true;
    ll cur = (d>=63?0:(a[i]>>d));
    ll good = cur - k + rec(i+1,d);
    ll bad = (d+1>=63?0:(a[i]>>(d+1))) + rec(i+1,d+1);
    return dp[i][d]=max(good,bad);
}

ll solve(){
    cin>>n>>k;
    a.assign(n,0);
    loop(i,n) cin>>a[i];
    memset(vis,false,sizeof(vis));
    return rec(0,0);
}

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    ll t;cin>>t;
    while(t--){
        cout<<solve()<<"\n";
    }
    return 0;
}
