#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long modpow(long long a, long long e){
    long long r = 1;
    while(e){
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
   
    const int MAXN = 55;
    vector<long long> fact(MAXN), invfact(MAXN);
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) fact[i] = fact[i-1] * i % MOD;
    invfact[MAXN-1] = modpow(fact[MAXN-1], MOD-2);
    for (int i = MAXN-2; i >= 0; --i) invfact[i] = invfact[i+1] * (i+1) % MOD;

    auto C = [&](int n, int k)->long long{
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % MOD * invfact[n-k] % MOD;
    };

    while(t--){
        int n;
        cin >> n;
        vector<long long> a(n+1);
        long long total = 0;
        for (int i = 0; i <= n; ++i){
            cin >> a[i];
            total += a[i];
        }
        long long a0 = a[0];
        vector<long long> persons;
        for (int i = 1; i <= n; ++i) persons.push_back(a[i]);

        long long q = total / n;
        int r = (int)(total % n);

       
        long long base = 0;
        int cntL = 0;
        for (long long x : persons){
            if (x <= q) cntL++;
            base += max(0LL, q - x);
        }
        long long x_needed = a0 - base; 
        if (x_needed < 0 || x_needed > r){
            cout << 0 << "\n";
            continue;
        }
        int x = (int)x_needed;
        int cntH = n - cntL;
        
        if (r - x < 0 || r - x > cntH){
            cout << 0 << "\n";
            continue;
        }
        long long ways = C(cntL, x) * C(cntH, r - x) % MOD;
        ways = ways * fact[r] % MOD;
        ways = ways * fact[n - r] % MOD;
        cout << ways % MOD << "\n";
    }
    return 0;
}
