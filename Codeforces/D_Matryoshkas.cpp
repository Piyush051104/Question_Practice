#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void findMostRecurrentSequences(int N, const vector<string>& keywords) {
    unordered_map<string, int> freq;
    freq.reserve(1 << 20);

    // count every substring of length >= 3
    for (auto &w : keywords) {
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

    // collect those with freq>=2, compute next permutation
    vector<string> outputs;
    outputs.reserve(freq.size());
    for (auto &p : freq) {
        if (p.second >= 2) {
            string seq = p.first;
            string nxt = seq;
            if (!next_permutation(nxt.begin(), nxt.end())) {
                nxt = seq;
            }
            outputs.push_back(move(nxt));
        }
    }

    // sort, dedupe, and print
    sort(outputs.begin(), outputs.end());
    outputs.erase(unique(outputs.begin(), outputs.end()), outputs.end());

    for (int i = 0; i < (int)outputs.size(); i++) {
        if (i) cout << ' ';
        cout << outputs[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> keywords(N);
    for (int i = 0; i < N; i++) {
        cin >> keywords[i];
    }

    findMostRecurrentSequences(N, keywords);
    return 0;
}