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
    int h, w; cin >> h >> w;
    vector<string> a(h);
    cin >> a;

    vector<vector<pair<int, int>>> graph(h*w+26);

    int s, g;

    for(int x=0; x<h; x++) for(int y=0; y<w; y++){
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, -1, 0, 1};
        if(a[x][y]=='#') continue;
        int u = w*x+y;

        for(int k=0; k<4; k++){
            int nx = x+dx[k];
            int ny = y+dy[k];
            if(nx<0||h<=nx||ny<0||w<=ny||a[nx][ny]=='#') continue;
            int v = w*nx+ny;

            graph[u].push_back({v, 2});
        }

        if('a'<=a[x][y]&&a[x][y]<='z') {
            int v = h*w+(a[x][y]-'a');
            graph[u].push_back({v, 1});
            graph[v].push_back({u, 1});
        }

        if(a[x][y]=='S') s = u;
        if(a[x][y]=='G') g = u;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
    vector<int> dist(h*w+26, 1e9);
    que.push({0, s});
    dist[s] = 0;

    while(que.size()){
        int d = que.top().first;
        int u = que.top().second;
        que.pop();
        if(d > dist[u]) continue;

        for(auto p: graph[u]){
            int v = p.first;
            int nd = d + p.second;
            if(nd < dist[v]){
                dist[v] = nd;
                que.push({nd, v});
            }
        }
    }

    if(dist[g]==1e9){
        cout << -1 << endl;
    } else {
        cout << dist[g]/2 << endl;
    }

    return 0;
}