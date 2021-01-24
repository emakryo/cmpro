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
    ll t;
    cin >> n >> t;
    vector<ll> a(n);
    cin >> a;

    int m = min(n, 20);
    vector<ll> xs(1<<m);
    for(int i=0; i<(1<<m); i++){
        for(int k=0; k<m; k++){
            if(i>>k&1) xs[i] += a[k];
        }
    }
    sort(xs.begin(), xs.end());

    if(n==m){
        auto it = lower_bound(xs.begin(), xs.end(), t+1);
        it--;
        cout << *it << endl;
        return 0;
    }

    int l = n-m;
    vector<ll> ys(1<<l);
    for(int i=0; i<(1<<l); i++){
        for(int k=0; k<l; k++){
            if(i>>k&1) ys[i] += a[k+m];
        }
    }

    ll ans = 0;
    for(ll y: ys){
        if(y>t) continue;
        auto it = lower_bound(xs.begin(), xs.end(), t+1-y);
        it--;
        ans = max(ans, *it+y);
    }
    cout << ans << endl;
    return 0;
}