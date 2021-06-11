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

pair<int, int> dfs(int u, int p, vector<vector<int>> &g){
    int m = 1;
    int z = 1;
    vector<int> x, y;
    for(int v: g[u]){
        if(v==p) continue;
        auto a = dfs(v, u, g);
        if(a.second%2){
            y.push_back(a.first);
        } else {
            x.push_back(a.first);
        }
        m += a.second;
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    for(int a: x){
        if(a<0) z += a;
        else {
            if(y.size()%2){
                z += -a;
            } else{
                z += a;
            }
        }
    }

    for(int i=0; i<y.size(); i++){
        if(i%2){
            z += -y[i];
        } else {
            z += y[i];
        }
    }

    dbg(u, z, m, x.size(), y.size());

    return {z, m};
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for(int i=1; i<n; i++){
        int p;
        cin >> p;
        p--;
        g[i].push_back(p);
        g[p].push_back(i);
    }

    ll x = dfs(0, -1, g).first;
    cout << (n+x)/2 << endl;

    return 0;
}