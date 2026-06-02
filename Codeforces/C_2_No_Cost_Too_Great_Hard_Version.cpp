#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<long long, long long> pll;
#define all(a) (a).begin(), (a).end()
#define loop(i,n) for(ll i=0;i<n;i++)
const int MAXA = 200000 + 5;
vector<int> build_spf(int maxN){
    vector<int> spf(maxN+1);
    for(int i=0;i<=maxN;++i) spf[i]=i;
    spf[0]=0; if(maxN>=1) spf[1]=1;
    for(int i=2;(long long)i*i<=maxN;++i) if(spf[i]==i) for(int j=i*i;j<=maxN;j+=i) if(spf[j]==j) spf[j]=i;
    return spf;
}
vector<int> small_primes;
vector<int> factorize_with_spf_cached(long long n,const vector<int>& spf, unordered_map<long long, vector<int>>& cache){
    auto it = cache.find(n);
    if(it!=cache.end()) return it->second;
    vector<int> res;
    if(n<=1){ cache.emplace(n,res); return res; }
    if(n < (long long)spf.size()){
        int nn=(int)n;
        while(nn!=1){
            int p=spf[nn];
            res.push_back(p);
            while(nn%p==0) nn/=p;
        }
        cache.emplace(n,res);
        return res;
    }
    for(int p: small_primes){
        if((long long)p*p>n) break;
        if(n%p==0){
            res.push_back(p);
            while(n%p==0) n/=p;
        }
    }
    if(n>1) res.push_back((int)n);
    cache.emplace(n,res);
    return res;
}
ll solve(const vector<int>& spf){
    ll n; if(!(cin>>n)) return 0;
    vector<ll> v1(n), v2(n);
    loop(i,n) cin>>v1[i];
    loop(i,n) cin>>v2[i];
    vector<pair<ll,ll>> temp(n);
    for(int i=0;i<n;++i) temp[i]={v2[i],v1[i]};
    sort(all(temp));
    unordered_set<int> flag; flag.reserve(n*4);
    unordered_set<int> flag1; flag1.reserve(n*4);
    unordered_map<long long, vector<int>> fac_cache; fac_cache.reserve(n*4);
    for(ll i=0;i<n;++i){
        auto f = factorize_with_spf_cached(temp[i].second, spf, fac_cache);
        for(auto p:f) if(flag.find(p)!=flag.end()) return 0;
        for(auto p:f) flag.insert(p);
        if(i>0) for(auto p:f) flag1.insert(p);
    }
    ll ans1 = LLONG_MAX;
    for(ll i=0;i<n;++i){
        auto f = factorize_with_spf_cached(temp[i].second+1, spf, fac_cache);
        bool ch=false;
        for(auto p:f) if(flag.find(p)!=flag.end()){ ch=true; ans1=temp[i].first; break; }
        if(ch) break;
    }
    ll num = temp[0].second + 1;
    ll c1 = temp[0].first;
    ll ans2 = LLONG_MAX;
    while(c1 < ans1 && c1 < temp[1].first + temp[0].first){
        auto f = factorize_with_spf_cached(num, spf, fac_cache);
        bool ch=false;
        for(auto p:f) if(flag1.find(p)!=flag1.end()){ ch=true; ans1=c1; break; }
        if(ch) break;
        c1 += temp[0].first;
        ++num;
    }
    ll ans3 = temp[1].first + temp[0].first;
    return min({ans1,ans2,ans3});
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto spf = build_spf(MAXA);
    for(int i=2;i<(int)spf.size();++i) if(spf[i]==i) small_primes.push_back(i);
    int t; if(!(cin>>t)) return 0;
    while(t--){
        cout << solve(spf) << '\n';
    }
    return 0;
}
