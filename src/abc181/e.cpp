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
    int n, m;
    cin >> n >> m;
    vector<ll> h(n); cin >> h;
    vector<ll> w(m); cin >> w;

    sort(h.begin(), h.end());
    sort(w.begin(), w.end());

    ll x = 0;
    for(int i=1; i<n; i+=2) x += h[i+1]-h[i];
    ll ans = 1e18;

    for(int i=0; i<n; i++){
        int k = lower_bound(w.begin(), w.end(), h[i])-w.begin();
        ll z = 1e18;
        if(k>0) z = min(z, h[i]-w[k-1]);
        if(k<m) z = min(z, w[k]-h[i]);
        ans = min(ans, x+z);

        if(i<n-1){
            if(i%2){
                x += h[i]-h[i+1];
            } else {
                if(i<n-1) x += h[i+1]-h[i];
            }
        }
    }

    cout << ans << endl;

    return 0;
}