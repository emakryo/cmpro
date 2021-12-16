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

class MaxFlowGraph{
    using ll = long long;
    const ll INF = 1e18;
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

public:
    struct edge {
        int to, rev; // destination, index for reversed edge
        long long cap; // capacity
    };
    int n;
    std::vector<std::vector<edge> > graph;
    MaxFlowGraph(int n_vertex): n(n_vertex){
        graph.assign(n_vertex, {});
    }

    void add_edge(int from, int to, ll cap){
        graph[from].push_back((edge){to, (int)graph[to].size(), cap});
        graph[to].push_back((edge){from, (int)graph[from].size()-1, 0});
    }

    ll flow(int s, int t){
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

    int n;
    cin >> n;
    vector<string> c(n);
    cin >> c;
    MaxFlowGraph g(2+n*n);
    ll inf = 1e15;
    int s = n*n;
    int t = n*n+1;
    for(int i=0; i<n*n; i++){
        int x = i / n;
        int y = i % n;
        if(x < n-1){
            g.add_edge(i, i+n, 1);
            g.add_edge(i+n, i, 1);
        }
        if(y < n-1){
            g.add_edge(i, i+1, 1);
            g.add_edge(i+1, i, 1);
        }
        if((x+y)%2){
            if(c[x][y]=='B'){
                g.add_edge(s, i, inf);
            } else{
                g.add_edge(s, i, 0);
            }
            if(c[x][y]=='W'){
                g.add_edge(i, t, inf);
            } else {
                g.add_edge(i, t, 0);
            }
        } else {
            if(c[x][y]=='B'){
                g.add_edge(i, t, inf);
            } else{
                g.add_edge(i, t, 0);
            }
            if(c[x][y]=='W'){
                g.add_edge(s, i, inf);
            } else {
                g.add_edge(s, i, 0);
            }
        }
    }

    ll ans = g.flow(s, t);

    cout << 2*n*(n-1) - ans << endl;
    return 0;
}
