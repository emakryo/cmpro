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
    ll x, y;
    cin >> x >> y;

    ll ans = 0;
    ll b1=2;
    for(int b=2; b-1<=min(y-1, x/(b+1)); b++){
        ans += b-1;
        b1 = b;
    }
    b1++;

    while(b1<=y&&x/(b1+1)>0){
        ll p = x/(b1+1);
        ll b2 = min(y+1, x/p);
        ans += p * (b2-b1);
        dbg(b1, b2, p, x);
        if(p==1) break;
        b1 = b2;
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