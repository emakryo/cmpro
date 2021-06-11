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
    vector<int> d(n), c(n);
    vector<ll> s(n);
    for(int i=0; i<n; i++) cin >> d[i] >> c[i] >> s[i];

    vector<pair<int, pair<int, ll>>> v(n);
    for(int i=0; i<n; i++){
        v[i] = {d[i], {c[i], s[i]}};
    }
    sort(v.begin(), v.end());
    for(int i=0; i<n; i++){
        d[i] = v[i].first;
        c[i] = v[i].second.first;
        s[i] = v[i].second.second;
    }

    int m = 5000;
    vector<vector<ll>> dp(m+1, vector<ll>(n+1));

    for(int i=0; i<m; i++){
        dp[i+1] = dp[i];
        for(int j=0; j<n; j++){
            dp[i+1][j+1] = max(dp[i+1][j+1], dp[i+1][j]);
            if(d[j]<i+1||i+1-c[j]<0) continue;
            dp[i+1][j+1] = max(dp[i+1][j+1], dp[i+1-c[j]][j]+s[j]);
        }
        if(i<10) dbg(i+1, dp[i+1]);
    }

    cout << dp[m][n] << endl;
    return 0;
}