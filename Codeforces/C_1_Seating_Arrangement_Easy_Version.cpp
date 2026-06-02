#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,x,se;
string s;

ll find(ll in,ll seat,vector<vector<ll>>&dp){
    if(seat < 0 || seat > x || seat > in) return -(ll)1e18;

    if(in == 0){
        return (seat == 0 ? 0 : -(ll)1e18);
    }

    if(dp[in][seat] != -1) return dp[in][seat];

    ll ans = find(in - 1, seat, dp);

    char c = s[in - 1];

    if(c == 'I' || c == 'A'){
        if(seat > 0){
            ll prev = find(in - 1, seat - 1, dp);
            if(prev > -(ll)1e17){
                ans = max(ans, prev + 1);
            }
        }
    }

    if(c == 'E' || c == 'A'){
        ll prev = find(in - 1, seat, dp);

        if(prev > -(ll)1e17 && prev < seat * se){
            ans = max(ans, prev + 1);
        }
    }

    return dp[in][seat] = ans;
}

ll solve(){
    cin >> n >> x >> se >> s;

    vector<vector<ll>> dp(n + 1, vector<ll>(x + 1, -1));

    ll ans = 0;

    for(ll j = 0; j <= x; j++){
        ans = max(ans, find(n, j, dp));
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--){
        cout << solve() << '\n';
    }

    return 0;
}