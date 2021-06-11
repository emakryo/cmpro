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

    int n;
    cin >> n;
    vector<int> a(2*n);
    cin >> a;

    vector<vector<int>> dp(2*n+1, vector<int>(2*n+1, 1e9));

    for(int e=0; e<=2*n; e++){
        dp[e][e] = 0;
        if(e>=2) dp[e-2][e] = abs(a[e-2]-a[e-1]);
        for(int s=e-4; s>=0; s-=2){
            for(int i=s+2; i<e; i+=2){
                dp[s][e] = min(dp[s][e], dp[s][i]+dp[i][e]);
            }
            dp[s][e] = min(dp[s][e], dp[s+1][e-1]+abs(a[s]-a[e-1]));
        }
    }

    cout << dp[0][2*n] << endl;
    return 0;
}