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

void solve(){
    int x, y;
    cin >> x >> y;
    string s;
    cin >> s;
    int n = s.size();

    vector<ll> dp(2);
    if(s[0]=='C') dp[1] = 1e18;
    if(s[0]=='J') dp[0] = 1e18;

    for(int i=1; i<n; i++){
        vector<ll> next(2);
        next[0] = min(dp[0], dp[1]+y);
        next[1] = min(dp[1], dp[0]+x);
        if(s[i]=='C') next[1] = 1e18;
        if(s[i]=='J') next[0] = 1e18;
        dp = next;
    }

    cout << min(dp[0], dp[1]) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": " << flush;
        solve();
    }
    return 0;
}