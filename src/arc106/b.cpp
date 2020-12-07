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

pair<ll, ll> dfs(int u, vector<ll> &a, vector<ll> &b, vector<vector<int>> &graph, vector<bool> &visit){
    pair<ll, ll> r(a[u], b[u]);
    visit[u] = true;
    for(int v: graph[u]){
        if(visit[v]) continue;
        auto s = dfs(v, a, b, graph, visit);
        r.first += s.first;
        r.second += s.second;
    }

    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m; cin >> n >> m;
    vector<ll> a(n), b(n);
    cin >> a >> b;
    vector<vector<int>> graph(n);

    for(int i=0; i<m; i++){
        int c, d; cin >> c >> d;
        c--; d--;
        graph[c].push_back(d);
        graph[d].push_back(c);
    }

    vector<bool> visit(n);
    for(int i=0; i<n; i++){
        if(visit[i]) continue;
        auto p = dfs(i, a, b, graph, visit);
        if(p.first != p.second) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}