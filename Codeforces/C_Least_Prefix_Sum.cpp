#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<ll> a(n+1);
        for(int i=1;i<=n;i++) cin >> a[i];

        ll ans = 0;

        {
            ll cur = 0;
            priority_queue<ll> pq;
            for(int i = m; i >= 2; --i){
                cur += a[i];
                if(a[i] > 0) pq.push(a[i]);
                while(cur > 0 && !pq.empty()){
                    cur -= 2 * pq.top();
                    pq.pop();
                    ans++;
                }
            }
        }

        {
            ll cur = 0;
            priority_queue<ll> pq;
            for(int i = m+1; i <= n; ++i){
                cur += a[i];
                if(a[i] < 0) pq.push(-a[i]);
                while(cur < 0 && !pq.empty()){
                    cur += 2 * pq.top();
                    pq.pop();
                    ans++;
                }
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
