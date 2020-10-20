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

#include<bits/stdc++.h>

struct edge {
    int to, rev; // destination, index for reversed edge
    ll cap; // capacity
};

struct FlowGraph{
    const ll INF = 1e18;
    int n;
    std::vector<std::vector<edge>> graph;
    std::vector<bool> used;
    ll dfs(int v, int t, ll f){
        if(v == t) return f;
        used[v] = true;
        for(int i=0; i<graph[v].size(); i++){
            edge &e = graph[v][i];
            if(!used[e.to] && e.cap > 0){
                ll d = dfs(e.to, t, std::min(e.cap, f));
                if(d>0){
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    FlowGraph(int n_vertex): n(n_vertex){
        graph.assign(n_vertex, {});
    }

    void add_edge(int from, int to, ll cap){
        graph[from].push_back((edge){to, (int)graph[to].size(), cap});
        graph[to].push_back((edge){from, (int)graph[from].size()-1, 0});
    }

    ll max_flow(int s, int t){
        ll flow = 0;
        while(true){
            used.assign(n, false);
            ll f = dfs(s, t, INF);
            if(f==0) return flow;
            flow += f;
        }
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    
    int n, m; cin >> n >> m;
    vector<string> s(n); cin >> s;

    FlowGraph f(n*m+2);

    int sc = n*m;
    int sk = n*m+1;
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    for(int i=0; i<n; i++) for(int j=0; j<m; j++) {
        if(s[i][j]=='#') continue;
        if((i+j)%2){
            f.add_edge(sc, i*m+j, 1);
            for(int k=0; k<4; k++){
                int nx=i+dx[k];
                int ny=j+dy[k];
                if(nx<0||n<=nx||ny<0||m<=ny) continue;
                if(s[nx][ny]=='#') continue;
                f.add_edge(i*m+j, nx*m+ny, 1);
            }
        } else {
            f.add_edge(i*m+j, sk, 1);
        }
    }

    cout << f.max_flow(sc, sk) << endl;

    for(int i=0; i<n; i++) for(int j=0; j<m; j++){
        if(s[i][j]!='.') continue;
        if((i+j)%2==0) continue;
        int p = i*m+j;

        for(auto e: f.graph[p]){
            if(e.cap > 0) continue;
            if(e.to == sk || e.to == sc) continue;
            int nx = e.to/m;
            int ny = e.to%m;
            if(s[nx][ny]!='.') continue;
            if(i+1==nx){
                s[i][j] = 'v';
                s[nx][ny] = '^';
            } else if(i-1==nx){
                s[i][j] = '^';
                s[nx][ny] = 'v';
            } else if(j+1==ny){
                s[i][j] = '>';
                s[nx][ny] = '<';
            } else if(j-1==ny){
                s[i][j] = '<';
                s[nx][ny] = '>';
            }
        }
    }

    for(int i=0; i<n; i++){
        cout << s[i] << endl;
    }
    return 0;
}