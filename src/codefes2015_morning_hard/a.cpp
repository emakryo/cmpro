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
    vector<ll> a(n);
    cin >> a;

    ll x = 0;
    ll l = 0, r = 0;
    for(int i=1; i<n; i++){
        x += a[i]*i + i-1;
        r += a[i];
    }

    ll ans = x;
    dbg(0, x);
    for(int i=1; i<n; i++){
        x -= r + (n-i-1);
        r -= a[i];
        l += a[i-1];
        x += l + i - 1;
        dbg(i, x);

        if(i%2==0) ans = min(ans, x);
    }

    cout << ans << endl;
    return 0;
}