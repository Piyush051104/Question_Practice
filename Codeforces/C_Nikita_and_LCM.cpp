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

long long lcm_safe(long long a, long long b, long long mx) {
    if (a == 0) return b;
    long long g = std::gcd(a, b);
    a /= g;
    if (a > mx / b) return mx + 1;
    return a * b;
}

const ll NEG = (ll)-9e15;
vector<ll> arr;
vector<unordered_map<ll,ll>> memo;
unordered_set<ll> present;
ll N, MAXA;

ll dfs(ll idx, ll cur){
    if(idx == N){
        if(cur == 0 || cur > MAXA || present.find(cur) == present.end()) return 0;
        return NEG;
    }
    auto it = memo[idx].find(cur);
    if(it != memo[idx].end()) return it->second;
    ll ans = dfs(idx + 1, cur);
    ll nl = lcm_safe(cur, arr[idx], MAXA);
    ll take = dfs(idx + 1, nl);
    if(take != NEG) ans = max(ans, take + 1);
    return memo[idx][cur] = ans;
}

ll solve(){
    cin.tie(nullptr);
    cin >> N;
    arr.assign(N, 0);
    present.clear();
    MAXA = 0;
    loop(i,N){
        cin >> arr[i];
        present.insert(arr[i]);
        MAXA = max(MAXA, arr[i]);
    }
    ll lcmval = 1;
    for(ll i = 0; i < N; ++i){
        lcmval = lcm_safe(lcmval, arr[i], MAXA);
        if(lcmval > MAXA) return N;
    }
    memo.assign(N+1, unordered_map<ll,ll>());
    ll ans = dfs(0, 0);
    if(ans < 0) ans = 0;
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        cout << solve() << '\n';
    }
    return 0;
}
