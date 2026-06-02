#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ll te;
    cin>>te;
    while (te--) 
    {
        int n;
        cin>>n;
        int y=(1<<n)-1;
        vector<int> vis((1<<n),0),ans(1,y);
        vis[y]=1;
        for (int i=0;(y>>(i+1));i++)
        {
            int u=y>>(i+1);
            int x=(1<<i);
            int g=(n-i);
            for (int j=0;j<x;j++)
            {
                int h=j<<g;
                ans.push_back(h+u);
                vis[h+u]=1;
            }
        }
        for (int i=0;i<=y;i++)
            if (!vis[i]) ans.push_back(i);
        for (auto &v:ans) cout<<v<<" ";
        cout<<endl;
    }
}