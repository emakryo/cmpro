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

void dfs(int u, int p, vector<vector<int>> &g, vector<int> &c, vector<bool> &visit){
    visit[u] = true;
    dbg(u, p);
    for(int v=0; v<g.size(); v++){
        if(g[u][v]==0||p==v) continue;

        if(g[u][v]==1&&g[v][u]==1&&c[v]==c[u]&&visit[v]) g[u][v] = 2;
        else if(c[v]<c[u]) g[u][v] = 2;
        else if(visit[v]) continue;
        else if(c[v]==c[u]){
            g[u][v] = 2;
            dfs(v, u, g, c, visit);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m; cin >> n >> m;
    vector<int> a(m), b(m);
    for(int i=0; i<m; i++){
        cin >> a[i] >> b[i];
        a[i]--; b[i]--;
    }
    vector<int> c(n); cin >> c;

    vector<vector<int>> g(n, vector<int>(n));
    for(int i=0; i<m; i++){
        g[a[i]][b[i]] = g[b[i]][a[i]] = 1;
    }

    vector<pair<int, int>> ci(n);
    for(int i=0; i<n; i++) ci[i] = {c[i], i};
    sort(ci.begin(), ci.end());

    vector<bool> visit(n);
    for(int i=0; i<n; i++){
        int j = ci[i].second;
        if(visit[j]) continue;
        dfs(j, -1, g, c, visit);
    }
    
    for(int i=0; i<m; i++){
        if(g[a[i]][b[i]]==2&&g[b[i]][a[i]]==1){
            cout << "->" << endl;
        } else if(g[a[i]][b[i]]==1&&g[b[i]][a[i]]==2){
            cout << "<-" << endl;
        } else {
            cout << "<-" << endl;
            dbg(g[a[i]][b[i]], g[b[i]][a[i]]);
        }
    }

    return 0;
}