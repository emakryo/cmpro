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

    ll n, m, k;
    cin >> n >> k >> m;

    int l = 51*51*51;
    // int l = 10;
    vector<vector<ll>> dp(n, vector<ll>(l));
    dp[0][0] = 1;

    for(int i=1; i<n; i++){
        for(int x=0; x<l; x++){
            dp[i][x] = dp[i-1][x];
            if(x >= i){
                dp[i][x] += dp[i][x-i];
            }
            if(x >= (k+1)*i) {
                dp[i][x] += m - dp[i-1][x-(k+1)*i];
            }
            dp[i][x] %= m;
            // dbg(i, x, dp[i][x]);
        }
    }

    for(int i=0; i<n; i++){
        ll ans = 0;
        for(int x=0; x<l; x++){
            ans += dp[i][x] * dp[n-i-1][x] % m;
            ans %= m;
        }
        ans *= k+1;
        ans += m-1;
        ans %= m;
        cout << ans << "\n";
    }

    return 0;
}