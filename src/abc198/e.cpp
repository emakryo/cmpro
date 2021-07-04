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

void dfs(int u, int p, vector<vector<int>> &g, vector<int> &c, multiset<int> &used, vector<bool> &ans){
    dbg(u, used.count(c[u]));
    if(used.count(c[u])==0){
        ans[u] = true;
    }
    used.insert(c[u]);
    for(int v: g[u]){
        if(v==p) continue;
        dfs(v, u, g, c, used, ans);
    }
    used.erase(used.find(c[u]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n;
    cin >> n;
    vector<int> c(n);
    cin >> c;
    vector<vector<int>> g(n);
    for(int i=0; i<n-1; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<bool> ans(n);
    multiset<int> used;
    dfs(0, -1, g, c, used, ans);

    for(int i=0; i<n; i++){
        if(ans[i]) cout << i+1 << endl;
    }
    return 0;
}