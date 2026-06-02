#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll query(ll i, ll j) {
    cout << "? " << i << " " << j << "\n";
    cout.flush();
    ll res;
    cin >> res;
    if (res == -1) exit(0);
    return res;
}

void answer(ll k) {
    cout << "! " << k << "\n";
    cout.flush();
}

void solve() {
    ll n;
    cin >> n;

    ll res = query(1, 2);
    if (res == 1) {
        answer(1);
        return;
    }

    res = query(1, 3);
    if (res == 1) {
        answer(1);
        return;
    }

    res = query(2, 3);
    if (res == 1) {
        answer(2);
        return;
    }

    for (ll i = 4; i < 2 * n; i += 2) {
        res = query(i, i + 1);
        if (res == 1) {
            answer(i);
            return;
        }
    }

    answer(2 * n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) solve();
    return 0;
}