#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)

int main() {
    int t;
    cin >> t;
    forn(tt, t) {
        int n, m, x, y, s = 0;
        cin >> n >> m >> x >> y;

        forn(i, n)
            cin >> s; 
        forn(i, m)
            cin >> s; 

        cout << n + m << endl;

    }
}