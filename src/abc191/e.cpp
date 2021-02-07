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

    int n, m; cin >> n >> m;
    vector<vector<pair<int, ll>>> graph(n);
    vector<ll> sl(n, 1e9);
    for(int i=0; i<m; i++){
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--; b--;
        graph[a].push_back({b, c});
        if(a==b) sl[a] = min(sl[a], c);
    }

    vector<vector<ll>> dist(n, vector<ll>(n, 1e9));

    for(int i=0; i<n; i++){
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
        dist[i][i] = 0;
        que.push({0, i});

        while(que.size()){
            int u = que.top().second;
            ll d = que.top().first;
            que.pop();

            if(d>dist[i][u]) continue;
            for(auto p: graph[u]){
                int v = p.first;
                ll dx = p.second;
                if(dist[i][u]+dx<dist[i][v]){
                    dist[i][v] = dist[i][u]+dx;
                    que.push({dist[i][v], v});
                }
            }
        }
        dbg(dist[i]);
    }

    for(int i=0; i<n; i++){
        ll ans = sl[i];
        for(int j=0; j<n; j++){
            if(i==j) continue;
            ans = min(ans, dist[i][j]+dist[j][i]);
        }
        if(ans == 1e9) cout << -1 << "\n";
        else cout << ans << "\n";
    }

    return 0;
}