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

    ll r, x, y;
    cin >> r >> x >> y;

    ll ans;
    if(x*x+y*y==r*r) ans = 1;
    else {
        ll n = max(0ll, (ll)sqrt((double)r*r/(x*x+y*y))-3);
        while(r*r*n*n<x*x+y*y) n++;
        ans = max(2ll, n);
    }

    cout << ans << endl;
    return 0;
}