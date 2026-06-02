#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int n; ll Ax, Ay, Bx, By;
        cin >> n >> Ax >> Ay >> Bx >> By;
        vector<ll> x(n), y(n);
        for(int i=0;i<n;i++) cin >> x[i];
        for(int i=0;i<n;i++) cin >> y[i];

        map<ll, pair<ll,ll>> mp;
        for(int i=0;i<n;i++){
            if(!mp.count(x[i])) mp[x[i]] = {y[i], y[i]};
            else{
                mp[x[i]].first = min(mp[x[i]].first, y[i]);
                mp[x[i]].second = max(mp[x[i]].second, y[i]);
            }
        }

        vector<ll> X;
        vector<pair<ll,ll>> seg;
        X.push_back(Ax);
        seg.push_back({Ay, Ay});
        for(auto &it: mp){
            X.push_back(it.first);
            seg.push_back(it.second);
        }
        X.push_back(Bx);
        seg.push_back({By, By});

        int m = X.size();
        const ll INF = (ll)4e18;
        ll dpL = 0, dpR = 0;

        for(int i=0;i+1<m;i++){
            ll dx = X[i+1] - X[i];
            ll L1 = seg[i].first, R1 = seg[i].second;
            ll L2 = seg[i+1].first, R2 = seg[i+1].second;
            ll D = R2 - L2;

            ll ndpL = INF, ndpR = INF;

            // from ending at L1
            {
                ll base = dpL + dx;
                ndpL = min(ndpL, base + llabs(L1 - R2) + D);
                ndpR = min(ndpR, base + llabs(L1 - L2) + D);
            }
            // from ending at R1
            {
                ll base = dpR + dx;
                ndpL = min(ndpL, base + llabs(R1 - R2) + D);
                ndpR = min(ndpR, base + llabs(R1 - L2) + D);
            }

            dpL = ndpL;
            dpR = ndpR;
        }

        cout << min(dpL, dpR) << '\n';
    }
    return 0;
}
