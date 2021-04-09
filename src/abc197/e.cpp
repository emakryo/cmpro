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
    vector<ll> x(n);
    vector<int> c(n);
    for(int i=0; i<n; i++) cin >> x[i] >> c[i];

    map<int, vector<ll>> cx;
    for(int i=0; i<n; i++) cx[c[i]].push_back(x[i]);
    vector<ll> xmin, xmax;
    for(auto p: cx){
        auto m = minmax_element(p.second.begin(), p.second.end());
        xmin.push_back(*m.first);
        xmax.push_back(*m.second);
        dbg(*m.first, *m.second);
    }

    int m = xmin.size();
    vector<ll> dp(2);
    if(0<xmin[0]){
        dp[0] = 2*xmax[0]-xmin[0];
        dp[1] = xmax[0];
    } else if(0<xmax[0]){
        dp[0] = 2*xmax[0]-xmin[0];
        dp[1] = xmax[0] - 2*xmin[0];
    } else {
        dp[0] = -xmin[0];
        dp[1] = xmax[0]-2*xmin[0];
    }
    for(int i=1; i<m; i++){
        vector<ll> next(2, 1e18);

        ll x0 = xmin[i-1];
        ll d0 = dp[0];

        if(x0<xmin[i]){
            next[0] = min(next[0], d0 + 2*xmax[i]-xmin[i]-x0);
            next[1] = min(next[1], d0 + xmax[i]-x0);
        } else if(x0<xmax[i]){
            next[0] = min(next[0], d0 + 2*xmax[i]-xmin[i]-x0);
            next[1] = min(next[1], d0 + xmax[i]+x0-2*xmin[i]);
        } else {
            next[0] = min(next[0], d0 + x0-xmin[i]);
            next[1] = min(next[1], d0 + xmax[i]+x0-2*xmin[i]);
        }

        x0 = xmax[i-1];
        d0 = dp[1];
        if(x0<xmin[i]){
            next[0] = min(next[0], d0 + 2*xmax[i]-xmin[i]-x0);
            next[1] = min(next[1], d0 + xmax[i]-x0);
        } else if(x0<xmax[i]){
            next[0] = min(next[0], d0 + 2*xmax[i]-xmin[i]-x0);
            next[1] = min(next[1], d0 + xmax[i]+x0-2*xmin[i]);
        } else {
            next[0] = min(next[0], d0 + x0-xmin[i]);
            next[1] = min(next[1], d0 + xmax[i]+x0-2*xmin[i]);
        }

        dp = next;
    }

    cout << min(dp[0]+abs(xmin[m-1]), dp[1]+abs(xmax[m-1])) << endl;
    
    return 0;
}