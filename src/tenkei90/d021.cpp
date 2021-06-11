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

// perform strongly connected component decomposition
class SCC{
    std::vector<bool> visited;
    std::vector<std::vector<int> > rev_graph;
    std::vector<int> visit_nodes;
    std::vector<int> root;
    // sort nodes by post-order of dfs
    void visit(int n){
        if(visited[n]) return;
        visited[n] = true;
        for(int i=0; i<graph[n].size(); i++){
            visit(graph[n][i]);
        }
        visit_nodes.push_back(n);
    }

    // assign component index
    void assign(int n, int r){
        if(root[n] >= 0) return;
        root[n] = r;
        for(int i=0; i<rev_graph[n].size(); i++){
            assign(rev_graph[n][i], r);
        }
    }

public:
    int n;
    std::vector<std::vector<int> > graph; // original graph
    std::vector<std::vector<int> > components; // nodes lists for each components
    std::vector<int> component_index; // index of component to which each node belongs
    std::vector<std::vector<int> > component_graph; // graph of component index

    SCC(std::vector<std::vector<int> > &g): graph(g), n(g.size()){
        rev_graph.assign(n, {});

        for(int i=0; i<n; i++){
            for(int j=0; j<g[i].size(); j++){
                rev_graph[g[i][j]].push_back(i);
            }
        }

        visited.assign(n, false);
        for(int i=0; i<n; i++){
            visit(i);
        }

        root.assign(n, -1);
        for(int i=n-1; i>=0; i--){
            int m = visit_nodes[i];
            assign(m, m);
        }

        std::map<int, std::vector<int> > root_index;
        for(int i=0; i<n; i++){
            root_index[root[i]].push_back(i);
        }

        for(auto i=root_index.begin(); i!=root_index.end(); i++){
            components.push_back(i->second);
        }

        component_index.assign(g.size(), 0);
        for(int i=0; i<components.size(); i++){
            for(int j=0; j<components[i].size(); j++){
                component_index[components[i][j]] = i;
            }
        }

        component_graph.assign(components.size(), {});
        for(int i=0; i<n; i++){
            for(int j=0; j<g[i].size(); j++){
                int l = component_index[i];
                int m = component_index[g[i][j]];
                if(l == m) continue;
                component_graph[l].push_back(m);
            }
        }

        for(int i=0; i<components.size(); i++){
            sort(component_graph[i].begin(), component_graph[i].end());
            auto last = unique(component_graph[i].begin(), component_graph[i].end());
            component_graph[i].resize(last - component_graph[i].begin());
        }
    }

};

int _main(){
    using namespace std;
/*
 * 0 -> 1 -> 2 -> 7  8 -> 9
 * ^    |    |    ^
 * |    V    V    V
 * 3 <- 4 -> 5 -> 6
 */
    vector<vector<int> > g(10, vector<int>());
    g[0].push_back(1);
    g[1].push_back(2);
    g[1].push_back(4);
    g[2].push_back(5);
    g[2].push_back(7);
    g[3].push_back(0);
    g[4].push_back(3);
    g[4].push_back(5);
    g[5].push_back(6);
    g[6].push_back(7);
    g[7].push_back(6);
    g[8].push_back(9);
    SCC scc(g);

    assert(scc.component_index[0] == scc.component_index[1]);
    assert(scc.component_index[0] == scc.component_index[3]);
    assert(scc.component_index[0] == scc.component_index[4]);
    assert(scc.component_index[0] != scc.component_index[2]);
    assert(scc.component_index[2] != scc.component_index[5]);
    assert(scc.component_index[2] != scc.component_index[6]);
    assert(scc.component_index[6] == scc.component_index[7]);
    assert(scc.component_index[7] != scc.component_index[8]);
    assert(scc.component_index[8] != scc.component_index[9]);

    int c0 = scc.component_index[0];
    int c2 = scc.component_index[2];
    int c5 = scc.component_index[5];
    int c6 = scc.component_index[6];
    int c8 = scc.component_index[8];
    int c9 = scc.component_index[9];

    assert((scc.component_graph[c0] == vector<int>{c2, c5}));
    assert((scc.component_graph[c2] == vector<int>{c5, c6}));
    assert((scc.component_graph[c5] == vector<int>{c6}));
    assert((scc.component_graph[c6] == vector<int>{}));
    assert((scc.component_graph[c8] == vector<int>{c9}));
    assert((scc.component_graph[c9] == vector<int>{}));

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    SCC scc(g);

    ll ans = 0;
    for(auto &vs: scc.components){
        ll k = vs.size();
        ans += k*(k-1)/2;
    }

    cout << ans << endl;

    return 0;
}