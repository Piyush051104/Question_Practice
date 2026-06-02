#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static int dp[201][201][201][8]; 
int f(int a, int b, int c, int xr) {
    if (a == 0 && b == 0 && c == 0) return 0;
    int &res = dp[a][b][c][xr];
    if (res != -1) return res;

    
    res = (xr == 0) ? 1 : 0;

  
    int bestNext = 0;
    if (a > 0) bestNext = max(bestNext, f(a - 1, b, c, xr ^ 1));
    if (b > 0) bestNext = max(bestNext, f(a, b - 1, c, xr ^ 2));
    if (c > 0) bestNext = max(bestNext, f(a, b, c - 1, xr ^ 3));

    res += bestNext;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dp, -1, sizeof(dp));

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

       
        int xr = 0;
        if (a & 1) xr ^= 1;
        if (b & 1) xr ^= 2;
        if (c & 1) xr ^= 3;
        

        int ans = f(a, b, c, xr);
        ans += d / 2; 
        cout << ans << '\n';
    }
    return 0;
}
