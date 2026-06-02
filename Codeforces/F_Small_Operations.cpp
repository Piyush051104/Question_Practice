#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using ull = unsigned long long;

vector<ll> primes;
void sieve(int n = 10000) {
    vector<char> isprime(n+1,1);
    isprime[0]=isprime[1]=0;
    for(int i=2;i<=n;i++){
        if(isprime[i]){
            primes.push_back(i);
            if((ll)i*i<=n) for(int j=i*i;j<=n;j+=i) isprime[j]=0;
        }
    }
}

vector<ll> prime_factors(ll n) {
    vector<ll> res;
    for (ll p : primes) {
        if (p * p > n) break;
        while (n % p == 0) {
            res.push_back(p);
            n /= p;
        }
    }
    if (n > 1) res.push_back(n);
    return res;
}

int greedy_ffd(const vector<ll>& a, ll k) {
    vector<ll> bins;
    for (ll x : a) {
        bool placed = false;
        for (ll &b : bins) {
            if (b <= k / x) { b *= x; placed = true; break; }
        }
        if (!placed) bins.push_back(x);
    }
    return (int)bins.size();
}

struct KeyHasher {
    static void append_num(string &s, ull v) {
       
        char buf[32];
        int len = 0;
        if (v == 0) buf[len++] = '0';
        else {
            ull t = v;
            char rev[32]; int ridx = 0;
            while (t) { rev[ridx++] = char('0' + (t % 10)); t /= 10; }
            for (int i = ridx-1; i >= 0; --i) buf[len++] = rev[i];
        }
        buf[len++] = '#';
        s.append(buf, buf + len);
    }
};

bool can_pack_with_m(const vector<ll>& a, ull k, int m, vector<ull>& bins, int idx, unordered_set<string>& seen) {
    if (idx == (int)a.size()) return true;
    ull x = (ull)a[idx];
    string key;
    key.reserve(m*6 + 10);
    key.push_back(char('A' + min(25, idx%26))); 
   
    vector<ull> rem(m);
    for (int i = 0; i < m; ++i) rem[i] = bins[i];
    sort(rem.begin(), rem.end());
    for (ull v : rem) KeyHasher::append_num(key, v);
    auto it = seen.find(key);
    if (it != seen.end()) return false;
    seen.insert(key);

    for (int i = 0; i < m; ++i) {
        ull cur = bins[i];
        if (cur > k / x) {
            if (cur == 1) break; 
            continue;
        }
        bins[i] = cur * x;
        if (can_pack_with_m(a, k, m, bins, idx + 1, seen)) return true;
        bins[i] = cur;
        if (cur == 1) break; 
    }
    return false;
}

int min_operations(vector<ll> a, ll k) {
    if (a.empty()) return 0;
    sort(a.begin(), a.end(), greater<ll>());
    int upper = greedy_ffd(a, k);
    long double totlog = 0;
    for (ll v : a) totlog += log((long double)v);
    long double logk = log((long double)k);
    int lower = (int)ceil(totlog / logk - 1e-12L);
    if (lower < 1) lower = 1;
    for (int m = lower; m <= upper; ++m) {
        vector<ull> bins(m, 1);
        unordered_set<string> seen;
        seen.reserve(1<<10);
        if (can_pack_with_m(a, (ull)k, m, bins, 0, seen)) return m;
    }
    return upper;
}

ll solve(){
    ll x,y,k; cin >> x >> y >> k;
    if(x == y) return 0;
    if(x != y && k == 1) return -1;
    while(true){
        ll g = std::gcd(x,y);
        if(g == 1) break;
        x /= g; y /= g;
    }
    vector<ll> p1 = prime_factors(x);
    vector<ll> p2 = prime_factors(y);
    for(auto &i:p1) if(i > k) return -1;
    for(auto &i:p2) if(i > k) return -1;
    int ans1 = min_operations(p1,k);
    int ans2 = min_operations(p2,k);
    return (ll)ans1 + (ll)ans2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve(10000);
    int t; if(!(cin>>t)) return 0;
    while(t--){
        cout << solve() << '\n';
    }
    return 0;
}
