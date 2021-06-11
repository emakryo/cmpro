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

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int h, w;
    cin >> h >> w;
    UnionFind uf(h*w);
    vector<bool> x(h*w);
    int q; cin >> q;

    for(int _i=0; _i<q; _i++){
        int t;
        cin >> t;
        if(t==1){
            int r, c; cin >> r >> c;
            r--; c--;
            int i = r*w+c;
            x[i] = true;

            for(int k=0; k<4; k++){
                int nr = r+dx[k];
                int nc = c+dy[k];
                int j = nr*w+nc;

                if(0<=nr&&nr<h&&0<=nc&&nc<w&&x[j]){
                    dbg("u", i, j);
                    uf.unite(i, j);
                }
            }
        } else {
            int ra, ca, rb, cb;
            cin >> ra >> ca >> rb >> cb;
            ra--; ca--; rb--; cb--;

            int i = ra*w+ca;
            int j = rb*w+cb;
            if(i==j){
                cout << (x[i]?"Yes":"No") << endl;
            } else {
                dbg("q", i, j, uf.same(i, j));
                cout << (uf.same(i, j)?"Yes":"No") << endl;
            }
        }
    }
    
    return 0;
}