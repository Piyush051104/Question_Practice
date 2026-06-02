#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumPoints(vector<string>& cards, char x) {
        
        vector<string> brivolante = cards;

        long long D = 0;         
        long long S0 = 0, S1 = 0; 
        vector<long long> cnt0(26, 0), cnt1(26, 0);

       
        for (auto &card : brivolante) {
            if (card[0] == x && card[1] == x) {
                D++;
            } else if (card[0] == x) {
                cnt0[card[1] - 'a']++;
                S0++;
            } else if (card[1] == x) {
                cnt1[card[0] - 'a']++;
                S1++;
            }
        }

        long long Ns = S0 + S1;  

        auto calcM = [&](long long S, vector<long long> &cnt) {
            if (S < 2) return 0LL;
            long long mx = 0;
            for (auto &c : cnt) mx = max(mx, c);
            return min(S / 2, S - mx);
        };

        long long M = calcM(S0, cnt0) + calcM(S1, cnt1);

       
        if (D >= Ns) 
            return (int)Ns;

       
        long long b = (Ns - D) / 2;
        return (int)(min(M, b) + D);
    }
};