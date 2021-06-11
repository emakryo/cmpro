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

    int n, w;
    cin >> n >> w;
    vector<int> a(n);
    cin >> a;
    vector<int> k(n);
    vector<vector<int>> c(n);
    for(int i=0; i<n; i++){
        cin >> k[i];
        c[i] = vector<int>(k[i]);
        cin >> c[i];
    }

    MaxFlowGraph g(n+2);

    int s = n, t = n+1;
    for(int i=0; i<n; i++){
        g.add_edge(s, i, w);
        g.add_edge(i, t, a[i]);

        for(int j=0; j<k[i]; j++){
            g.add_edge(i, c[i][j]-1, 1e18);
        }
    }

    ll ans = reduce(a.begin(), a.end()) - g.flow(s, t);
    cout << ans << endl;

    return 0;
}