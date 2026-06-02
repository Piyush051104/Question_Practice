#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        vector<vector<int>> g(n+1), gr(n+1);
        vector<pair<int,int>> edges;
        for(int i=0;i<m;i++){
            int a,b; cin >> a >> b;
            g[a].push_back(b);
            gr[b].push_back(a);
            edges.push_back({a,b});
        }

        vector<int> order;
        vector<char> vis(n+1,0);
        for(int i=1;i<=n;i++){
            if(vis[i]) continue;
            stack<pair<int,int>> st;
            st.push({i,-1});
            while(!st.empty()){
                auto [v,idx]=st.top(); st.pop();
                if(idx==-1){
                    if(vis[v]) continue;
                    vis[v]=1;
                    st.push({v,0});
                    for(int u:g[v]) if(!vis[u]) st.push({u,-1});
                }else{
                    order.push_back(v);
                }
            }
        }

        vector<int> comp(n+1,-1);
        int cc=0;
        for(int i=(int)order.size()-1;i>=0;i--){
            int v=order[i];
            if(comp[v]!=-1) continue;
            stack<int> st;
            st.push(v);
            comp[v]=cc;
            while(!st.empty()){
                int u=st.top(); st.pop();
                for(int w:gr[u]){
                    if(comp[w]==-1){
                        comp[w]=cc;
                        st.push(w);
                    }
                }
            }
            cc++;
        }

        vector<int> sz(cc,0);
        vector<char> self(cc,0);
        for(int i=1;i<=n;i++) sz[comp[i]]++;
        for(auto &e:edges){
            if(e.first==e.second && comp[e.first]==comp[e.second])
                self[comp[e.first]]=1;
        }

        vector<pair<int,int>> ce;
        for(auto &e:edges){
            int u=comp[e.first], v=comp[e.second];
            if(u!=v) ce.push_back({u,v});
        }
        sort(ce.begin(),ce.end());
        ce.erase(unique(ce.begin(),ce.end()),ce.end());

        vector<vector<int>> cg(cc);
        for(auto &p:ce) cg[p.first].push_back(p.second);

        vector<char> reach(cc,0);
        int s=comp[1];
        queue<int> q;
        reach[s]=1;
        q.push(s);
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v:cg[u]){
                if(!reach[v]){
                    reach[v]=1;
                    q.push(v);
                }
            }
        }

        vector<char> cyc(cc,0);
        for(int i=0;i<cc;i++){
            if(sz[i]>1 || self[i]) cyc[i]=1;
        }

        vector<char> inf(cc,0);
        for(int i=0;i<cc;i++){
            if(reach[i] && cyc[i]){
                inf[i]=1;
                q.push(i);
            }
        }
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v:cg[u]){
                if(reach[v] && !inf[v]){
                    inf[v]=1;
                    q.push(v);
                }
            }
        }

        vector<int> indeg(cc,0), ways(cc,0);
        for(int u=0;u<cc;u++){
            if(!reach[u] || inf[u]) continue;
            for(int v:cg[u]){
                if(reach[v] && !inf[v]) indeg[v]++;
            }
        }

        if(reach[s] && !inf[s]) ways[s]=1;
        for(int i=0;i<cc;i++){
            if(reach[i] && !inf[i] && indeg[i]==0) q.push(i);
        }

        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v:cg[u]){
                if(!reach[v] || inf[v]) continue;
                ways[v]=min(2, ways[v]+ways[u]);
                indeg[v]--;
                if(indeg[v]==0) q.push(v);
            }
        }

        for(int i=1;i<=n;i++){
            int c=comp[i];
            int ans;
            if(!reach[c]) ans=0;
            else if(inf[c]) ans=-1;
            else if(ways[c]==1) ans=1;
            else ans=2;
            cout<<ans<<(i<n?' ':'\n');
        }
    }
    return 0;
}
