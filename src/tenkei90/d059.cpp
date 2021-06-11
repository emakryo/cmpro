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

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> g(n);
    for(int i=0; i<m; i++){
        int x, y;
        cin >> x >> y;
        x--; y--;

        g[x].push_back(y);
    }

    int p = 64;
    for(int i=0; i<(q+p-1)/p; i++){
        vector<int> bs;
        vector<ll> dp(n);
        int l = p;
        if(i==(q-1)/p) l = (q-1)%p+1;
        dbg(i, l);
        for(int k=0; k<l; k++){
            int a, b;
            cin >> a >> b;
            a--; b--;
            bs.push_back(b);
            dp[a] += 1ll<<k;
            dbg(i, k);
        }

        for(int j=0; j<n; j++){
            for(int k: g[j]){
                dp[k] = dp[k] | dp[j];
            }
        }

        for(int k=0; k<bs.size(); k++){
            cout << (dp[bs[k]]>>k&1?"Yes":"No") << endl;
        }

    }
    return 0;
}