#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n+1);
        for(int i = 1; i <= n; i++) cin >> a[i];

        vector<int> vis(n+1, 0), step(n+1, 0);
        int timer = 0;
        int cycles = 0, two_cycles = 0;

        for(int i = 1; i <= n; i++){
            if(vis[i]) continue;
            timer++;
            int cur = i, cnt = 1;
            while(!vis[cur]){
                vis[cur] = timer;
                step[cur] = cnt++;
                cur = a[cur];
            }
            if(vis[cur] == timer){
                int len = cnt - step[cur];
                cycles++;
                if(len == 2) two_cycles++;
            }
        }

        int mx = cycles;
        int mn = (cycles - two_cycles) + (two_cycles > 0 ? 1 : 0);

        cout << mn << " " << mx << "\n";
    }
    return 0;
}
