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

    int n, m; cin >> n >> m;
    vector<vector<int>> graph(n);
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int k; cin >> k;
    vector<int> c(k);
    for(int i=0; i<k; i++){
        cin >> c[i];
        c[i]--;
    }

    vector<vector<int>> dist(k, vector<int>(k, 1e9));


    for(int i=0; i<k; i++){
        vector<int> d(n, 1e9);
        queue<pair<int, int>> que;
        que.push({c[i], 0});
        while(que.size()){
            int u = que.front().first;
            int x = que.front().second;
            que.pop();
            if(d[u]<=x) continue;
            d[u] = x;
            for(int v: graph[u]){
                if(d[v]>d[u]+1){
                    que.push({v, d[u]+1});
                }
            }
        }

        for(int j=0; j<k; j++){
            if(i!=j) dist[i][j] = d[c[j]];
        }
    }

    vector<vector<vector<int>>> dp(1<<k, vector<vector<int>>(k, vector<int>(k, 1e9)));

    for(int s=0; s<(1<<k); s++){
        for(int i=0; i<k; i++){
            if((s>>i&1)==0) continue;
            if((1<<i) == s){
                dp[s][i][i] = 1;
            }
            for(int j=0; j<k; j++){
                if(s>>j&1) continue;
                for(int l=0; l<k; l++){
                    if((s>>l&1)==0) continue;
                    dp[s|(1<<j)][i][j] = min(dp[s|(1<<j)][i][j], dp[s][i][l] + dist[l][j]);
                }
            }
            dbg(s, i, dp[s][i]);
        }
    }

    int ans = 1e9;
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            ans = min(ans, dp[(1<<k)-1][i][j]);
        }
    }

    if(ans == 1e9){
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}