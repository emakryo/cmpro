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
    vector<int> x(n), y(n), z(n);
    for(int i=0; i<n; i++) cin >> x[i] >> y[i] >> z[i];

    vector<vector<int>> dist(n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            dist[i][j] = abs(x[i]-x[j]) + abs(y[i]-y[j]) + max(0, z[j]-z[i]);
        }
    }

    // for(int k=0; k<n; k++){
    //     for(int i=0; i<n; i++){
    //         for(int j=0; j<n; j++){
    //             dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
    //         }
    //     }
    // }

    vector<vector<ll>> dp(1<<n, vector<ll>(n, 1e18));

    dp[1][0] = 0;
    for(int s=1; s<(1<<n); s++){
        for(int i=0; i<n; i++){
            if((s>>i)&1==0) continue;
            for(int j=0; j<n; j++){
                dp[s|(1<<j)][j] = min(dp[s|(1<<j)][j], dp[s][i]+dist[i][j]);
            }
        }
    }

    ll ans = 1e18;

    for(int i=1; i<n; i++){
        ans = min(dp[(1<<n)-1][i]+dist[i][0], ans);
    }
    cout << ans << endl;

    return 0;
}