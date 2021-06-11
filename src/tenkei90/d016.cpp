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

    ll n, a, b, c;
    cin >> n >> a >> b >> c;

    int ans = 1e9;
    for(int i=0; i<10000; i++){
        for(int j=0; i+j<10000; j++){
            ll x = n - i*a - j*b;
            if(x>=0&&x%c==0&&x/c+i+j<10000){
                ans = min((ll)ans, x/c+i+j);
            }
        }
    }

    cout << ans << endl;
    return 0;
}