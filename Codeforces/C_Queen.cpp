#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<string> keywords(N);
    for (int i = 0; i < N; i++) {
        cin >> keywords[i];
    }

    // Count every substring of length >= 3
    unordered_map<string, int> freq;
    freq.reserve(1 << 20);
    for (const auto &w : keywords) {
        int L = w.size();
        for (int i = 0; i < L; i++) {
            string s;
            s.reserve(L - i);
            for (int j = i; j < L; j++) {
                s.push_back(w[j]);
                if (j - i + 1 >= 3) {
                    freq[s]++;
                }
            }
        }
    }

    // Gather recurring substrings, compute next permutation
    vector<string> outputs;
    outputs.reserve(freq.size());
    for (auto &p : freq) {
        if (p.second >= 2) {
            string t = p.first;
            string nxt = t;
            if (!next_permutation(nxt.begin(), nxt.end())) {
                nxt = t;
            }
            outputs.push_back(move(nxt));
        }
    }

    // Sort and unique
    sort(outputs.begin(), outputs.end());
    outputs.erase(unique(outputs.begin(), outputs.end()), outputs.end());

    // Print in one line
    for (int i = 0; i < (int)outputs.size(); i++) {
        if (i) cout << ' ';
        cout << outputs[i];
    }
    cout << "\n";

    return 0;
}