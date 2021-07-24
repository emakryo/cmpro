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

vector<ll> mul(vector<ll> x, vector<ll> y) {
    vector<ll> z(9);
    for(int i=0; i<3; i++) for(int j=0; j<3; j++) for(int k=0; k<3; k++){
        z[3*i+j] += x[3*i+k] * y[3*k+j];
    }
    for(int i=0; i<9; i++) z[i] = z[i]%10;
    return z;
}

vector<ll> pow(vector<ll> x, ll k) {
    if(k==1) return x;
    if(k%2) return mul(pow(x, k-1), x);
    vector<ll> z = pow(x, k/2);
    return mul(z, z);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    ll p, q, r, k;
    cin >> p >> q >> r >> k;

    vector<ll> x = {
        1, 1, 1, 1, 0, 0, 0, 1, 0
    };

    vector<ll> z = pow(x, k-3);

    ll ans = r%10*z[0] + q%10*z[1] + p%10*z[2];
    cout << ans % 10 << endl;


    return 0;
}