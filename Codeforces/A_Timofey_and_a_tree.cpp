#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    vector<vector<int>> graph(n+1);
    for(int i = 0; i < n-1; ++i){
        int u,v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> color(n+1);
    for(int i = 1; i <= n; ++i) cin >> color[i];

    int a = -1, b = -1;
    for(int u = 1; u <= n; ++u){
        for(int v : graph[u]){
            if(color[u] != color[v]){
                a = u; b = v;
                break;
            }
        }
        if(a != -1) break;
    }

    if(a == -1){
        cout << "YES\n1\n";
        return 0;
    }

    auto check = [&](int center)->bool{
        for(int neigh : graph[center]){
            int base = color[neigh];
            stack<pair<int,int>> st;
            st.emplace(neigh, center);
            while(!st.empty()){
                auto [u,p] = st.top(); st.pop();
                if(color[u] != base) return false;
                for(int w : graph[u]) if(w != p) st.emplace(w, u);
            }
        }
        return true;
    };

    if(check(a)){
        cout << "YES\n" << a << "\n";
    } else if(check(b)){
        cout << "YES\n" << b << "\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
