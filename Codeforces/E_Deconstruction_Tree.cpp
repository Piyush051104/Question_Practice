#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_NODES = 3000000;
int trie[MAX_NODES][2];
int trie_cnt = 1;

void insert(int val) {
    int curr = 1;
    for (int i = 29; i >= 0; --i) {
        int bit = (val >> i) & 1;
        if (!trie[curr][bit]) {
            trie[curr][bit] = ++trie_cnt;
            trie[trie_cnt][0] = trie[trie_cnt][1] = 0;
        }
        curr = trie[curr][bit];
    }
}

int query(int val) {
    int curr = 1;
    int ans = 0;
    for (int i = 29; i >= 0; --i) {
        int bit = (val >> i) & 1;
        if (trie[curr][bit]) {
            curr = trie[curr][bit];
        } else {
            curr = trie[curr][1 ^ bit];
            ans |= (1 << i);
        }
    }
    return ans;
}

void reset_trie() {
    trie_cnt = 1;
    trie[1][0] = trie[1][1] = 0;
}

int solve(vector<int>& A, int bit) {
    if (A.empty() || bit < 0) return 0;
    
    vector<int> L, R;
    for (int x : A) {
        if ((x >> bit) & 1) R.push_back(x);
        else L.push_back(x);
    }
    
    if (L.size() % 2 == 0) {
        int max_L = 0, max_R = 0;
        if (!L.empty()) max_L = solve(L, bit - 1);
        if (!R.empty()) max_R = solve(R, bit - 1);
        return max(max_L, max_R);
    } else {
        reset_trie();
        
        if (L.size() > R.size()) swap(L, R);
        
        for (int x : L) insert(x);
        
        int min_xor = 2e9 + 7;
        for (int y : R) {
            min_xor = min(min_xor, query(y));
        }
        return min_xor;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> A(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        cin >> A[i];
    }
    
    cout << solve(A, 29) << "\n";
    
    return 0;
}