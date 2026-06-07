#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll cnt = 0;
    ll cost = 0;
};

ll solve() {
    ll n;
    cin >> n;

    unordered_map<ll, ll> freq;
    freq.reserve(n * 2);

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        freq[x]++;
    }

    unordered_map<ll, Node> mp;
    mp.reserve(freq.size() * 40 + 10);
    mp.max_load_factor(0.7f);

    for (auto &p : freq) {
        ll number = p.first;
        ll f = p.second;

        if (number == 1) {
            mp[1].cnt += f;
            mp[2].cnt += f;
            mp[2].cost += f;
            continue;
        }

        ll num = number;
        ll cnt = 0;

        while (num > 1) {
            mp[num].cnt += f;
            mp[num].cost += cnt * f;
            if (num & 1) num++;
            else num /= 2;
            cnt++;
        }

        mp[1].cnt += f;
        mp[1].cost += cnt * f;
    }

    ll ans = LLONG_MAX;
    for (auto &it : mp) {
        if (it.second.cnt == n) {
            ans = min(ans, it.second.cost);
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }
    return 0;
}