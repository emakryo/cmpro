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

void dfs(int u, vector<vector<int>> &g, vector<int> &visit) {
    for(int v: g[u]) {
        if(visit[v] >= 0) continue;
        visit[v] = visit[u];
        dfs(v, g, visit);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n;
    cin >> n;
    int m = 400001;
    vector<vector<int>> g(m);
    for(int i=0; i<n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> visit(m, -1);
    for(int i=0; i<m; i++){
        if(visit[i]>=0) continue;
        visit[i] = i;
        dfs(i, g, visit);
    }

    vector<int> es(m);
    vector<int> vs(m);
    for(int i=0; i<m; i++){
        es[visit[i]] += g[i].size();
        vs[visit[i]] += 1;
    }

    int ans = 0;
    for(int i=0; i<m; i++){
        if(es[i]/2 == vs[i]-1) ans += vs[i]-1;
        else ans += vs[i];
    }
    cout << ans << endl;

    return 0;
}