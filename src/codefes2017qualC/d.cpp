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

const int INF = 1e9;
int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    string s;
    cin >> s;

    vector<int> x(1);
    for(int i=0; i<s.size(); i++){
        int k = s[i] - 'a';
        x.push_back(x.back() ^ 1<<k);
    }

    if(x.back() == 0) {
        cout << 1 << endl;
        return 0;
    }

    vector<int> dp(1<<26, INF);
    dp[0] = 0;
    for(int i=0; i<s.size(); i++){
        int k = s[i] - 'a';
        for(int j=0; j<26; j++){
            dp[x[i+1]] = min(dp[x[i+1]], dp[x[i+1] ^ 1<<j]+1);
        }
    }

    cout << dp[x.back()] << endl;
}