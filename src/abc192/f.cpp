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
    ll x; cin >> x;
    vector<int> a(n);
    cin >> a;

    // n = 2;
    // x = 1e9;
    // a = vector<int>(n, 10000000);

    ll ans = 1e18;
    for(int k=1; k<=n; k++){
        vector<vector<vector<ll>>> dp(n+1, vector<vector<ll>>(k+1, vector<ll>(k, -1e18)));
        dp[0][0][0] = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<=k; j++){
                for(int q=0; q<k; q++){
                    if(j<k) dp[i+1][j+1][(q+a[i])%k] = max(dp[i+1][j+1][(q+a[i])%k], dp[i][j][q] + a[i]);
                    dp[i+1][j][q] = max(dp[i+1][j][q], dp[i][j][q]);
                }
            }
        }

        if(dp[n][k][x%k]>0){
            dbg(n, k, x%k, dp[n][k][x%k], (x-dp[n][k][x%k])/k);
            ans = min(ans, (x-dp[n][k][x%k])/k);
        }
    }

    cout << ans << endl;

    return 0;
}