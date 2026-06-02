#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int mod = 1000000007;
ll idx = 0;
ll mini = 1e9;
void dfs(int i, vector<int>&adj, vector<int>&vis, vector<ll>&c, vector<int>&order) {
    vis[i] = 1;
    int par = adj[i];
   // cout << i <<" " <<par << endl;
    order.push_back(i);
    if(c[i] <= mini) {
        mini = c[i];
        idx = i;
    }
    if(vis[par] == 0) {
         dfs(par, adj, vis, c, order);
    }
}
int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    cin >> t;
    while(t--)
    {
        ll n;
        cin >> n;
        vector<int>par(n + 1);
        vector<int>inedges(n + 1);
        vector<ll>c(n + 1);
        for(int i = 1; i <= n; i++) {
            cin >> par[i];
            inedges[par[i]]++;
        }
        for(int i = 1; i <= n; i++) {
            cin >> c[i];
        }
        
        queue<int>q; 
        vector<int>vis(n + 1);
        vector<int> ans;
        for(int i = 1; i <= n; i++) {
            if(inedges[i] == 0) {
                q.push(i);

            }
        }

        while(!q.empty()) {
            int curr = q.front();
            vis[curr] = 1;
            inedges[par[curr]]--;
            ans.push_back(curr);
            q.pop();
            if(inedges[par[curr]] == 0) {
                q.push(par[curr]);
            }

        }
        for(int i = 1; i <= n; i++) {
            if(vis[i] == 0) {
                idx = -1;
                vector<int>order;
                mini = 1e9;
                dfs(i, par, vis, c, order);
                int id = -1;
                for(int j = 0; j < order.size(); j++) {
                    if(order[j] == idx)  {
                        id = j;
                        break;
                    }
                    
                }
                for(int j = id + 1; j < order.size(); j++) {
                    ans.push_back(order[j]);
                }
                for(int j = 0; j < id; j++) {
                    ans.push_back(order[j]);
                }
                ans.push_back(idx);
                
            }
        }
        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i] <<' ';
        }
        cout << '\n';
    }
}