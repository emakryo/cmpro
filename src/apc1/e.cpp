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

pair<int, int> dfs1(int u, int p, vector<vector<int>> &g) {
    int d = 0;
    int x = u;

    for(int v: g[u]) {
        if(v == p) continue;
        pair<int, int> q = dfs1(v, u, g);
        if(d < q.first+1) {
            x = q.second;
            d = q.first+1;
        }
    }

    return {d, x};
}

int dfs2(int u, int p, vector<vector<int>> &g) {
    int r = 0;
    int m = 0;
    for(int v: g[u]) {
        if(v == p) continue;
        int x = dfs2(v, u, g);
        if(x==0) m++;
        r += x;
    }
    r += max(0, m - 1);
    dbg(u, r);
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n;
    cin >> n;

    vector<vector<int>> g(n);
    for(int i=0; i<n-1; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    pair<int, int> d = dfs1(0, -1, g);
    int v0 = d.second;

    cout << dfs2(v0, -1, g) + 1 << endl;
    return 0;
}