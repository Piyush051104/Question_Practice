#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; if(!(cin >> t)) return 0;
    while(t--){
        ll n,q; cin >> n >> q;
        vector<ll> a(n+1);
        for(ll i=1;i<=n;i++) cin >> a[i];
        ll L,R; cin >> L >> R;
        vector<ll> P(n+1,0), X(n+1,0);
        for(ll i=1;i<=n;i++){ P[i]=P[i-1]+a[i]; X[i]=X[i-1]^a[i]; }
        ll bestVal = LLONG_MIN, bestL = L, bestR = L;
        ll bestLen = R - L + 1;
        for(ll l = L; l <= R; ++l){
            ll target = (P[R] - P[l-1]) - (X[R] ^ X[l-1]);
            ll low = l, high = R, ans = R;
            while(low <= high){
                ll mid = (low + high) >> 1;
                ll cur = (P[mid] - P[l-1]) - (X[mid] ^ X[l-1]);
                if(cur < target) low = mid + 1;
                else { ans = mid; high = mid - 1; }
            }
            ll len = ans - l + 1;
            if(target > bestVal || (target == bestVal && (len < bestLen || (len == bestLen && l < bestL)))){
                bestVal = target;
                bestL = l;
                bestR = ans;
                bestLen = len;
            }
        }
        cout << bestL << " " << bestR << '\n';
    }
    return 0;
}
