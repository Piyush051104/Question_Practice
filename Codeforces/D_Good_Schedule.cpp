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

ll solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    loop1(1, n + 1) cin >> a[i];
    loop1(1, n + 1) cin >> b[i];

    vector<vector<int>> pos(n + 2), mask(n + 2);

    for (int i = 1; i <= n; i++) {
        if (a[i] == b[i]) {
            pos[a[i]].push_back(i);
            mask[a[i]].push_back(3);
        } else {
            pos[a[i]].push_back(i);
            mask[a[i]].push_back(1);
            pos[b[i]].push_back(i);
            mask[b[i]].push_back(2);
        }
    }

    vector<vector<int>> reach(n + 2);

    for (int v = n; v >= 1; v--) {
        reach[v].assign(pos[v].size(), 0);

        for (int j = 0; j < (int)pos[v].size(); j++) {
            if (mask[v][j] != 3) continue;

            if (v == n) {
                reach[v][j] = n;
                continue;
            }

            auto it = upper_bound(pos[v + 1].begin(), pos[v + 1].end(), pos[v][j]);
            if (it == pos[v + 1].end()) {
                reach[v][j] = n;
            } else {
                int k = (int)(it - pos[v + 1].begin());
                if (mask[v + 1][k] == 3) reach[v][j] = reach[v + 1][k];
                else reach[v][j] = pos[v + 1][k] - 1;
            }
        }
    }

    auto calc = [&](long long l, long long r, long long U) -> long long {
        if (l > r || U <= l) return 0;
        long long t = min(r, U - 1);
        if (t < l) return 0;
        long long cnt = t - l + 1;
        __int128 res = (__int128)cnt * U - (__int128)(l + t) * cnt / 2;
        return (long long)res;
    };

    ll ans = 0;
    int prev = 0;

    for (int j = 0; j < (int)pos[1].size(); j++) {
        int p = pos[1][j];
        long long U = (mask[1][j] == 3 ? (long long)reach[1][j] + 1 : (long long)p);
        ans += calc(prev + 1, p, U);
        prev = p;
    }

    ans += calc(prev + 1, n, (long long)n + 1);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int multTestQ;
    cin >> multTestQ;
    while (multTestQ--) {
        cout << solve() << '\n';
    }
    return 0;
}