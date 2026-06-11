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
ll powermod(ll x, ll y, ll p){ll res = 1;x = x % p;if (x == 0) return 0;while (y > 0){if (y & 1)res = (res*x) % p;y = y>>1;x = (x*x) % p;}return res;}

static inline ll enc(int p, int q, int base){
    return 1LL * p * base + q;
}

bool check_good_value(ll y, int p, int q, unordered_map<ll,int> &firstPos, unordered_map<ll,int> &lastPos){
    if(firstPos[y] == lastPos[y]) return true;
    int l = firstPos[y], r = lastPos[y];
    if(q < l || q > r) return false;
    if(q == l) return p == r + 1;
    if(q == r) return p == l - 1;
    return false;
}

unordered_set<ll> gen_pairs(ll v, vector<ll> &a, unordered_map<ll,int> &freq, unordered_map<ll,int> &firstPos, unordered_map<ll,int> &lastPos){
    int n = (int)a.size();
    int c = freq[v];
    unordered_set<ll> st;
    if(c <= 0) return st;

    vector<int> pref(n + 1, 0);
    loop(i, n) pref[i + 1] = pref[i] + (a[i] == v);

    int cur = 0;
    loop(i, c) cur += (a[i] == v);

    for(int L = 0; L + c <= n; L++){
        if(cur == c - 1){
            int left = pref[L];
            if(left <= 1){
                int R = L + c - 1;
                int lo = L, hi = R;
                while(lo < hi){
                    int mid = (lo + hi) >> 1;
                    if(pref[mid + 1] - pref[L] == mid - L + 1) lo = mid + 1;
                    else hi = mid;
                }
                int q = lo;
                int p = (left == 1 ? firstPos[v] : lastPos[v]);
                st.insert(enc(p, q, n + 1));
            }
        }
        if(L + c < n){
            cur += (a[L + c] == v) - (a[L] == v);
        }
    }
    return st;
}

bool solve(){
    ll n;
    cin >> n;
    vector<ll> a(n);
    loop(i, n) cin >> a[i];

    unordered_map<ll,int> blockCnt, freq, firstPos, lastPos;
    blockCnt.reserve(n * 2);
    freq.reserve(n * 2);
    firstPos.reserve(n * 2);
    lastPos.reserve(n * 2);

    for(int i = 0; i < (int)n; ){
        int j = i;
        while(j < (int)n && a[j] == a[i]) j++;
        ll v = a[i];
        blockCnt[v]++;
        freq[v] += (j - i);
        if(!firstPos.count(v)) firstPos[v] = i;
        lastPos[v] = j - 1;
        i = j;
    }

    vector<ll> bad;
    for(auto &it : blockCnt){
        if(it.second > 1) bad.push_back(it.first);
    }

    if((int)bad.size() > 2) return false;
    if((int)bad.size() == 0) return true;

    if((int)bad.size() == 1){
        ll x = bad[0];
        auto cand = gen_pairs(x, a, freq, firstPos, lastPos);
        for(auto code : cand){
            int p = (int)(code / (n + 1));
            int q = (int)(code % (n + 1));
            ll y = a[q];
            if(y != x && check_good_value(y, p, q, firstPos, lastPos)) return true;
        }
        return false;
    }

    ll x = bad[0], y = bad[1];
    auto sx = gen_pairs(x, a, freq, firstPos, lastPos);
    auto sy = gen_pairs(y, a, freq, firstPos, lastPos);

    if(sx.size() > sy.size()){
        for(auto code : sy){
            int p = (int)(code / (n + 1));
            int q = (int)(code % (n + 1));
            if(sx.count(enc(q, p, n + 1))) return true;
        }
    }else{
        for(auto code : sx){
            int p = (int)(code / (n + 1));
            int q = (int)(code % (n + 1));
            if(sy.count(enc(q, p, n + 1))) return true;
        }
    }

    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while(t--){
        cout << (solve() ? "YES" : "NO") << '\n';
    }
    return 0;
}