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

    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    cin >> a;

    ll ans = 0;
    vector<ll> d(n-1);

    for(int i=0; i<n-1; i++){
        d[i] = a[i+1] - a[i];
        ans += abs(d[i]);
    }
    dbg(d);

    for(int i=0; i<q; i++){
        int l, r;
        cin >> l >> r;
        ll v;
        cin >> v;

        if(l>1){
            ans -= abs(d[l-2]);
            d[l-2] += v;
            ans += abs(d[l-2]);
        }

        if(r<n){
            ans -= abs(d[r-1]);
            d[r-1] -= v;
            ans += abs(d[r-1]);
        }

        dbg(d);

        cout << ans << endl;
    }

    return 0;
}