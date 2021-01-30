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
    vector<string> s(n); cin >> s;

    ll dp[61][2];
    dp[0][0] = 1;
    dp[0][1] = 1;

    for(int i=0; i<n; i++){
        if(s[i]=="AND") {
            dp[i+1][0] = 2*dp[i][0] + dp[i][1];
            dp[i+1][1] = dp[i][1];
        } else {
            dp[i+1][0] = dp[i][0];
            dp[i+1][1] = dp[i][0] + 2 *dp[i][1];
        }
    }

    cout << dp[n][1] << endl;
    return 0;
}