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

bool dfs(int u, int c, int s, vector<vector<int>> &a, vector<int> &cs){
    int n = a.size();
    cs[u] = c;
    for(int v=0; v<n; v++){
        if(s>>v&1) continue;
        if(a[u][v]==0) continue;
        if(cs[v]==c) return false;
        if(cs[v]<0){
            if(!dfs(v, 1-c, s, a, cs)){
                return false;
            }
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i=0; i<m; i++){
        int x, y;
        cin >> x >> y;
        a[x-1][y-1] = 1;
        a[y-1][x-1] = 1;
    }

    ll ans = 0;
    for(int s=0; s<(1<<n); s++){
        bool ok = true;
        for(int i=0; i<n; i++){
            if((s>>i&1)==0) continue;
            for(int j=i+1; j<n; j++){
                if((s>>j&1)==0) continue;
                if(a[i][j]) ok = false;
            }
        }
        if(!ok) continue;

        ll x = 1;
        vector<int> cs(n, -1);
        for(int i=0; i<n; i++){
            if(s>>i&1) continue;
            if(cs[i]>=0) continue;
            if(dfs(i, 0, s, a, cs)){
                x *= 2;
            } else {
                x = 0;
            }
        }
        dbg(s, x);
        ans += x;
    }

    cout << ans << endl;

    return 0;
}