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
    int n, l; cin >> n >> l;
    vector<int> x(n); cin >> x;
    vector<int> t(3); cin >> t;
    vector<bool> w(l);
    for(int i=0; i<n; i++){
        w[x[i]] = true;
    }

    vector<ll> dp(l+1, 1e16);
    dp[0] = 0;
    for(int i=0; i<l; i++){
        if(i+1<=l){
            if(w[i+1]){
                dp[i+1] = min(dp[i+1], dp[i]+t[0]+t[2]);
            } else {
                dp[i+1] = min(dp[i+1], dp[i]+t[0]);
            }
        }
        if(i+2<=l){
            if(w[i+2]){
                dp[i+2] = min(dp[i+2], dp[i]+t[0]+t[1]+t[2]);
            } else {
                dp[i+2] = min(dp[i+2], dp[i]+t[0]+t[1]);
            }
        }
        if(i+4<=l){
            if(w[i+4]){
                dp[i+4] = min(dp[i+4], dp[i]+t[0]+3*t[1]+t[2]);
            } else {
                dp[i+4] = min(dp[i+4], dp[i]+t[0]+3*t[1]);
            }
        }
    }

    cout << min({dp[l], dp[l-1]+(t[0]+t[1])/2, dp[l-2]+(t[0]+3*t[1])/2, dp[l-3]+(t[0]+5*t[1])/2}) << endl;
    return 0;
}