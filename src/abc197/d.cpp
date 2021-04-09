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

    double x0, y0, xm, ym;
    cin >> x0 >> y0 >> xm >> ym;

    double xo = (x0+xm)/2, yo = (y0+ym)/2;
    // double r = sqrt((x0-xo)*(x0-xo)+(y0-yo)*(y0-yo));

    double r = 2*M_PI/n;
    double x1 = (x0-xo)*cos(r) - (y0-yo)*sin(r) + xo;
    double y1 = (x0-xo)*sin(r) + (y0-yo)*cos(r) + yo;

    cout << x1 << " " << y1 << endl;
    return 0;
}