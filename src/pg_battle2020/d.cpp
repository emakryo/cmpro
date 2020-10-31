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

typedef vector<vector<pair<int, int>>> G;

int dfs(int u, int p, G &graph, vector<int> &nchild){
    int ret = -1;
    for(auto v: graph[u]){
        if(v.first==p) continue;
        ret = max(ret, dfs(v.first, u, graph, nchild));
        nchild[u] += nchild[v.first];
        if(nchild[v.first] == nchild.size()/2) ret = u;
    }
    nchild[u] += 1;
    return ret;
}

void dfs2(int u, int p, G &graph, vector<ll> &depth){
    for(auto v: graph[u]){
        if(v.first==p) continue;
        depth[v.first] = v.second + depth[u];
        dfs2(v.first, u, graph, depth);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    
    int n; cin >> n;
    G graph(n);
    for(int i=0; i<n-1; i++){
        int a, b, m; cin >> a >> b >> m;
        a--; b--;
        graph[a].push_back({b, m});
        graph[b].push_back({a, m});
    }

    vector<int> nchild(n);
    int a = dfs(0, -1, graph, nchild);
    if(a < 0){
        cout << 0 << endl;
        return 0;
    }
    int b;
    for(int i=0; i<n; i++){
        if(nchild[i] == n/2) b = i;
    }

    int lab;
    for(auto e: graph[a]){
        if(e.first == b) lab = e.second;
    }

    vector<ll> da(n, -1), db(n, -1);
    da[a] = 0;
    db[b] = 0;
    dfs2(a, b, graph, da);
    dfs2(b, a, graph, db);

    ll ans = 0;
    vector<ll> sda, sdb;
    for(int i=0; i<n; i++){
        if(da[i]>=0) sda.push_back(da[i]);
        if(db[i]>=0) sdb.push_back(db[i]);
    }
    sort(sda.begin(), sda.end());
    sort(sdb.begin(), sdb.end());
    for(int i=0; i<n; i++){
        if(da[i]<0) continue;
        int x = lower_bound(sdb.begin(), sdb.end(), da[i]+lab) - lower_bound(sdb.begin(), sdb.end(), da[i]-lab);
        ans += x;
        dbg(i, da[i], x);
    }
    for(int i=0; i<n; i++){
        if(db[i]<0) continue;
        int x = lower_bound(sda.begin(), sda.end(), db[i]+lab) - lower_bound(sda.begin(), sda.end(), db[i]-lab);
        ans += x;
        dbg(i, db[i], x);
    }

    cout << ans << endl;

    return 0;
}