#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// order-statistics tree (supports order_of_key / find_by_order)
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Multiset behavior: store (value, unique_id)
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ordered_set<pair<long long,int>> os;
    int uid = 0;

    // insert values (allow duplicates)
    vector<long long> a = {5, 1, 3, 3, 7, 3};
    for(long long v : a) os.insert({v, uid++});

    long long x = 8;

    // count of elements < x:
    // use upper bound with (x, -inf) or (x, lowest uid). For < x, order_of_key({x, -INF})
    long long cnt_less = os.order_of_key({x, -1}); // all pairs strictly less than (x, -1) ⇒ values < x
    cout << cnt_less << "\n"; // here: elements < 4 are {1,3,3,3} = 4
}
