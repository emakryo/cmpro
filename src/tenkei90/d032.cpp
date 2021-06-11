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

    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i=0; i<n; i++){
        cin >> a[i];
    }

    int m; cin >> m;
    set<pair<int, int>> xy;
    for(int i=0; i<m; i++){
        int x, y;
        cin >> x >> y;
        x--; y--;
        xy.insert({x, y});
        xy.insert({y, x});
    }

    vector<int> p(n);
    for(int i=0; i<n; i++){
        p[i] = i;
    }

    int ans = 1e9;
    do {
        bool ok = true;
        for(int i=0; i<n-1; i++){
            if(xy.count({p[i], p[i+1]})){
                ok = false;
            }
        }
        if(!ok) continue;

        int t = 0;
        for(int i=0; i<n; i++){
            t += a[p[i]][i];
        }
        dbg(p);
        dbg(t);
        ans = min(ans, t);
    } while(next_permutation(p.begin(), p.end()));

    cout << (ans==1e9?-1:ans) << endl;
    return 0;
}