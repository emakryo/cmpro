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

ll floor(ll x, ll d){
    if(x>=0) return x/d;
    else return -(((-x)+d-1)/d);
}

ll ceil(ll x, ll d){
    return -floor(-x, d);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    double x, y, r;
    cin >> x >> y >> r;
    ll ix=round(x*10000), iy=round(y*10000), ir=round(r*10000);
    dbg(ix, iy, ir);

    ll ans = 0;
    for(ll i=ceil(ix-ir, 10000); i<=floor(ix+ir, 10000); i++){
        ll x2 = (ix-10000LL*i)*(ix-10000LL*i);
        ll d = ir*ir-x2;
        ll lb = 0, ub = 2e9;
        while(ub-lb>1){
            ll m = (lb+ub)/2;
            if(m*m<=d) lb = m;
            else ub = m;
        }
        ll ly = ceil(iy-lb, 10000);
        ll ry = floor(iy+lb, 10000);
        ans += ry-ly+1;
    }

    cout << ans << endl;
    return 0;
}