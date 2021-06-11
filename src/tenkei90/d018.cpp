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

    ll t, l, x, y; cin >> t >> l >> x >> y;
    
    int q; cin >> q;

    for(int _i=0; _i<q; _i++){
        ll e;
        cin >> e;

        double ey = 0.5 * l * (-sin(2*M_PI*e/t));
        double ez = 0.5 * l * (-cos(2*M_PI*e/t)) + 0.5 * l;

        cout << 180 * atan(ez / sqrt(x*x+(y-ey)*(y-ey))) / M_PI << endl;
    }
    return 0;
}