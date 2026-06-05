#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    vector<int> vis(n + 1, 0), order;
    order.reserve(n);

    for (int s = 1; s <= n; s++) {
        if (vis[s]) continue;
        stack<pair<int,int>> st;
        st.push({s, 0});
        vis[s] = 1;

        while (!st.empty()) {
            int u = st.top().first;
            int &idx = st.top().second;

            if (idx + 1 <= (int)g[u].size() ) {
                int v = g[u][idx++];
                if (!vis[v]) {
                    vis[v] = 1;
                    st.push({v, 0});
                }
            }
            else{
                order.push_back(u);
                st.pop();
            }
        }
    }

    vector<int> comp(n + 1, 0);
    int k = 0;

    for (int i = n - 1; i >= 0; i--) {
        int s = order[i];
        if (comp[s]) continue;
        k++;

        stack<int> st;
        st.push(s);
        comp[s] = k;

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            for (int v : rg[u]) {
                if (!comp[v]) {
                    comp[v] = k;
                    st.push(v);
                }
            }
        }
    }

    cout << k << '\n';
    for (int i = 1; i <= n; i++) {
        cout << comp[i] << ' ';
    }
    cout << '\n';

    return 0;
}