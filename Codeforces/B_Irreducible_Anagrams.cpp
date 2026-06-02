#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(){
    string s; cin >> s;
    int n = (int)s.length();
    int q; cin >> q;

    
    vector<array<int,26>> pref(n+1);
    pref[0].fill(0);
    for(int i = 0; i < n; ++i){
        pref[i+1] = pref[i];
        pref[i+1][s[i]-'a']++;
    }

    while(q--){
        int l, r; cin >> l >> r;
        --l; --r; 

        if (l == r) {
            cout << "Yes\n";
            continue;
        }

       
        int distinct = 0;
        for(int c = 0; c < 26; ++c){
            if (pref[r+1][c] - pref[l][c] > 0) ++distinct;
        }

        if (distinct >= 3) {
            cout << "Yes\n";
        } else if (distinct == 1) {
            cout << "No\n";
        } else { 
            if (s[l] != s[r]) cout << "Yes\n";
            else cout << "No\n";
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
