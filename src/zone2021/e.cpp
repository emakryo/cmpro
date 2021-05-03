#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
    string sep = " ";
    if(v.size()) os << v[0];
    for(int i=1; i<v.size(); i++) os << sep << v[i];
    return os;
}

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
    for(int i=0; i<v.size(); i++) is >> v[i];
    return is;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
    cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int r, c;
    cin >> r >> c;
    vector<vector<int>> a(r, vector<int>(c-1));
    vector<vector<int>> b(r-1, vector<int>(c));

    for(int i=0; i<r; i++) cin >> a[i];
    for(int i=0; i<r-1; i++) cin >> b[i];

    vector<vector<pair<int, ll>>> g(2*r*c);

    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            int u = x*c+y;

            if(y<c-1){
                g[u].push_back({u+1, a[x][y]});
                g[u+r*c].push_back({u+1, a[x][y]});
            }
            if(y>0){
                g[u].push_back({u-1, a[x][y-1]});
                g[u+r*c].push_back({u-1, a[x][y-1]});
            }
            if(x<r-1){
                g[u].push_back({u+c, b[x][y]});
                g[u+r*c].push_back({u+c, b[x][y]});
            }
            if(x>0){
                g[u].push_back({u-c+r*c, 2});
                g[u+r*c].push_back({u-c+r*c, 1});
            }
        }
    }

    vector<ll> dist(2*r*c, 1e18);
    dist[0] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
    que.push({0, 0});

    while(que.size()){
        int u = que.top().second;
        ll d = que.top().first;
        que.pop();

        if(d > dist[u]) continue;

        for(auto p: g[u]){
            int v = p.first;
            ll nd = dist[u]+p.second;
            if(dist[v]>nd){
                dbg(u/(r*c), (u%(r*c))/c, u%c, "->", v/(r*c), (v%(r*c))/c, v%c, ": ", nd);
                dist[v] = nd;
                que.push({nd, v});
            }
        }
    }

    cout << min(dist[r*c-1], dist[2*r*c-1]) << endl;
    return 0;
}