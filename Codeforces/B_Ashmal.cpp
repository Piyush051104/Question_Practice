#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<ll,ll> best_pair(ll K){
    if(K == 0) return {0,0};
    int msb = 0;
    for(int i = 0; i < 31; ++i) if((K >> i) & 1) msb = i;
    int B = msb + 1;
    vector memo(B, vector(2, vector<ll>(2, -1)));
    vector choice(B, vector(2, vector<pair<int,int>>(2, {-1,-1})));
    function<ll(int,int,int)> dp = [&](int pos, int ta, int tb)->ll{
        if(pos < 0) return 0;
        ll &res = memo[pos][ta][tb];
        if(res != -1) return res;
        int kb = (K >> pos) & 1;
        ll best = -1;
        pair<int,int> bestChoice = {-1,-1};
        vector<pair<int,int>> opts;
        if(kb == 0) opts = {{0,0},{1,1}}; else opts = {{0,1},{1,0}};
        for(auto &pr : opts){
            int a = pr.first, b = pr.second;
            if(ta && a > kb) continue;
            if(tb && b > kb) continue;
            int nta = ta && (a == kb);
            int ntb = tb && (b == kb);
            ll add = (a & b) ? (1LL << pos) : 0;
            ll val = add + dp(pos-1, nta, ntb);
            if(val > best){
                best = val;
                bestChoice = {a,b};
            }
        }
        res = best;
        choice[pos][ta][tb] = bestChoice;
        return res;
    };
    dp(msb,1,1);
    ll A=0, Bv=0;
    int ta=1, tb=1;
    for(int pos = msb; pos >= 0; --pos){
        auto pr = choice[pos][ta][tb];
        int ai = pr.first, bi = pr.second;
        if(ai == -1) ai = 0, bi = 0;
        A = (A << 1) | ai;
        Bv = (Bv << 1) | bi;
        int kb = (K >> pos) & 1;
        ta = ta && (ai == kb);
        tb = tb && (bi == kb);
    }
    return {A,Bv};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if(!(cin >> t)) return 0;
    while(t--){
        ll n; int k;
        cin >> n >> k;
        vector<ll> ans;
        if(k % 2 == 1){
            ans.assign(k, n);
        } else {
            if(k == 2){
                auto p = best_pair(n);
                ans = {p.first, p.second};
            } else {
                ans.assign(k-2, n);
                auto p = best_pair(n);
                ans.push_back(p.first);
                ans.push_back(p.second);
            }
        }
        for(int i = 0; i < (int)ans.size(); ++i){
            if(i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
