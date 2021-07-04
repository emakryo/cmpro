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

#include<bits/stdc++.h>

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, pair<ll, ll>>>> g(n);
    for(int i=0; i<m; i++){
        int a, b;
        ll c, d;
        cin >> a >> b >> c >> d;
        a--; b--;
        g[a].push_back({b, {c, d}});
        g[b].push_back({a, {c, d}});
    }

    int s = 0;

    std::vector<long long> dist(n, 1e18);
    dist[s] = 0;
    using Pli = std::pair<long long, int>;
    std::priority_queue<Pli, std::vector<Pli>, std::greater<Pli>> que;
    que.push({0, s});

    while(que.size()){
        int u = que.top().second;
        long long d = que.top().first;
        que.pop();

        if(d > dist[u]) continue;

        for(auto p: g[u]){
            int v = p.first;
            ll w = max(0ll, (ll)sqrt(p.second.second) - dist[u] - 2);

            ll d = 1e18;
            for(int k=0; k<3; k++){
                d = min(d, p.second.first+w+dist[u]+p.second.second/(dist[u]+w+1));
                w++;
            }

            if(d < dist[v]){
                dbg(u, v, d);
                dist[v] = d;
                que.push({d, v});
            }
        }
    }

    cout << (dist[n-1]==1e18?-1:dist[n-1]) << endl;
    return 0;
}