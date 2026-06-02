#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<string> g(n);
        for (int i = 0; i < n; i++) cin >> g[i];

        int N = n * m;
        vector<char> type(N);
        vector<int> target(N, -1);
        vector<int> deg(N, 0);      
        vector<char> removed(N, 0);

        queue<int> q;

        auto id = [m](int r, int c) {
            return r * m + c;
        };

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                int u = id(r, c);
                type[u] = g[r][c];

                if (g[r][c] == '?') {
                    int cnt = 0;
                    if (r > 0) cnt++;
                    if (r + 1 < n) cnt++;
                    if (c > 0) cnt++;
                    if (c + 1 < m) cnt++;
                    deg[u] = cnt;

                    if (cnt == 0) {
                        removed[u] = 1;
                        q.push(u);
                    }
                } else {
                    int nr = r, nc = c;
                    if (g[r][c] == 'U') nr--;
                    if (g[r][c] == 'D') nr++;
                    if (g[r][c] == 'L') nc--;
                    if (g[r][c] == 'R') nc++;

                    if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                        removed[u] = 1;
                        q.push(u);
                    } else {
                        target[u] = id(nr, nc);
                    }
                }
            }
        }

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            int x = q.front();
            q.pop();

            int r = x / m, c = x % m;

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;

                int y = id(nr, nc);
                if (removed[y]) continue;

                if (type[y] == '?') {
                    deg[y]--;
                    if (deg[y] == 0) {
                        removed[y] = 1;
                        q.push(y);
                    }
                } else {
                    if (target[y] == x) {
                        removed[y] = 1;
                        q.push(y);
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < N; i++) {
            if (!removed[i]) ans++;
        }

        cout << ans << '\n';
    }

    return 0;
}