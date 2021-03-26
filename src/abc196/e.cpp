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
    vector<ll> a(n);
    vector<int> t(n);
    for(int i=0; i<n; i++) cin >> a[i] >> t[i];

    int q;
    cin >> q;
    vector<ll> x(q);
    cin >> x;

    ll xl = -1e18, xr = 1e18;
    ll yl = -1e18, yr = 1e18;
    ll b = 0;

    for(int i=0; i<n; i++){
        if(t[i]==1){
            yl += a[i];
            yr += a[i];
            b += a[i];
        } else if(t[i]==2){
            if(yr<=a[i]){
                xl = xr = 1e18;
                yl = yr = b = a[i];
            } else if(yl<=a[i]){
                yl = a[i];
                xl = a[i]-b;
            }
        } else if(t[i]==3){
            if(a[i]<=yl){
                xl = xr = -1e18;
                yl = yr = b = a[i];
            } else if(a[i]<=yr){
                yr = a[i];
                xr = a[i]-b;
            }
        }
    }

    for(int i=0; i<q; i++){
        if(x[i]<=xl){
            cout << yl << endl;
        } else if(x[i]<=xr){
            cout << x[i]+b << endl;
        } else {
            cout << yr << endl;
        }
    }


    return 0;
}