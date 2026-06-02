#include <bits/stdc++.h>
using namespace std;

vector<int> primes;

// sieve up to sqrt(1e8)
void sieve(int n = 10000) {
    vector<bool> isprime(n + 1, true);
    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            if ((long long)i * i <= n)
                for (int j = i * i; j <= n; j += i)
                    isprime[j] = false;
        }
    }
}

// returns all prime factors (repeated)
vector<int> prime_factors(int n) {
    vector<int> res;
    for (int p : primes) {
        if (p * p > n) break;
        while (n % p == 0) {
            res.push_back(p);
            n /= p;
        }
    }
    if (n > 1) res.push_back(n);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();   // precompute once

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        auto fac = prime_factors(n);
        for (int x : fac)
            cout << x << " ";
        cout << "\n";
    }
}
