#include <bits/stdc++.h>
using namespace std;


int modInverse(int b, int mod = 5) {
    for (int x = 1; x < mod; x++) {
        if ((b * x) % mod == 1) return x;
    }
    return -1;
}

int main() {
    long long m, n;
    cin >> m >> n;

    int a = ((m % 5) + 5) % 5;
    int b = ((n % 5) + 5) % 5;

    if (b == 0) {
        if (a == 0) cout << 0 << "\n"; 
        else cout << "Not possible\n";
        return 0;
    }
    int inv = modInverse(b, 5);
    int k = ((5 - a) % 5 * inv) % 5;

    if (k <= n) cout << k << "\n";
    else cout << "Not possible\n";

    return 0;
}
