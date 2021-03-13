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
    int n, m; cin >> n >> m;
    vector<ll> a(n); cin >> a;
    vector<ll> x(m); cin >> x;

    vector<ll> asum(n);
    vector<ll> smax(n);
    asum[0] = smax[0] = a[0];
    for(int i=1; i<n; i++){
        asum[i] += a[i] + asum[i-1];
        smax[i] = max(smax[i-1], asum[i]);
    }

    vector<ll> ans;

    for(int i=0; i<m; i++){
        if(asum[n-1]>0){
            ll d = (max(0ll, x[i]-smax[n-1])+asum[n-1]-1)/asum[n-1];
            ll y = x[i] - asum[n-1]*d;
            int k = lower_bound(smax.begin(), smax.end(), y)-smax.begin();
            dbg(x[i], d, y, k);
            ans.push_back(n*d + k);
        } else if(x[i]<=smax[n-1]){
            int k = lower_bound(smax.begin(), smax.end(), x[i]) - smax.begin();
            ans.push_back(k);
        } else {
            ans.push_back(-1);
        }
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int t; cin >> t;
    for(int i=0; i<t; i++) solve();
    return 0;
}