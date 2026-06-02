
#include <bits/stdc++.h>
#include<vector>
using namespace std;


typedef long long int lli;
typedef pair<lli, lli> p;

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
#define sz(a) ((int)a.size())
#define rep(i, a, n) for (lld i = (a); i <= (n); ++i)
#define repI(i, a, n) for (int i = (a); i <= (n); ++i)
#define repD(i, a, n) for (lld i = (a); i >= (n); --i)
#define repDI(i, a, n) for (int i = (a); i >= (n); --i)
#define fastIO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL); cout.precision(numeric_limits<double>::max_digits10);

// std::ios::sync_with_stdio(false); // Ab : )

vector<vector<int> > dp(5005, vector<int>(5005, -1)); // dp[0][0] = max cake can be eatten by bob
vector<int> c; // cake freq

// alice opt_ play - eat min_taste
// bob opt_ play - eat if he can prevent it eaten by alice
int solve(int i, int x){ // idx_count, (alice - bob) = no. cake bob can eat 
    if(i == sz(c)) return 0; // end of dp
    if(dp[i][x] != -1) return dp[i][x]; // already exists
    // bob able to eat (no. cake bob can eat - no. of cake at the idx) ->  max(i-bob eats cake or ii-bob don't eat cake)
    if(x - c[i] >= 0) return dp[i][x] = max(1 + solve(i+1, x - c[i]), solve(i+1, x+1)); 
    else return dp[i][x] = solve(i+1, x+1);  // bob can't able to eat cake 
}

int main() {
    fastIO;
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        vector<int> a(n); // tast_i
        // greedy won't work here because bob can't choose specificaly which cake he can eat
        // actually he don't know the future of alice
        // bob has options to eat a particular eat Yes/No  -  DP
        for(int i=0;i<n+2;i++){
        	for(int j=0;j<n+2;j++){
        		dp[i][j]=-1;
        	}
        }
        c.clear();
        map<int, int> mp; // map to store freq of cake
        repI(i, 0 , n-1) { cin >> a[i]; mp[a[i]]++; }
        for(auto it: mp) c.push_back(it.second);
        int ans = solve(0, 0);
        cout << c.size() - ans << endl;
    }
    return 0;
}