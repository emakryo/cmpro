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
typedef std::vector<std::vector<int>> Graph;

bool toposort_rec(int u, Graph &g, std::vector<bool> &visit, std::vector<bool> &done, std::vector<int> &order) {
    if(visit[u]) return true;
    if(done[u]) return false;
    done[u] = visit[u] = true;
    for(auto v: g[u]){
        if(toposort_rec(v, g, visit, done, order)) return true;
    }
    visit[u]=false;
    order.push_back(u);
    return false;
}

/*
    Topological sort.
    If graph is not a DAG, return empty list.
*/
std::vector<int> toposort(Graph &graph) {
    int n = graph.size();
    std::vector<int> order;
    std::vector<bool> done(n), visit(n);
    for(int i=0; i<n; i++){
        if(done[i]) continue;
        if(toposort_rec(i, graph, visit, done, order)){
            return std::vector<int>();
        }
    }
    reverse(order.begin(), order.end());
    return order;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    vector<bool> is_root(n, true);
    for(int i=0; i<n+m-1; i++){
        int a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        is_root[b]=false;
    }

    vector<int> ord = toposort(g);

    vector<int> par(n);
    for(int i=0; i<n; i++){
        int u = ord[i];
        for(auto v: g[u]){
            par[v] = u+1;
        }
    }

    for(int i=0; i<n; i++){
        cout << par[i] << endl;
    }
    
    return 0;
}