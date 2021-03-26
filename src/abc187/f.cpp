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

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(n));
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        a--; b--;
        g[a][b] = g[b][a] = 1;
    }

    vector<int> dp(1<<n, 1e9);
    for(int s=1; s<(1<<n); s++){
        bool ok = true;
        for(int i=0; i<n; i++) for(int j=i+1; j<n; j++){
            if((s>>i&1)==0||(s>>j&1)==0) continue;
            if(g[i][j]==0) ok = false;
        }
        if(ok){
            dp[s] = 1;
            continue;
        }

        for(int t=(s-1)&s; t; t=(t-1)&s){
            int u = s-t;
            dp[s] = min(dp[s], dp[t]+dp[u]);
        }
    }

    cout << dp[(1<<n)-1] << endl;
    return 0;
}