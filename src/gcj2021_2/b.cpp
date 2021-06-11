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

void solve_(){
    int n; cin >> n;

    vector<map<ll, int>> dp(n+1);

    for(int i=3; i<=n; i++){
        dp[i][i] = 1;
        for(auto p: dp[i]){
            for(int k=2; i+k*p.first<=n; k++){
                dp[i+k*p.first][k*p.first] = max(dp[i+k*p.first][k*p.first], p.second+1);
                dbg(i, k, p.first, i+k*p.first, dp[i+k*p.first][k*p.first]);
            }
        }
    }

    int ans = 0;
    for(auto p: dp[n]){
        ans = max(ans, p.second);
    }
    cout << ans << endl;
}

int rec(int x){
    if(x<=5) return 1;
    int ret = 1;
    for(int p=2; p*p<=x; p++){
        if(x%p) continue;
        ret = max(ret, 1+rec(x/p-1));
        ret = max(ret, 1+rec(p-1));
    }
    dbg(x, ret);
    return ret;
}

void solve(){
    int n; cin >> n;

    int ans = 1;
    for(int p=3; p*p<=n; p++){
        if(n%p) continue;
        ans = max(ans, 1+rec(n/p-1));
        ans = max(ans, 1+rec(p-1));
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";

        solve();
    }
    return 0;
}