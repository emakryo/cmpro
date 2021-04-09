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
    vector<map<int, vector<int>>> g(n);
    vector<pair<int, int>> e(m);
    for(int i=0; i<m; i++){
        int a, b;
        string s;
        cin >> a >> b >> s;
        char c = s[0];
        a--; b--;
        g[a][c].push_back(b);
        g[b][c].push_back(a);
        e[i] = {a, b};
    }

    int l = n*n;
    vector<vector<int>> h(l);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(auto p: g[i]){
                if(g[j].count(p.first)==0) continue;
                for(int k: g[i][p.first]) for(int l: g[j][p.first]){
                    h[i*n+j].push_back(k*n+l);
                }
            }
        }
    }

    vector<int> dist(l, 1e9);
    dist[n-1] = 0;
    queue<int> que;
    que.push(n-1);

    while(que.size()){
        int v = que.front();
        que.pop();
        for(int u: h[v]){
            if(dist[u]>dist[v]+1){
                dist[u] = dist[v]+1;
                que.push(u);
            }
        }
    }

    int ans = 1e9;
    for(int i=0; i<n; i++){
        ans = min(ans, 2*dist[i*n+i]);
    }
    for(int i=0; i<m; i++){
        ans = min(ans, 1+2*dist[e[i].first*n+e[i].second]);
        ans = min(ans, 1+2*dist[e[i].second*n+e[i].first]);
    }

    cout << (ans==1e9?-1:ans) << endl;

    return 0;
}