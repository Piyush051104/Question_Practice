#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll mod_inv(ll a, ll mod) {
    ll x, y;
    exgcd(a, mod, x, y);
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

void solve(vector<ll>& x, vector<ll>& y) {
    ll n, ml;
    cin >> n >> ml;

    if (ml < n) {
        cout << ml << " " << n << '\n';
        return;
    }

    if (ml <= n && ml > 1) {
        cout << 1 << " " << ml << '\n';
        return;
    }

    for (ll i = 2; i <= 30; i++) {
        ll a = ml, b = x[i], m = y[i];

        ll r = (m - (a % m)) % m;
        ll g = gcd(b, m);

        if (r % g != 0) continue;

        b /= g;
        r /= g;
        m /= g;

        ll inv = mod_inv(b, m);
        ll x1 = (r * inv) % m;
        if (x1 == 0) x1 = m;

        ll y1 = (a / g + b * x1) / m;

        if (x1 <= n && y1 <= n && x1 < y1 && x1 > 0 && y1 > 0) {
            cout << x1 << " " << y1 << '\n';
            return;
        }
    }

    cout << -1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ll> x(31), y(31);
    x[0] = 1; y[0] = 0;
    x[1] = 0; y[1] = 1;
    x[2] = 2; y[2] = 3;
    x[3] = 6; y[3] = 7;

    for (ll i = 4; i <= 30; i++) {
        y[i] = 3 * y[i - 1] - 2 * y[i - 2];
        x[i] = 3 * x[i - 1] - 2 * x[i - 2];
    }

    ll t;
    cin >> t;
    while (t--) solve(x, y);
    return 0;
}