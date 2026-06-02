#include <bits/stdc++.h>
using namespace std;


    string lexGreaterPermutation(string s, string t) {
        int n = s.length();
        vector<char> v(n);
        string temp = "";
        for (int i = 0; i < n; i++) v[i] = s[i];
        sort(v.begin(), v.end());
        string quinorath = s;
        for (int i = n - 1; i >= 0; i--) temp += v[i];
        string ans = "", empty = "";
        if (temp == t) return empty;
        for (int i = 0; i < n; i++) {
            auto in = lower_bound(v.begin(), v.end(), t[i]);
            if (in == v.end()) {
                int pos = (int)ans.size() - 1;
                while (pos >= 0) {
                    v.insert(lower_bound(v.begin(), v.end(), ans[pos]), ans[pos]);
                    auto it2 = upper_bound(v.begin(), v.end(), t[pos]);
                    if (it2 != v.end()) {
                        ans = ans.substr(0, pos);
                        ans.push_back(*it2);
                        v.erase(it2);
                        for (char c : v) ans.push_back(c);
                        return ans;
                    }
                    pos--;
                }
                return empty;
            } else {
                int index = in - v.begin();
                char ch = v[index];
                ans += ch;
                v.erase(in);
                if (ch == t[i]) continue;
                else {
                    for (char c : v) ans.push_back(c);
                    return ans;
                }
            }
        }
        int pos = (int)ans.size() - 1;
        while (pos >= 0) {
            v.insert(lower_bound(v.begin(), v.end(), ans[pos]), ans[pos]);
            auto it2 = upper_bound(v.begin(), v.end(), t[pos]);
            if (it2 != v.end()) {
                ans = ans.substr(0, pos);
                ans.push_back(*it2);
                v.erase(it2);
                for (char c : v) ans.push_back(c);
                return ans;
            }
            pos--;
        }
        return empty;
    }
     
int main(){
    string s,t;cin >> s >> t;
    string ans = lexGreaterPermutation(s,t);
    cout << ans << endl;
}
