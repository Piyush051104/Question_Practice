#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> findOverlappingTimes(vector<vector<int>> intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return a[0] < b[0];
         });

    vector<vector<int>> merged;
    int start = intervals[0][0];
    int end   = intervals[0][1];

    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] <= end) {
            end = max(end, intervals[i][1]);
        } else {
            merged.push_back({start, end});
            start = intervals[i][0];
            end   = intervals[i][1];
        }
    }

    merged.push_back({start, end});
    return merged;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cols;
    cin >> n >> cols;
    vector<vector<int>> intervals(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> intervals[i][0] >> intervals[i][1];
    }

    auto result = findOverlappingTimes(intervals);
    for (auto &p : result) {
        cout << p[0] << " " << p[1] << "\n";
    }

    return 0;
}
