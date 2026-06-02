#include <bits/stdc++.h>
using namespace std;

vector<pair<long long,long long>> findOverlappingTimes(vector<pair<long long,long long>>& iv) {
    if (iv.empty()) return {};
    sort(iv.begin(), iv.end());
    vector<pair<long long,long long>> merged;
    long long s = iv[0].first, e = iv[0].second;
    for (int i = 1; i < iv.size(); i++) {
        if (iv[i].first <= e) {
            e = max(e, iv[i].second);
        } else {
            merged.emplace_back(s, e);
            s = iv[i].first;
            e = iv[i].second;
        }
    }
    merged.emplace_back(s, e);
    return merged;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cols;
    cin >> n >> cols; // cols will be 2
    vector<pair<long long,long long>> intervals(n);
    for (int i = 0; i < n; i++) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    auto ans = findOverlappingTimes(intervals);
    for (auto &p : ans) {
        cout << p.first << " " << p.second << "\n";
    }
    return 0;
}