#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(ll x, ll y, ll n, ll m, vector<vector<char>>& v){
    return x >= 0 && y >= 0 && x < n && y < m && v[x][y] != '#';
}

ll solve(){
    ll n, m;
    cin >> n >> m;

    vector<vector<char>> v(n, vector<char>(m));
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            cin >> v[i][j];
        }
    }

    ll sx, sy, ex, ey;
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            if(v[i][j] == 'S'){
                sx = i;
                sy = j;
            }
            if(v[i][j] == 'T'){
                ex = i;
                ey = j;
            }
        }
    }

    const ll INF = (1LL << 60);

    vector<vector<array<array<ll, 4>, 4>>> dis(
        n, vector<array<array<ll, 4>, 4>>(m)
    );

    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            for(int d = 0; d < 4; d++){
                for(int c = 0; c < 4; c++){
                    dis[i][j][d][c] = INF;
                }
            }
        }
    }

    vector<ll> xc = {-1, 0, 0, 1};
    vector<ll> yc = {0, -1, 1, 0};

    priority_queue<
        tuple<ll, ll, ll, ll, ll>,
        vector<tuple<ll, ll, ll, ll, ll>>,
        greater<tuple<ll, ll, ll, ll, ll>>
    > pq;

    for(ll d = 0; d < 4; d++){
        ll nx = sx + xc[d];
        ll ny = sy + yc[d];
        if(check(nx, ny, n, m, v)){
            dis[nx][ny][d][1] = 1;
            pq.push({1, 1, d, nx, ny});
        }
    }

    while(!pq.empty()){
        auto [dist, cnt, di, x, y] = pq.top();
        pq.pop();

        if(dist != dis[x][y][di][cnt]) continue;

        if(x == ex && y == ey) return dist;

        for(ll nd = 0; nd < 4; nd++){
            ll nx = x + xc[nd];
            ll ny = y + yc[nd];
            if(!check(nx, ny, n, m, v)) continue;

            if(nd == di){
                if(cnt < 3 && dis[nx][ny][nd][cnt + 1] > dist + 1){
                    dis[nx][ny][nd][cnt + 1] = dist + 1;
                    pq.push({dist + 1, cnt + 1, nd, nx, ny});
                }
                
            }else{
                if(dis[nx][ny][nd][1] > dist + 1){
                    dis[nx][ny][nd][1] = dist + 1;
                    pq.push({dist + 1, 1, nd, nx, ny});
                }
            }
        }
    }

    return -1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << solve() << '\n';
    return 0;
}