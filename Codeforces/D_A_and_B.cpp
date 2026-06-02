#include <bits/stdc++.h>
using namespace std;

int main() {
int t;
cin>>t;
while(t-->0){
    int n;
    cin>>n;
    vector<int>arr(n);
    for(auto &i:arr){
        cin>>i;
    }
    bool flag=true;bool flag1=true;
    for(int i=0;i<n-1;i++){
        if(arr[i]>arr[i+1])flag=false;
    }
    for(int i=0;i<n-1;i++){
        if(arr[i]<arr[i+1])flag1=false;
    }
    if(flag||flag1){
        cout<<1<<endl;
        cout<<n<<" ";
        for(auto &i:arr)cout<<i<<" ";
        cout<<endl;
        continue;
    }
    
    int mn=n+23;int mx=0;
    for(int i=0;i<n/2;i++){
        mn=min(mn,arr[i]);
        mx=max(arr[i],mx);
    }
    int mn1=n+23;int mx1=0;
    for(int i=(n/2);i<n;i++){
        mn1=min(mn1,arr[i]);
        mx1=max(mx1,arr[i]);
    }
    if(mx<mn1||mx1<mn){
        cout<<1<<endl;
        for(auto &i:arr)cout<<i<<" ";
        cout<<endl;
        continue;
    }
    
    cout<<2<<endl;
    int cnt=0;vector<int>v;
    for(int i=0;i<(n/2);i++){
        if(arr[i]>(n/2))v.push_back(arr[i]);
    }
    for(int i=(n/2);i<n;i++){
        if(arr[i]<=(n/2))v.push_back(arr[i]);
    }
    
    cout<<v.size()<<endl;
    for(auto  &i:v){
        cout<<i<<" ";
    }
    cout<<endl;
    vector<int>v1;
    for(int i=0;i<n/2;i++){
        if(arr[i]<=(n/2))v1.push_back(arr[i]);
    }
    for(int i=n/2;i<n;i++){
        if(arr[i]>(n/2))v1.push_back(arr[i]);
    }
    cout<<v1.size()<<endl;
    for(auto &i:v1){
        cout<<i<<" ";
    }
    cout<<endl;
}

}
