#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ll te;
    cin>>te;
    while (te--) 
    {
        int n,x,y=0;
        cin>>n;
        vector<vector<int>> a((n*n)+1);
        vector<vector<int>> ans(n,vector<int> (n));
        for (int i=1;i<=(n*n);i++)
        {
            for (int j=i+1;j<=(n*n) && a[i].size()<4;j++)
            {
                cout<<"? "<<i<<" "<<j<<" "<<endl;
                cin>>x;
                if (x==1)
                {
                    a[i].push_back(j);
                    a[j].push_back(i);
                }
            }
            if (a[i].size()==2)
                y=i;
            sort(a[i].begin(),a[i].end());
        }
        vector<int> vis(1+n*n,0);
        ans[0][0]=y;
        ans[0][1]=a[y][1];
        ans[1][0]=a[y][0];
        vis[y]=1;
        vis[a[y][1]]=1;
        vis[a[y][0]]=1;
        for (int i=1;i<n;i++)
        {
            int u=ans[0][i];
            int r=ans[1][i-1];
            int h=0;
            for (auto &v:a[u])
            {
                if (!vis[v] && binary_search(a[r].begin(),a[r].end(),v))
                {
                    ans[1][i]=v;
                    vis[v]=1;
                }
                if (vis[v]==0)  h=v;
            }
            if (i<n-1)
            ans[0][i+1]=h;
            vis[h]=1;
        }
        for (int i=1;i<n-1;i++)
        {
            for (int j=0;j<n;j++)
            {
                int u=ans[i][j];
                for (auto &v:a[u])
                {
                    if (vis[v]==0)
                    {
                        ans[i+1][j]=v;
                        vis[v]=1;
                    } 
                }
            }
        }
        cout<<"! "<<endl;
        for (auto &v:ans)
        {
            for (auto &v1:v) cout<<v1<<" ";
            cout<<endl;
        }
    }
}