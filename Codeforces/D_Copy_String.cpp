#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    const int B = 20;
    const int MAXM = 1 << B; // 2^20

    while (T--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;

        // map mask -> smallest index (1-based)
        unordered_map<int,int> mp;
        mp.reserve(k*2);

        for (int i = 1; i <= k; ++i) {
            string t; cin >> t;
            int mask = 0;
            for (char c : t) mask |= (1 << (c - 'a'));
            // store smallest index for that mask
            if (!mp.count(mask) || i < mp[mask]) mp[mask] = i;
        }

        // sup_index[mask] = index of some dictionary mask D that is a supermask of mask
        // initialize with -1, then set exactly-present masks, then run SOS DP to propagate superset indices.
        vector<int> sup_index(MAXM, -1);
        for (auto &p : mp) sup_index[p.first] = p.second;

        // SOS DP over supersets:
        for (int b = 0; b < B; ++b) {
            for (int mask = 0; mask < MAXM; ++mask) {
                if (((mask >> b) & 1) == 0) {
                    int with = mask | (1 << b);
                    if (sup_index[with] != -1 && sup_index[mask] == -1) {
                        sup_index[mask] = sup_index[with];
                    }
                }
            }
        }

        vector<int> ans(n, 0);
        int i = 0;
        while (i < n) {
            int mask = 0;
            int bestLen = 0;
            // Only need to check up to 20 chars ahead since only 20 bits exist.
            int limit = min(n, i + B);
            for (int j = i; j < limit; ++j) {
                mask |= (1 << (s[j] - 'a'));
                if (sup_index[mask] != -1) {
                    bestLen = j - i + 1; // valid segment length
                }
            }
            ans[i] = bestLen;
            if (bestLen == 0) ++i;
            else i += bestLen;
        }

        // print result
        for (int idx = 0; idx < n; ++idx) {
            if (idx) cout << ' ';
            cout << ans[idx];
        }
        cout << '\n';
    }

    return 0;
}