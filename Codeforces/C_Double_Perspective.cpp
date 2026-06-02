#include <bits/stdc++.h>
using namespace std;

int minPatches(vector<int>& A, int B) {
    long long miss = 1;       
    int patches = 0;          
    int i = 0, n = A.size();

    // While there remains some value <= B that we cannot form
    while (miss <= B) {
        if (i < n && A[i] <= miss) {
            // We can extend coverage by using A[i]
            miss += A[i++];
        } else {
            // Patch with 'miss' itself to double our coverage
            miss += miss;
            ++patches;
        }
    }
    return patches;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> A(n);
    for (int &x : A) {
        cin >> x;
    }

    int B;
    cin >> B;

    cout << minPatches(A, B) << "\n";
    return 0;
}