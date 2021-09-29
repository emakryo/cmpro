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

bool dfs(int u, int p, vector<vector<int>> &g, vector<int> &x, vector<pair<int, int>> &dp) {
    int m = x[u];
    vector<bool> dp2(m+1);
    dp2[0] = true;
    int sum = 0;
    for(int v: g[u]) {
        if(v==p) continue;
        if(!dfs(v, u, g, x, dp)){
            return false;
        }

        sum += dp[v].first + dp[v].second;
        for(int j=m; j>=0; j--){
            if(dp2[j]){
                dp2[j] = false;
                if(j+dp[v].first<=m) dp2[j+dp[v].first] = true;
                if(j+dp[v].second<=m) dp2[j+dp[v].second] = true;
            }
        }
    }
    dbg(u, dp2);

    for(int j=m; j>=0; j--){
        if(dp2[j]){
            dp[u] = {x[u], sum-j};
            dbg(u, x[u], sum-j);
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n;
    cin >> n;
    vector<int> p(n-1), x(n);
    cin >> p >> x;

    vector<vector<int>> g(n);
    for(int i=0; i<n-1; i++){
        g[i+1].push_back(p[i]-1);
        g[p[i]-1].push_back(i+1);
        dbg(i+1, p[i]-1);
    }

    vector<pair<int, int>> dp(n);

    if(dfs(0, -1, g, x, dp)) {
        cout << "POSSIBLE" << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}