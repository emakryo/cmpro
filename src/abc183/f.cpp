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

struct UnionFind{
    std::vector<int> par, rnk, cnt;
    UnionFind(int n){
        par.assign(n, 0);
        rnk.assign(n, 0);
        cnt.assign(n, 1);
        for(int i=0; i<n; i++) par[i]=i;
    }
    int root(int i){
        if(par[i]==i) return i;
        return par[i]=root(par[i]);
    }
    void unite(int i, int j){
        int ri = root(i);
        int rj = root(j);
        if(ri==rj) return;

        if(rnk[ri]==rnk[rj]){
            cnt[rj] += cnt[ri];
            par[ri] = rj;
            rnk[rj]++;
        }
        else if(rnk[ri] < rnk[rj]){
            cnt[rj] += cnt[ri];
            par[ri] = rj;
        }
        else{
            cnt[ri] += cnt[rj];
            par[rj] = ri;
        }
    }
    bool same(int i, int j){
        return root(i) == root(j);
    }
    int count(int i){
        return cnt[root(i)];
    }
};

void dfs(int u, int p, vector<vector<int>> &graph, vector<int> &c, vector<int> &count, vector<int> &ans, vector<vector<pair<int, int>>> &query){
    dbg(u);
    int n = graph.size()/2;
    for(auto q: query[u]){
        ans[q.first] = -count[q.second];
    }
    if(u<n){
        count[c[u]]++;
    }

    for(int v: graph[u]){
        dfs(v, u, graph, c, count, ans, query);
    }

    for(auto q: query[u]){
        ans[q.first] += count[q.second];
    }

    dbg(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, q; cin >> n >> q;
    vector<int> c(n); cin >> c;
    for(int i=0; i<n; i++) c[i]--;

    vector<vector<int>> graph(2*n);
    UnionFind uf(2*n);
    vector<int> root(n);
    for(int i=0; i<n; i++) root[i] = i;
    vector<vector<pair<int, int>>> query(2*n);
    int m = n;
    int p = 0;

    while(q--){
        int z, a, b; cin >> z >> a >> b;
        a--; b--;
        if(z==1){
            if(uf.same(a, b)) continue;
            graph[m].push_back(root[uf.root(a)]);
            graph[m].push_back(root[uf.root(b)]);
            uf.unite(a, b);
            uf.unite(a, m);
            root[uf.root(m)] = m;
            m++;
        } else {
            query[root[uf.root(a)]].push_back({p++, b});
        }
    }

    vector<int> ans(p);
    vector<int> count(n);

    vector<bool> done(2*n);
    for(int i=0; i<n; i++){
        int r = root[uf.root(i)];
        if(done[r]) continue;
        dfs(r, -1, graph, c, count, ans, query);
        done[r] = true;
    }

    for(int i=0; i<p; i++){
        cout << ans[i] << "\n";
    }

    return 0;
}