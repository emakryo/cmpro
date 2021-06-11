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

#include <bits/stdc++.h>

template<typename T = long long>
struct LCA {
    int n, l, root=-1;
    std::vector<std::vector<std::pair<int, T>>> graph;
    std::vector<int> dep;
    std::vector<T> dist;
    std::vector<std::vector<int>> par;
    std::vector<std::vector<T>> max_edges;
    LCA(int n) : n(n) {
        l = 0;
        while ((1 << l) < n) l++;
        graph.assign(n, {});
        dist.assign(n, 0);
        dep.assign(n, 0);
        par.assign(n, vector<int>(l, -1));
        max_edges.assign(n, vector<T>(l));
    }
    void add_edge(int u, int v, T c = 1) {
        graph[u].emplace_back(v, c);
        graph[v].emplace_back(u, c);
    }
    void init(int _root = 0) {
        root = _root;
        dfs(root, -1, 0, 0);
        for (int i=1; i<l; i++) {
            for (int u=0; u<n; u++) {
                if (par[u][i-1] < 0) continue;
                par[u][i] = par[par[u][i-1]][i-1];
                max_edges[u][i] = std::max(max_edges[u][i-1], max_edges[par[u][i-1]][i-1]);
            }
        }
    }
    void dfs(int u, int p, T c, int d) {
        dist[u] = c;
        par[u][0] = p;
        dep[u] = d;
        for (auto e : graph[u]) {
            int v = e.first;
            T cv = e.second;
            if (v==p) continue;
            max_edges[v][0] = cv;
            dfs(v, u, c+cv, d+1);
        }
    }
    int operator() (int u, int v) const {
        assert(root>=0); // check whether inited
        if (dep[u]<dep[v]) swap(u, v);
        int gap = dep[u]-dep[v];
        for (int i=0; i<l; i++) {
            if (gap & (1 << i)) u = par[u][i];
        }
        if (u==v) return u;
        for (int i=l-1; i>=0; i--) {
            if (par[u][i]!=par[v][i]) {
                u = par[u][i];
                v = par[v][i];
            }
        }
        return par[u][0];
    }
    T distance(int u, int v) const {
        int c = (*this)(u, v);
        if(c < 0) return -1; // when graph is not connected
        return dist[u]+dist[v]-2*dist[c];
    }
    T max_edge(int from, int to) const {
        // maximum edge between from and to
        // https://atcoder.jp/contests/past202004-open/submissions/13002791
        assert(root>=0); // check whether inited
        int u = from;
        T x = 0;
        for(int i=l-1; i>=0; i--){
            if(par[u][i]<0) continue;
            if(dep[par[u][i]]>=dep[to]){
                x = std::max(x, max_edges[u][i]);
                u = par[u][i];
            }
        }
        return x;
    }
};

void dfs(int u, int p, vector<vector<int>> &g, vector<int> &b){
    b.push_back(u);
    for(int v: g[u]){
        if(v==p) continue;
        dfs(v, u, g, b);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n; cin >> n;
    vector<vector<int>> g(n);
    LCA lca(n);
    for(int i=0; i<n-1; i++){
        int a, b; cin >> a >> b;
        a--; b--;
        lca.add_edge(a, b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    lca.init();

    vector<int> b;
    dfs(0, -1, g, b);
    dbg(b);

    vector<pair<int, int>> bi;
    for(int i=0; i<n; i++){
        bi.push_back({b[i], i});
    }
    sort(bi.begin(), bi.end());

    int q; cin >> q;
    vector<int> ans;
    for(int _i=0; _i<q; _i++){
        int k; cin >> k;
        vector<int> v(k);
        cin >> v;

        vector<pair<int, int>> vi(k);
        for(int i=0; i<k; i++) vi[i] = {bi[v[i]-1].second, v[i]-1};
        sort(vi.begin(), vi.end());

        int r = vi[0].second;
        int a = 0;
        for(int i=1; i<k; i++){
            int x = vi[i-1].second;
            int y = vi[i].second;

            int z = lca(x, y);
            dbg(_i, i, r, x, y, z, lca(r, z));

            if(lca(r, z)==r){
                a += lca.distance(y, z);
            } else {
                a += lca.distance(y, r);
                r = z;
            }
            dbg(a);
        }

        ans.push_back(a);
    }

    for(int a: ans){
        cout << a << '\n';
    }

    return 0;
}