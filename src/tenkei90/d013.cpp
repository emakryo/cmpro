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

vector<ll> dijkstra(int s, vector<vector<pair<int, ll>>> &g){
    int n = g.size();
    vector<ll> dist(n, 1e9);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
    que.push({0, s});

    while(que.size()){
        int u = que.top().second;
        ll d = que.top().first;
        que.pop();

        if(d > dist[u]) continue;

        for(auto p: g[u]){
            int v = p.first;
            ll dv = dist[u] + p.second;
            if(dv < dist[v]){
                dist[v] = dv;
                que.push({dv, v});
            }
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m; cin >> n >> m;
    vector<vector<pair<int, ll>>> g(n);
    for(int i=0; i<m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    vector<ll> d1 = dijkstra(0, g);
    vector<ll> d2 = dijkstra(n-1, g);

    for(int i=0; i<n; i++){
        cout << d1[i] + d2[i] << "\n";
    }

    return 0;
}