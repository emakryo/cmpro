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
    vector<vector<int>> r(m);
    for(int i=0; i<m; i++){
        int k;
        cin >> k;
        r[i].assign(k, 0);
        cin >> r[i];
    }

    vector<vector<int>> g(n+m);

    for(int i=0; i<m; i++){
        for(int s: r[i]){
            g[i+n].push_back(s-1);
            g[s-1].push_back(i+n);
        }
    }

    queue<pair<int, int>> que;
    vector<int> dist(n+m, 1e9);
    dist[0] = 0;
    que.push({0, 0});

    while(que.size()){
        int v = que.front().first;
        int d = que.front().second;
        que.pop();

        if(d>dist[v]) continue;

        for(int u: g[v]){
            if(dist[v]+1<dist[u]){
                que.push({u, dist[v]+1});
                dist[u] = dist[v]+1;
            }
        }
    }

    for(int i=0; i<n; i++){
        cout << (dist[i]==1e9?-1:dist[i]/2) << endl;
    }

    return 0;
}