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
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int s; cin >> s;
    int k; cin >> k;
    vector<int> t(k+1);
    t[0] = s-1;
    for(int i=1; i<=k; i++){
        int tt; cin >> tt;
        t[i] = tt-1;
    }

    vector<vector<int>> dist(k+1, vector<int>(k+1));

    for(int i=0; i<k+1; i++){
        queue<int> que;
        vector<int> d(n, 1e9);
        d[t[i]] = 0;
        que.push(t[i]);

        while(que.size()){
            int u = que.front();
            que.pop();
            for(int v: graph[u]){
                if(d[v]<1e9) continue;
                d[v] = d[u] + 1;
                que.push(v);
            }
        }

        for(int j=0; j<k+1; j++){
            dist[i][j] = d[t[j]];
        }
        dbg(dist[i]);
    }

    vector<vector<int>> cost(k+1, vector<int>(1<<(k+1), 1e9));

    cost[0][1] = 0;

    for(int i=1; i<(1<<(k+1)); i++){
        for(int j=0; j<k+1; j++){
            if((i>>j&1)==0) continue;
            for(int l=0; l<k+1; l++){
                if(i>>l&1) continue;
                cost[l][i|(1<<l)] = min(cost[l][i|(1<<l)], cost[j][i] + dist[j][l]);
            }
        }
    }

    int ans = 1e9;
    for(int i=0; i<k; i++){
        ans = min(ans, cost[i+1][(1<<(k+1))-1]);
    }

    cout << ans << endl;

    return 0;
}