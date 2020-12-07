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

ll rec(int l, int r, vector<ll> &a, vector<ll> &b){
    if(r-l==2) return max(a[l]+a[l+1], b[l]+b[l+1]);
    ll ret = 0;

    ret = max(ret, max(a[l]+a[r-1], b[l]+b[r-1]) + rec(l+1, r-1, a, b));
    for(int m=l+2; m<r; m+=2){
        ret = max(ret, rec(l, m, a, b)+rec(m, r, a, b));
    }

    return ret;
}



int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n; cin>>n;
    vector<ll> a(n), b(n);
    cin >> a >> b;

    // cout << rec(0, n, a, b) << endl;

    ll sa = 0;
    vector<ll> c0(n/2), c1(n/2);
    for(int i=0; i<n; i++){
        sa += a[i];
        if(i%2) c0[i/2] = b[i] - a[i];
        else c1[i/2] = b[i] - a[i];
    }

    sort(c0.rbegin(), c0.rend());
    sort(c1.rbegin(), c1.rend());

    vector<ll> s(n/2);
    s[0] = c0[0]+c1[0];

    for(int i=1; i<n/2; i++){
        s[i] = c0[i]+c1[i]+s[i-1];
    }

    ll ans = sa;
    for(int i=0; i<n/2; i++){
        ans = max(ans, sa+s[i]);
    }
    cout << ans << endl;

    return 0;
}