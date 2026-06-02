#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class rectangle {
public:
    int x1, y1, x2, y2;
    rectangle() {}
    rectangle(int _x1, int _y1, int _x2, int _y2) {
        x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2;
    }
};

struct Event {
    ll x;
    ll y1, y2;
    int type;
    bool operator<(Event const& o) const {
        return x < o.x;
    }
};

struct SegmentTree {
    int n;
    vector<int> cnt;
    vector<ll> len;
    vector<ll> ys;

    SegmentTree(int _n, const vector<ll>& _ys)
      : n(_n), cnt(4*_n), len(4*_n), ys(_ys) {}

    void update(int node, int l, int r, int ql, int qr, int val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            cnt[node] += val;
        } else {
            int mid = (l + r) >> 1;
            update(2*node,     l,    mid, ql, qr, val);
            update(2*node + 1, mid+1, r,   ql, qr, val);
        }
        if (cnt[node] > 0) {
            len[node] = ys[r+1] - ys[l];
        } else if (l == r) {
            len[node] = 0;
        } else {
            len[node] = len[2*node] + len[2*node + 1];
        }
    }

    void update(int y1, int y2, int val) {
        update(1, 0, n-1, y1, y2-1, val);
    }

    ll covered_length() const {
        return len[1];
    }
};

ll totalArea(int n, rectangle r[]) {
    vector<Event> ev;
    vector<ll> yvals;
    ev.reserve(2*n);
    yvals.reserve(2*n);

    for (int i = 0; i < n; ++i) {
        // entering edge
        ev.push_back({r[i].x1, r[i].y1, r[i].y2, +1});
        // leaving edge
        ev.push_back({r[i].x2, r[i].y1, r[i].y2, -1});
        yvals.push_back(r[i].y1);
        yvals.push_back(r[i].y2);
    }

    sort(yvals.begin(), yvals.end());
    yvals.erase(unique(yvals.begin(), yvals.end()), yvals.end());
    int m = (int)yvals.size();
    SegmentTree st(m - 1, yvals);

    for (auto &e : ev) {
        e.y1 = int(lower_bound(yvals.begin(), yvals.end(), e.y1) - yvals.begin());
        e.y2 = int(lower_bound(yvals.begin(), yvals.end(), e.y2) - yvals.begin());
    }

    sort(ev.begin(), ev.end());
    ll area = 0;
    ll prevX = ev.front().x;

    for (auto &e : ev) {
        ll dx = e.x - prevX;
        area += dx * st.covered_length();
        st.update((int)e.y1, (int)e.y2, e.type);
        prevX = e.x;
    }
    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<rectangle> r(n);
    for (int i = 0; i < n; ++i) {
        // read in x1, y1, x2, y2
        cin >> r[i].x1>> r[i].y1>> r[i].x2>> r[i].y2;
    }

    cout << totalArea(n, r.data()) << "\n";
    return 0;
}