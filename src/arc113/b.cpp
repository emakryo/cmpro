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

ll pow(ll x, ll y){
    if(y == 0) return 1;
    else if(y%2) return pow(x, y-1) * x % 4;
    else {
        ll z = pow(x, y/2);
        return z*z%4;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    ll a, b, c;
    cin >> a >> b >> c;
    a = a%10;
    if(a==0){
        cout << 0 << endl;
        return 0;
    }

    int k = pow(b%4, c);
    if(k==0) k+=4;
    int x = 1;
    for(int i=0; i<k; i++){
        x *= a;
    }

    cout << x % 10 << endl;
    
    return 0;
}