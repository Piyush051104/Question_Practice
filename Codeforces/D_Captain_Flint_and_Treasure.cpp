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

ll powermod(ll x, ll y, ll p){
    ll res = 1;
    x = x % p;
    if (x == 0) return 0;
    while (y > 0){
        if (y & 1) res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

vector<ll> a, b, degree, seq, sub;
ll n;
vector<vector<ll>> graph, child;
ll ans = 0;

void dfs(ll node){
    sub[node] = a[node];
    for(auto &ch : child[node]){
        dfs(ch);
        if(sub[ch] > 0) sub[node] += sub[ch];
    }
}

void solve(){
    ans = 0;
    cin >> n;
    a.assign(n + 1, 0);
    b.assign(n + 1, 0);
    degree.assign(n + 1, 0);
    graph.assign(n + 1, {});
    child.assign(n + 1, {});
    sub.assign(n + 1, 0);
    seq.clear();

    loop1(1, n + 1){
        ll u; cin >> u;
        a[i] = u;
    }
    loop1(1, n + 1){
        ll u; cin >> u;
        b[i] = u;
    }

    
    for(ll i = 1; i <= n; i++){
        if(b[i] != -1){
            child[b[i]].push_back(i);
        }
    }

    
    for(ll i = 1; i <= n; i++){
        if(b[i] == -1){
            dfs(i);
        }
    }

    
    vector<vector<ll>> tempgraph(n + 1);
    degree.assign(n + 1, 0);

    for(ll i = 1; i <= n; i++){
        if(b[i] != -1){
            if(sub[i] > 0){
                tempgraph[i].push_back(b[i]);
                degree[b[i]]++;
            } else {
                tempgraph[b[i]].push_back(i);
                degree[i]++;
            }
        }
    }

    stack<ll> st;
    for(ll i = 1; i <= n; i++){
        if(degree[i] == 0) st.push(i);
    }

    while(!st.empty()){
        ll top = st.top();
        st.pop();
        seq.push_back(top);

        for(auto &ch : tempgraph[top]){
            degree[ch]--;
            if(degree[ch] == 0) st.push(ch);
        }
    }

    
    for(ll x : seq){
        ans += a[x];
        if(b[x] != -1) a[b[x]] += a[x];
    }

    cout << ans << '\n';
    for(ll x : seq) cout << x << ' ';
    cout << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}