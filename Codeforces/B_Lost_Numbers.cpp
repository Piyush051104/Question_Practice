#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<long long, long long> pll;
typedef priority_queue<ll> pq;
typedef priority_queue<ll, vector<ll>, greater<ll>> pqr;
#define all(a) (a).begin(), (a).end()
#define fixed(n) fixed << setprecision(n)
#define MOD 1000000007
#define loop(i,n) for(ll i=0;i<n;i++)
#define loop1(a,n) for(ll i=a;i<n;i++)
#define sum_vector(v) accumulate(v.begin(),v.end(),0LL)
#define min_value(v) *min_element(v.begin(),v.end())
#define max_value(v) *max_element(v.begin(),v.end())

ll powermod(ll x, ll y, ll p) {
    ll res = 1;
    x = x % p;
    if (x == 0) return 0;
    while (y > 0) {
        if (y & 1) res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

// clang-format off
template<typename T, typename V> bool ckmax(T &a, V b) { return (long long) a < (long long) b ? a = b, 1: 0; }
template<typename T, typename V> bool ckmin(T &a, V b) { return (long long) a > (long long) b ? a = b, 1: 0; }
template <typename T> ostream &operator<<(ostream &out, const vector<T> &v) { for (const auto &x : v) out << x << ' '; return out; }
template <typename T> istream &operator>>(istream &in, vector<T> &v) { for (auto &x : v) in >> x; return in; }
// clang-format on

template<const int mod>
struct mint {
    int val;
    constexpr mint(long long x = 0) : val((x % mod + mod) % mod) {}
    explicit operator int() const { return val; }
    mint& operator+=(const mint &b) {
        val = (val + 1LL * b.val) % mod;
        return *this;
    }
    mint& operator-=(const mint &b) {
        val -= b.val;
        if (val < 0) val += mod;
        return *this;
    }
    mint& operator*=(const mint &b) {
        val = 1LL * val * b.val % mod;
        return *this;
    }
    mint& operator/=(const mint &b) {
        return *this *= b.inv();
    }
    mint inv() const {
        return powermod(val, mod - 2, mod);
    }
    mint power(int b) const {
        mint a = *this, res(1);
        for (; b; a *= a, b /= 2)
            if (b & 1) res *= a;
        return res;
    }
    mint operator-() const { return val == 0 ? 0 : mod - val; }
    mint& operator++() { val = val == mod - 1 ? 0 : val + 1; return *this; }
    mint& operator--() { val = val == 0 ? mod - 1 : val - 1; return *this; }
    mint operator++(int32_t) { mint before = *this; ++*this; return before; }
    mint operator--(int32_t) { mint before = *this; --*this; return before; }
    friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
    friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
    friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
    friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
    friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
    friend bool operator!=(const mint &a, const mint &b) { return a.val != b.val; }
    friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }
    friend istream& operator>>(istream &in, mint &a) { return in >> a.val; }
    friend ostream& operator<<(ostream &os, const mint &a) { return os << a.val; }
};
using Mint = mint<MOD>;

vector<int> generatePalindromes(int n) {
    vector<int> pals;
    int maxLen = to_string(n).size();

    for (int d = 1; d <= maxLen; ++d) {
        int half = (d + 1) / 2;
        int start = (half == 1 ? 1 : pow(10, half - 1));
        int end = pow(10, half) - 1;

        for (int i = start; i <= end; ++i) {
            string left = to_string(i);
            string right = left;
            if (d % 2) right.pop_back();
            reverse(right.begin(), right.end());

            int pal = stoi(left + right);
            if (pal > n) continue;
            pals.push_back(pal);
        }
    }

    return pals;
}

vector<int> palindromes = generatePalindromes(40000);
int si;
vector<vector<ll>> dp;

int solve() {
    int n;
    cin >> n;
    return dp[n][si - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

   
    palindromes.insert(palindromes.begin(), 0);
    si = palindromes.size();
    dp.assign(40001, vector<ll>(si, 0));

    for (int j = 0; j < si; ++j)
        dp[0][j] = 1;


    for (int i = 1; i <= 40000; ++i) {
        for (int j = 0; j < si; ++j) {
            if (j > 0)
                dp[i][j] = dp[i][j - 1];
            if (palindromes[j] <= i)
                dp[i][j] = (dp[i][j] + dp[i - palindromes[j]][j]) % MOD;
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int ans = solve();
        cout << ans << '\n';
    }

    return 0;
}
