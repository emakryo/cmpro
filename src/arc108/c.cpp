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

void dfs(int u, int p, int c, int n, vector<int> &color, vector<vector<pair<int, int>>> &graph){
    if(c<=0) color[u] = 1;
    else if(p>=0 && color[p]==c) color[u] = c%color.size()+1;
    else color[u] = c;
    dbg(u, color[u], n);
    for(auto q: graph[u]){
        int v = q.first;
        int c = q.second;
        if(color[v]) continue;
        dfs(v, u, c, n+1, color, graph);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);

    for(int i=0; i<m; i++){
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        graph[u].push_back({v, c});
        graph[v].push_back({u, c});
    }

    vector<int> color(n);

    dfs(0, -1, 0, 0, color, graph);
    for(int i=0; i<n; i++){
        cout << color[i] << '\n';
    }

    return 0;
}