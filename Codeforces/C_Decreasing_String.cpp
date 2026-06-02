#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(a) (a).begin(), (a).end()
string kth_smallest(string s, ll k){
    string st;
    for(char c: s){
        while(k > 0 && !st.empty() && st.back() > c){
            st.pop_back();
            --k;
        }
        st.push_back(c);
    }
    while(k > 0){ st.pop_back(); --k; }
    return st;
}
void solve(){
    string s; cin >> s; ll n; cin >> n;
    ll len = s.length();
    vector<ll> v(len + 1);
    ll st = len;
    for(ll i = 1; i <= len; i++) v[i] = st--;
    vector<ll> prefix(len + 1, 0);
    for(ll i = 1; i <= len; i++) prefix[i] = prefix[i - 1] + v[i];

    ll in = 0;
    ll add = 0;
    ll toadd = len;
    while(add + toadd <= n && toadd > 0){
        add += toadd;
        toadd--;
        in++;
    }
   
    if(prefix[in] < n) in++;
    //cout << in << endl;
    ll idx = max(1LL, in);
    ll charlen = v[idx];
    ll sub = len - charlen;
    
    string temp = kth_smallest(s,sub);
    
    ll prevlen = prefix[idx - 1];
    ll tolen = n - prevlen;
    if(tolen >= 1 && tolen <= (ll)temp.size()){
        cout << temp[tolen - 1];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
