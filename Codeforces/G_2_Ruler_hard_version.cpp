#include <bits/stdc++.h>
using namespace std;

// Sieve to get all primes up to n
vector<int> get_primes(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= n; ++i)
        if (is_prime[i]) primes.push_back(i);
    return primes;
}
int get_ans(int N,vector<int>P){
    vector<int> primes = get_primes(N);
    int M = primes.back();   // largest prime ≤ N

    // check frozen tail (positions M+1 .. N must already be correct)
    for (int i = M; i < N; ++i) {          // 0‑based index i corresponds to 1‑based position i+1
        if (P[i] != i + 1) {
            return -1;
        }
    }

    // work only on the first M elements (they form a permutation of 1..M)
    vector<int> cur(P.begin(), P.begin() + M);
    vector<int> target(M);
    iota(target.begin(), target.end(), 1);

    // BFS from cur to target
    queue<vector<int>> q;
    map<vector<int>, int> dist;
    dist[cur] = 0;
    q.push(cur);

    while (!q.empty()) {
        auto v = q.front(); q.pop();
        int d = dist[v];
        if (v == target) {
            return d;
            
        }
        for (int p : primes) {
            if (p > M) break;               
            auto nxt = v;
            reverse(nxt.begin(), nxt.begin() + p);
            if (!dist.count(nxt)) {
                dist[nxt] = d + 1;
                q.push(nxt);
            }
        }
    }
    return -1;
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; ++i) cin >> P[i];
    int ans = get_ans(N,P);

    cout << ans << endl;
    
}