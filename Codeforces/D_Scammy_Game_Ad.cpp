#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solve(){
    ll n; cin >> n;

    vector<pair<char,char>> op(n);
    vector<pair<ll,ll>> val(n);

    for(ll i = 0; i < n; i++){
        char l, r;
        ll a, b;
        cin >> l >> a >> r >> b;
        op[i] = {l, r};
        val[i] = {a, b};
    }

    vector<ll> dp(n + 1, 0);

    for(ll i = n - 1; i >= 0; i--){
        char l = op[i].first, r = op[i].second;

        if(l == '+' && r == '+') dp[i] = dp[i + 1];
        else if(l == '+' && r == 'x') dp[i] = 1;
        else if(l == 'x' && r == '+') dp[i] = 0;
        else {
            if(val[i].first < val[i].second) dp[i] = 1;
            else if(val[i].first > val[i].second) dp[i] = 0;
            else dp[i] = dp[i + 1];
        }
    }

    ll ans1 = 1, ans2 = 1;

    for(ll i = 0; i < n; i++){
        ll val1 = val[i].first, val2 = val[i].second;
        char l = op[i].first, r = op[i].second;
        ll cnt = 0;

        if(l == '+' && r == '+'){
            cnt = val1 + val2;
        }
        else if(l == '+' && r == 'x'){
            cnt = val1 + (val2 - 1) * ans2;
        }
        else if(l == 'x' && r == '+'){
            cnt = (val1 - 1) * ans1 + val2;
        }
        else{
            cnt = (val1 - 1) * ans1 + (val2 - 1) * ans2;
        }

        if(dp[i + 1] == 0) ans1 += cnt;
        else ans2 += cnt;
    }

    return ans1 + ans2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;
    while(t--){
        cout << solve() << '\n';
    }
    return 0;
}
