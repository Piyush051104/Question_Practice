#include <bits/stdc++.h>
using namespace std;

int lastRemaining(int n) {
    
        long long st = 1;
        long long diff = 1;
        bool flag = true;
        long long rem = n;
        while (rem > 1) {
            long long cur = rem;
            if (!flag && (cur % 2 == 0)) st += diff;
            diff *= 2;
            rem = (cur + 1) / 2;
            flag = !flag;
        }
        return st;
    
}

int main() {
    cout << lastRemaining(8) << "\n";
    cout << lastRemaining(5) << "\n";
    cout << lastRemaining(1) << "\n";
    return 0;
}
