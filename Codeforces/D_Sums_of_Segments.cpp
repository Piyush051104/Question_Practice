#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    ll n; cin >> n;
    vector<ll> v(n + 1), prefix(n + 1, 0);
    for(ll i = 1; i <= n; i++){
        cin >> v[i];
        prefix[i] = prefix[i - 1] + v[i];
    }

    vector<ll> suppref(n + 1, 0);
    for(ll i = 1; i <= n; i++){
        suppref[i] = suppref[i - 1] + prefix[i];
    }

    vector<ll> block(n + 1, 0);
    for(ll i = 1; i <= n; i++){
        block[i] = (suppref[n] - suppref[i - 1]) - (n - i + 1) * prefix[i - 1];
    }

    vector<ll> blocksize(n + 1, 0);
    for(ll i = 1; i <= n; i++){
        blocksize[i] = blocksize[i - 1] + (n - i + 1);
    }

    vector<ll> blockprefsum(n + 1, 0);
    for(ll i = 1; i <= n; i++){
        blockprefsum[i] = blockprefsum[i - 1] + block[i];
    }

    auto sum_in_block = [&](ll b, ll l, ll r){
        ll L = b + l - 1;
        ll R = b + r - 1;
        return (suppref[R] - suppref[L - 1]) - (r - l + 1) * prefix[b - 1];
    };

    ll q; cin >> q;
    while(q--){
        ll l, r; cin >> l >> r;
        ll in1 = lower_bound(blocksize.begin(), blocksize.end(), l) - blocksize.begin();
        ll in2 = lower_bound(blocksize.begin(), blocksize.end(), r) - blocksize.begin();

        ll pos1 = l - blocksize[in1 - 1];
        ll pos2 = r - blocksize[in2 - 1];

        ll ans = 0;
        if(in1 == in2){
            ans = sum_in_block(in1, pos1, pos2);
        }else{
            ans += sum_in_block(in1, pos1, n - in1 + 1);
            if(in2 - in1 > 1){
                ans += blockprefsum[in2 - 1] - blockprefsum[in1];
            }
            ans += sum_in_block(in2, 1, pos2);
        }
        cout << ans << '\n';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
