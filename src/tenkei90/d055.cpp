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

    int n;
    cin >> n;
    ll p, q;
    cin >> p >> q;

    vector<ll> a(n);
    cin >> a;

    int ans = 0;
    for(int i0=0; i0<n; i0++){
        for(int i1=i0+1; i1<n; i1++){
            for(int i2=i1+1; i2<n; i2++){
                for(int i3=i2+1; i3<n; i3++){
                    for(int i4=i3+1; i4<n; i4++){
                        ll x = a[i0]*a[i1]%p*a[i2]%p*a[i3]%p*a[i4]%p;
                        if(x==q) ans++;
                    }
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}