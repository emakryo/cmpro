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

    int n, m, q; cin >> n >> m >> q;
    vector<vector<int>> graph(n);
    for(int i=0; i<m; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> c(n); cin >> c;
    for(int i=0; i<q; i++){
        int a; cin >> a;
        int x, y;
        if(a == 1){
            cin >> x;
            x--;
            cout << c[x] << endl;

            for(int v: graph[x]){
                c[v] = c[x];
            }
        } else {
            cin >> x >> y;
            x--;
            cout << c[x] << endl;

            c[x] = y;
        }
    }

    return 0;
}