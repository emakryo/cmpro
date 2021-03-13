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

vector<double> mul(vector<double> x, vector<double> y) {
    return vector<double>{
        x[0]*y[0]+x[1]*x[2],
        x[0]*y[1]+x[1]*y[3],
        x[2]*y[0]+x[3]*x[2],
        x[2]*y[1]+x[3]*y[3],
    };
}

vector<double> pow(vector<double> x, ll n){
    if(n==1) return x;
    if(n%2) return mul(pow(x, n-1), x);
    vector<double> z = pow(x, n/2);
    return mul(z, z);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    double p;
    ll n;
    cin >> p >> n;

    vector<double> a{1-2*p, p, 0, 1};
    vector<double> x = pow(a, n);
    cout << x[1] << endl;

    return 0;
}