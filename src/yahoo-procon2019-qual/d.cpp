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

    int l; cin >> l;
    vector<ll> a(l);
    cin >> a;

    vector<vector<ll>> dp(l+1, vector<ll>(5));
    dp[0][1] = dp[0][2] = dp[0][3] = dp[0][4] = 1e18;

    for(int i=0; i<l; i++){
        dp[i+1][0] = dp[i][0] + a[i];
        dp[i+1][1] = min(dp[i][0], dp[i][1]) + (a[i]>0?a[i]%2:2);
        dp[i+1][2] = min({dp[i][0], dp[i][1], dp[i][2]}) + 1 - a[i]%2;
        dp[i+1][3] = min({dp[i][0], dp[i][1], dp[i][2], dp[i][3]}) + (a[i]>0?a[i]%2:2);
        dp[i+1][4] = min({dp[i][0], dp[i][1], dp[i][2], dp[i][3], dp[i][4]}) + a[i];
    }

    cout << *min_element(dp[l].begin(), dp[l].end()) << endl;
    return 0;
}