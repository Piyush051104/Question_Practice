#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string decimalToBinary(ll n){
    if(n == 0) return "0";
    string s;
    int msb = -1;
    for(int i = 63; i >= 0; --i){
        if((n >> i) & 1LL){
            msb = i;
            break;
        }
    }
    for(int i = msb; i >= 0; --i){
        s.push_back(((n >> i) & 1LL) ? '1' : '0');
    }
    return s;
}

ll binaryToDecimal(const string &s){
    ll num = 0;
    for(char c : s){
        num = num * 2 + (c - '0');
    }
    return num;
}

void solve(){
    ll n, k;
    cin >> n >> k;

    if(k & 1){
        for(ll i = 0; i < k; i++){
            cout << n << " ";
        }
        cout << "\n";
        return;
    }

    string s = decimalToBinary(n);
    ll len = s.length();
    ll cnt = 0;

    vector<string> ans(k);
    vector<bool> flag(k, false);

    for(ll i = 0; i < len; i++){
        if(s[i] == '0'){
            bool leaveZero = (cnt & 1);
            for(ll j = 0; j < k; j++){
                if(flag[j]){
                    if(leaveZero){
                        ans[j] += '0';
                        leaveZero = false;
                    } else {
                        ans[j] += '1';
                    }
                } else {
                    ans[j] += '0';
                }
            }
        } else {
            ll tightCount = k - cnt;
            if(tightCount > 0){
                bool usedZero = false;
                for(ll j = 0; j < k; j++){
                    if(!flag[j]){
                        if(!usedZero){
                            ans[j] += '0';
                            flag[j] = true;
                            usedZero = true;
                            cnt++;
                        } else {
                            ans[j] += '1';
                        }
                    } else {
                        ans[j] += '1';
                    }
                }
            } else {
                bool usedZero = false;
                for(ll j = 0; j < k; j++){
                    if(flag[j]){
                        if(!usedZero){
                            ans[j] += '0';
                            usedZero = true;
                        } else {
                            ans[j] += '1';
                        }
                    } else {
                        ans[j] += '1';
                    }
                }
            }
        }
    }

    for(ll i = 0; i < k; i++){
        cout << binaryToDecimal(ans[i]) << " ";
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
