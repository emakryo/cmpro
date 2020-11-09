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
    vector<ll> a(n); cin >> a;

    vector<ll> cum(n), cummax(n);
    cum[0] = a[0];
    cummax[0] = max(0ll, a[0]);
    for(int i=1; i<n; i++){
        cum[i] = cum[i-1]+a[i];
        cummax[i] = max(cummax[i-1], cum[i]);
    }
    dbg(cum);
    dbg(cummax);

    ll ans = cummax[0];
    ll cum2 = cum[0];
    for(int i=1; i<n; i++){
        ans = max(cum2+cummax[i], ans);
        cum2 += cum[i];
    }

    cout << ans << endl;
    return 0;
}