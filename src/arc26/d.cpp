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

struct edge {
    int u;
    int v;
    int c;
    int t;
};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m;
    cin >> n >> m;
    vector<edge> es(m);
    for(int i=0; i<m; i++){
        int a, b, c, t;
        cin >> a >> b >> c >> t;
        es[i] = edge{ a, b, c, t };
    }

    double lb = 0, ub = 1e18;
    for(int i_=0; i_<100; i_++){
        double x = (ub+lb)/2;

        UnionFind uf(n);
        double sum = 0;

        vector<pair<double, pair<int, int>>> ws(m);
        for(int i=0; i<m; i++){
            ws[i] = {-x*es[i].t+es[i].c, {es[i].u, es[i].v}};
        }
        sort(ws.begin(), ws.end());

        for(int i=0; i<m; i++){
            int u = ws[i].second.first;
            int v = ws[i].second.second;
            // dbg(ws[i].first, u, v);
            if(ws[i].first < 0 || !uf.same(u, v)){
                uf.unite(u, v);
                sum += ws[i].first;
            }
        }

        dbg(x, uf.count(0), sum);
        // break;

        if(uf.count(0)==n && sum > 0){
            lb = x;
        } else {
            ub = x;
        }
    }

    cout << ub << endl;

    return 0;
}