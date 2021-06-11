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

void dfs(int u, int p, vector<vector<int>> &g, vector<int> &depth){
    for(int v: g[u]){
        if(v==p) continue;
        depth[v] = depth[u]+1;
        dfs(v, u, g, depth);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n; cin >> n;
    vector<vector<int>> g(n);
    for(int i=0; i<n-1; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> depth(n);
    dfs(0, -1, g, depth);

    int m = 0;
    for(int i=0; i<n; i++){
        if(depth[i]%2) m++;
    }

    vector<int> ans;
    for(int i=0; i<n; i++){
        if((m>=n/2) == (depth[i]%2>0)){
            if(ans.size()<n/2) ans.push_back(i+1);
        }
    }

    cout << ans << endl;

    return 0;
}