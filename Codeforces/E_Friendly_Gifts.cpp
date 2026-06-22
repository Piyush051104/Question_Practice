#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<long long, long long> pll;
typedef priority_queue<ll> pq;
typedef priority_queue<ll, vector<ll>, greater<ll>> pqr;
#define all(a) (a).begin(), (a).end()
#define fixed(n) fixed << setprecision(n)
#define MOD 1000000007
#define loop(i,n) for(ll i=0;i<n;i++)
#define loop1(a,n) for(ll i=a;i<n;i++)
#define sum_vector(v) accumulate(v.begin(),v.end(),0LL)
#define min_value(v) *min_element(v.begin(),v.end())
#define max_value(v) *max_element(v.begin(),v.end())
ll powermod(ll x, ll y, ll p){ll res = 1;x = x % p;if (x == 0) return 0;while (y > 0){if (y & 1)res = (res*x) % p;y = y>>1;x = (x*x) % p;}return res;}
int solve(){
    int n;cin >> n;
    vector<int>v(n);
    loop(i,n) cin >> v[i];
    if(n == 1) return 0;
    int ans = 0;
    map<int,set<pair<int,int>>>mp;
    vector<int>time(n + 1,0);
    int ti = 0;
    vector<vector<int>>check(n,vector<int>(n,0));
    for(int i = 0 ;i < n;i++){
        ti++;
        int cnt = 0;
        int mini = INT_MAX;
        int maxi = INT_MIN;
        for(int j = i;j < n;j++){
            mini = min(mini,v[j]);
            maxi = max(maxi,v[j]);
            if(time[v[j]] == ti){
                break;
            }
            time[v[j]] = ti;
            cnt++;
           
            if(maxi -  mini + 1 == cnt){
                check[mini - 1][maxi - 1] = 1;
                int l1 = mini - cnt - 1;
                int l2 = mini - 2;
                if(l1 >= 0 &&  l2  >= 0 && check[l1][l2]) ans = max(ans,cnt);

                int r1 = maxi;
                int r2 = maxi + cnt - 1;
                if(r2 <= n - 1 && r1 <= n - 1 && check[r1][r2]){
                    ans = max(ans,cnt);
                }
            }
        }
    }

    
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        int ans = solve();
        cout << ans << endl;
    }
    return 0;
}