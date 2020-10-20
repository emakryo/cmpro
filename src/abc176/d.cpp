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

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int h, w; cin >> h >> w;
    using pii = pair<int, int>;
    pii c; cin >> c.first >> c.second;
    c.first--; c.second--;
    pii d; cin >> d.first >> d.second;
    d.first--; d.second--;
    vector<string> s(h);
    for(int i=0; i<h; i++) cin>>s[i];

    UnionFind uf(h*w);
    for(int i=0; i<h; i++) for(int j=0; j<w; j++){
        if(s[i][j]=='#') continue;
        if(i+1<h&&s[i+1][j]=='.') uf.unite(i*w+j, (i+1)*w+j);
        if(j+1<w&&s[i][j+1]=='.') uf.unite(i*w+j, i*w+j+1);
    }

    vector<set<int>> graph(h*w);
    for(int i=0; i<h; i++) for(int j=0; j<w; j++){
        if(s[i][j]=='#') continue;
        int a = uf.root(i*w+j);
        for(int x=-2; x<3; x++) for(int y=-2; y<3; y++){
            if(x==0&&y==0) continue;
            if(x+i<0||h<=x+i||y+j<0||w<=y+j||s[x+i][y+j]=='#') continue;
            int b = uf.root((i+x)*w+j+y);
            if(a==b) continue;
            graph[a].insert(b);
            graph[b].insert(a);
            dbg(a, b);
        }
    }

    vector<int> dist(h*w, 1e9);
    queue<int> que;
    int start = uf.root(c.first*w+c.second);
    dist[start] = 0;
    que.push(start);

    while(que.size()){
        int v = que.front();
        que.pop();
        for(int u: graph[v]){
            if(dist[u]<1e9) continue;
            dist[u] = dist[v]+1;
            que.push(u);
        }
    }

    
    int ans =  dist[uf.root(d.first*w+d.second)];
    cout << (ans==1e9?-1:ans) << endl;

    return 0;
}