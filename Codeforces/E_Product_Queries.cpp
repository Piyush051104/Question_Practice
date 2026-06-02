#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int n; cin>>n;
        vector<int>a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        vector<int> dis(n+1, INF);
        queue<int> q;
        for(int x: a){
            if(x<=n && dis[x]>1){
                dis[x]=1;
                q.push(x);
            }
        }
        while(!q.empty()){
            int x = q.front(); q.pop();
            for(int mult: a){
                if(mult==1) continue;
                if((long long)x * mult > n) break;
                int y = x * mult;
                if(dis[y] > dis[x] + 1){
                    dis[y] = dis[x] + 1;
                    q.push(y);
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(dis[i]==INF) cout << -1;
            else cout << dis[i];
            if(i==n) cout << '\n'; else cout << ' ';
        }
    }
    return 0;
}
