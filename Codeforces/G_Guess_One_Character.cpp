#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    if(!(cin >> T)) return 0;
    while(T--){
        ll n;
        if(!(cin >> n)) return 0;

        string q;
        q = "1";
        cout << 1 << ' ' << q << endl;
        ll r1;
        if(!(cin >> r1) || r1 == -1) return 0;

        q = "11";
        cout << 1 << ' ' << q << endl;
        ll r2;
        if(!(cin >> r2) || r2 == -1) return 0;

        q = "01";
        cout << 1 << ' ' << q << endl;
        ll r3;
        if(!(cin >> r3) || r3 == -1) return 0;

        ll dif = r1 - r2;
        char ans = (dif == r3) ? '0' : '1';

        cout << 0 << ' ' << 1 << ' ' << ans << endl;
        int verdict;
        if(!(cin >> verdict) || verdict == -1) return 0;
    }
    return 0;
}
