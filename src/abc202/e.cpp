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

int o = 0;
void dfs(int u, int p, vector<vector<int>> &g, vector<int> &ord, vector<int> &depth, vector<int> &children){
    children[u] = 1;
    ord[u] = o;
    o++;
    for(int v: g[u]){
        if(v==p) continue;

        depth[v] = depth[u]+1;
        dbg(v, u);
        dfs(v, u, g, ord, depth, children);
        children[u] += children[v];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n;
    cin >> n;
    vector<int> p(n-1);
    cin >> p;

    int q;
    cin >> q;
    
    vector<int> u(q), d(q);
    for(int i=0; i<q; i++){
        cin >> u[i] >> d[i];
        u[i]--;
    }

    vector<vector<int>> g(n);
    for(int i=0; i<n-1; i++){
        g[i+1].push_back(p[i]-1);
        g[p[i]-1].push_back(i+1);
    }

    int o=0;
    vector<int> ord(n);
    vector<int> depth(n);
    vector<int> children(n);

    dfs(0, -1, g, ord, depth, children);

    dbg(ord);
    dbg(depth);
    dbg(children);

    vector<vector<int>> dnode(n);
    for(int i=0; i<n; i++){
        dnode[depth[i]].push_back(ord[i]);
    }

    for(int i=0; i<n; i++){
        sort(dnode[i].begin(), dnode[i].end());
    }

    for(int i=0; i<q; i++){
        cout << lower_bound(dnode[d[i]].begin(), dnode[d[i]].end(), ord[u[i]]+children[u[i]])
         - lower_bound(dnode[d[i]].begin(), dnode[d[i]].end(), ord[u[i]]) << '\n';
    }

    return 0;
}