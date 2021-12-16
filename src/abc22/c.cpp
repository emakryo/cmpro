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
    int inf = 1e9;
    vector<vector<pair<int, int>>> g(n);
    for(int i=0; i<m; i++){
        int u, v, l;
        cin >> u >> v >> l;
        u--; v--;
        g[u].push_back({v, l});
        g[v].push_back({u, l});
    }

    int ans = inf;
    vector<int> dist(n, inf);
    for(auto s: g[0]){
        vector<int> sdist(n, inf);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
        que.push({0, s.first});
        sdist[s.first] = s.second;
        while(que.size()){
            int u = que.top().second;
            int s = que.top().first;
            que.pop();
            if(sdist[u] < s) continue;
            for(auto v: g[u]) {
                if(v.first==0) continue;
                if(sdist[u] + v.second < sdist[v.first]){
                    sdist[v.first] = sdist[u] + v.second;
                    que.push({sdist[v.first], v.first});
                }
            }
        }

        for(int i=0; i<n; i++){
            ans = min(ans, sdist[i] + dist[i]);
            dist[i] = min(dist[i], sdist[i]);
        }
    }

    if(ans < inf) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}