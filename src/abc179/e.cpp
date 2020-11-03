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

ll naive(ll n, int x, int m){
    ll ans = 0;
    ll now = x;
    for(int i=0; i<n; i++){
        ans += now;
        now = now*now%m;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    ll n; cin >> n;
    int x, m; cin >> x >> m;

    if(x==0 || m == 1){
        cout << 0 << endl;
        return 0;
    }

    vector<int> idx(m, -1);
    vector<ll> cum(m);
    ll y = x;
    int k = 0;
    while(idx[y]<0&&k<n){
        idx[y] = k;
        cum[k] = (k>0?cum[k-1]:0)+y;
        k++;
        y = y*y%m;
        dbg(y);
    }
    // dbg(k, y);
    // cum.resize(k);
    // dbg(cum);
    if(k==n){
        cout << cum[k-1] << endl;
    } else{
        int l = idx[y];
        ll a = l>0?cum[l-1]:0; // first part
        ll b = cum[k-1]-a;     // single loop
        ll c = (n-l)%(k-l)?cum[(n-l)%(k-l)-1+l]-a:0; // last part
        dbg(l, k-l, n-l, (n-l)/(k-l), (n-l)%(k-l));
        dbg(a, b, c);
        ll ans = a;
        ans += b * ((n-l)/(k-l));
        ans += c;
        cout << ans << endl;
    }
    //dbg(naive(n, x, m));
    return 0;
}