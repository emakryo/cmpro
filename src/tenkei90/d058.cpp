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
    ll k; cin >> k;
    int m = 100000;
    vector<vector<int>> next(64, vector<int>(m));

    for(int i=0; i<m; i++){
        int x = i, y = i;
        for(int j=0; j<5; j++){
            x += y%10;
            y /= 10;
        }
        next[0][i] = x%m;
    }

    dbg(vector<int>(next[0].begin(), next[0].begin()+20));

    for(int i=0; i<63; i++){
        for(int j=0; j<m; j++){
            next[i+1][j] = next[i][next[i][j]];
        }
    }

    int ans = n;
    for(int i=0; i<64; i++){
        if(k>>i&1){
            ans = next[i][ans];
            dbg(i, k>>i&1, ans);
        }
    }

    cout << ans << endl;

    return 0;
}