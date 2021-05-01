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

    int n, m; cin >> n >> m;
    vector<int> x(m), y(m), z(m);
    for(int i=0; i<m; i++) cin >> x[i] >> y[i] >> z[i];

    vector<vector<pair<int, int>>> c(n+1);
    for(int i=0; i<m; i++) c[x[i]].push_back({y[i]-1, z[i]});

    vector<ll> dp(1<<n);

    dp[0] = 1;
    for(int s=1; s<(1<<n); s++){
        vector<int> cnt(n);
        for(int i=0; i<n; i++) if(s>>i&1) cnt[i]++;
        for(int i=1; i<n; i++) cnt[i] += cnt[i-1];
        bool ok = true;

        for(auto p: c[cnt[n-1]]){
            if(cnt[p.first] > p.second) ok = false;
        }
        if(!ok) continue;

        for(int i=0; i<n; i++){
            if(s>>i&1){
                dp[s] += dp[s^(1<<i)];
            }
        }
        dbg(s, dp[s]);
    }

    cout << dp[(1<<n)-1] << endl;
    return 0;
}