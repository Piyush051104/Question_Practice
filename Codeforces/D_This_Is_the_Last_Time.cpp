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
    x %= p;
    if (x == 0) return 0;
    while (y > 0){
        if (y & 1) res = (res * x) % p;
        y >>= 1;
        x = (x * x) % p;
    }
    return res;
}
// clang-format off
template<typename T, typename V> bool ckmax(T &a, V b) { return (long long)a < (long long)b ? a = b, 1 : 0; }
template<typename T, typename V> bool ckmin(T &a, V b) { return (long long)a > (long long)b ? a = b, 1 : 0; }
template <typename T> ostream &operator<<(ostream &out, const vector<T> &v) { for (const auto &x : v) out << x << ' '; return out; }
template <typename T> istream &operator>>(istream &in, vector<T> &v) { for (auto &x : v) in >> x; return in; }
// clang-format on

void solve(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<ll> colo(n + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> colo[i];
    }

    vector<vector<pair<ll,ll>>> graph(n + 1);
    loop(i, n - 1){
        ll a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    // threshold for heavy nodes
    const int B = 450;

    // detect heavy nodes
    vector<char> isHeavy(n + 1, 0);
    vector<int> heavyIdxOfNode(n + 1, -1);
    vector<int> heavyNodes;
    for (int u = 1; u <= n; u++){
        if ((int)graph[u].size() >= B){
            heavyIdxOfNode[u] = (int)heavyNodes.size();
            heavyNodes.push_back(u);
            isHeavy[u] = 1;
        }
    }
    int H = heavyNodes.size();

    // For each heavy node, map color -> sum of weights of edges to neighbors of that color
    vector<unordered_map<ll,ll>> heavyMap(H);
    // For each node, list of (heavyIdx, weight) of edges to heavy neighbors
    vector<vector<pair<int,ll>>> heavyNeighbors(n + 1);

    // Build heavyMap and heavyNeighbors
    for (int h = 0; h < H; h++){
        int u = heavyNodes[h];
        auto &mp = heavyMap[h];
        mp.reserve(graph[u].size() * 2);
        for (auto &e : graph[u]){
            int v = e.first;
            ll w = e.second;
            mp[ colo[v] ] += w;
            heavyNeighbors[v].push_back({h, w});
        }
    }

    // compute initial answer
    ll ans = 0;
    for (int u = 1; u <= n; u++){
        for (auto &e: graph[u]){
            int v = e.first;
            ll w = e.second;
            if (v > u && colo[u] != colo[v]) ans += w;
        }
    }

    // process queries
    while(q--){
        ll no, co;
        cin >> no >> co;
        ll currco = colo[no];
        if (currco == co){
            cout << ans << "\n";
            continue;
        }

        ll sum1 = 0, sum2 = 0;
        if (isHeavy[no]){
            int idx = heavyIdxOfNode[no];
            auto &mp = heavyMap[idx];
            auto it1 = mp.find(currco);
            if (it1 != mp.end()) sum1 = it1->second;
            auto it2 = mp.find(co);
            if (it2 != mp.end()) sum2 = it2->second;
        } else {
            // light node: scan its adjacency
            for (auto &e : graph[no]){
                int v = e.first;
                ll w = e.second;
                if (colo[v] == currco) sum1 += w;
                else if (colo[v] == co) sum2 += w;
            }
        }

        // update answer
        ans += sum1 - sum2;

        // update heavyMaps of every heavy neighbor of 'no'
        for (auto &hn : heavyNeighbors[no]){
            int hidx = hn.first;
            ll w   = hn.second;
            heavyMap[hidx][currco] -= w;
            heavyMap[hidx][co]    += w;
        }

        // finally update color
        colo[no] = co;
        cout << ans << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}