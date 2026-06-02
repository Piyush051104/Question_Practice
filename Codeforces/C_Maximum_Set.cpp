#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
const int MAXF = 1000000;
vector<ll> fact, invfact;

ll modpow(ll a, ll e){
    ll r = 1;
    a %= MOD;
    while(e){
        if(e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

void init_fact(){
    if(!fact.empty()) return;
    fact.assign(MAXF+1, 0);
    invfact.assign(MAXF+1, 0);
    fact[0] = 1;
    for(int i=1;i<=MAXF;i++) fact[i] = fact[i-1] * i % MOD;
    invfact[MAXF] = modpow(fact[MAXF], MOD-2);
    for(int i=MAXF-1;i>=0;i--) invfact[i] = invfact[i+1] * (i+1) % MOD;
}

ll ncr(ll n, ll r){
    if(r < 0 || r > n) return 0;
    if(n < 0 || n > MAXF) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n-r] % MOD;
}

void solve(){
    init_fact();
    ll l,r; if(!(cin >> l >> r)) return;
    ll st = l;
    ll cnt = 1;
    while(st * 2 <= r){
        st = st * 2;
        cnt++;
    }
    ll ans = 0;
    ll pr = 3;
    ll used = 0;
    ll val = (cnt-1 >= 0) ? (1LL << (cnt - 1)) : 1;
    if(val == 0) val = 1;
    ll a = r / val;
    ll diff = a - l + 1;
    if(diff > 0){
        ll req = ncr(cnt, cnt - used);
        ans = (ans + (req * (diff % MOD)) % MOD) % MOD;
    }
    while(true){
        if(used == cnt){
            pr++;
            used = 0;
        }
        used++;
        if(pr - 1 == 0) break;
        ll part = val / (pr - 1);
        ll tmp = part * pr;
        val = tmp;
        if(val <= 0) break;
        if(val > r) break;
        a = r / val;
        diff = a - l + 1;
        if(diff <= 0) break;
        if(used > cnt - 1) break;
        ll req = ncr(cnt - 1, cnt - 1 - used);
        ans = (ans + (req * (diff % MOD)) % MOD) % MOD;
    }
    cout << cnt << " " << ans % MOD << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}