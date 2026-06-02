#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(){
    ll n,k; cin >> n >> k;
    vector<string> v(k);
    for(ll i=0;i<k;i++) cin >> v[i];
    vector<bitset<26>> pres(n);
    for(ll i=0;i<k;i++){
        for(ll j=0;j<n;j++){
            pres[j].set(v[i][j]-'a');
        }
    }
    vector<ll> divisors;
    for(ll i=1;i*i<=n;i++){
        if(n%i==0){
            divisors.push_back(i);
            if(i!=n/i) divisors.push_back(n/i);
        }
    }
    sort(divisors.begin(), divisors.end());
    for(ll d:divisors){
        string pattern="";
        bool ok=true;
        for(ll i=0;i<d;i++){
            bool found=false;
            for(int c=0;c<26;c++){
                bool fits=true;
                for(ll pos=i;pos<n;pos+=d){
                    if(!pres[pos].test(c)){ fits=false; break; }
                }
                if(fits){ pattern.push_back(char('a'+c)); found=true; break; }
            }
            if(!found){ ok=false; break; }
        }
        if(ok){
            ll times = n / d;
            for(ll t=0;t<times;t++) cout << pattern;
            cout << '\n';
            return;
        }
    }
    cout << v[0] << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
