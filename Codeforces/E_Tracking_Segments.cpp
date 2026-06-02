#include <bits/stdc++.h>
using namespace std;

int main() {
    long long m, n;
    if (!(cin >> m >> n)) return 0;

    int a = ((m % 11) + 11) % 11;
    int b = ((n % 11) + 11) % 11;

    if (n == 0) {
        cout << (a == 0 ? 0 : -1) << '\n';
        return 0;
    }

    if (b == 0) {
      
        if (a == 0) cout << 0 << '\n';
        else cout << -1 << '\n';
        return 0;
    }

  
    int inv = -1;
    for (int x = 1; x < 11; ++x) if ((b * x) % 11 == 1) { inv = x; break; }

    int k = ((11 - a) % 11) * inv % 11;

    if (k <= n) cout << k << '\n';
    else cout << -1 << '\n'; 
    return 0;
}
