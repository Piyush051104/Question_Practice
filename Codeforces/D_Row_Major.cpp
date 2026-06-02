#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll n; cin >> n;
        ll c = 1;
        while (true) {
            if (n % c != 0) break;
            ++c;
        }
        ll distinct = min(c, n);
        string s; s.reserve(n);
        for (ll i = 0; i < n; ++i) s.push_back(char('a' + (i % distinct)));
        cout << s << '\n';
    }
    return 0;
}
