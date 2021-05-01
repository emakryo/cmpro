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

int dfs(int u, int p, vector<vector<int>> &g, vector<bool> &visit, set<pair<int, int>> &edges){
    int o = 0;
    visit[u] = true;
    dbg(u);
    for(auto v: g[u]){
        if(visit[v]){
            if(v!=p){
                if(edges.count({u, v}) || edges.count({v, u})){
                    cout << u+1 << " " << v+1 << endl;
                    edges.erase({u, v});
                    edges.erase({v, u});
                    o++;
                }
            }
        } else {
            if(dfs(v, u, g, visit, edges)){
                cout << u+1 << " " << v+1 << endl;
                o++;
            }
        }
    }

    if(o%2){
        cout << u+1 << " " << p+1 << endl;
    }

    return 1-o%2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n);
    set<pair<int, int>> edges;
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;

        g[a].push_back(b);
        g[b].push_back(a);
        edges.insert({a, b});
    }

    if(m%2){
        cout << -1 << endl;
        return 0;
    }

    vector<bool> visit(n);
    dfs(0, -1, g, visit, edges);
    return 0;
}