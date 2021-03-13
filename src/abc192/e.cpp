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

    int n; cin >> n;
    int m; cin >> m;
    int x; cin >> x;
    int y; cin >> y;
    x--; y--;

    vector<int> a(m), b(m);
    vector<ll> t(m), k(m);
    vector<vector<pair<int, pair<ll, ll>>>> g(n);
    for(int i=0; i<m; i++){
        cin >> a[i] >> b[i] >> t[i] >> k[i];
        a[i]--; b[i]--;
        g[a[i]].push_back({b[i], {t[i], k[i]}});
        g[b[i]].push_back({a[i], {t[i], k[i]}});
    }

    vector<ll> dist(n, 1e18);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
    dist[x] = 0;
    que.push({0, x});

    while(que.size()){
        auto p = que.top();
        que.pop();
        ll d = p.first;
        int u = p.second;
        if(d>dist[u]) continue;
        for(auto q: g[u]){
            int v = q.first;
            ll te = q.second.first;
            ll ke = q.second.second;
            ll dv = dist[u] + te + (ke-d%ke)%ke;
            if(dv<dist[v]){
                dist[v] = dv;
                que.push({dv, v});
            }
        }
    }

    cout << (dist[y]==1e18?-1:dist[y]) << endl;

    return 0;
}