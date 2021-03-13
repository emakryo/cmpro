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
    ll n; cin >> n;

    ll ans = 0;
    for(int k=0; k<=5; k++){
        ll b = 1;
        for(int j=0; j<k; j++) b *= 1000;
        ans += k*(min(b*1000, n+1) - b);
        dbg(k, b, min(b*1000, n+1)-b);
        if(n<b*1000) break;
    }

    cout << ans << endl;
    return 0;
}