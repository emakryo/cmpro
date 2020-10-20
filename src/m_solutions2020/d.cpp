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
    vector<int> a(n); cin >> a;

    ll c0 = 1000;
    ll c1 = 1000;
    ll s = 0;
    for(int i=0; i<n; i++){
        ll nc0 = max(c0, c1+a[i]*s);
        if(s+c1/a[i] > c0/a[i] || (s+c1/a[i] == c0/a[i] && c1%a[i] > c0%a[i])) {
            s += c1/a[i];
            c1 %= a[i];
        } else {
            s = c0/a[i];
            c1 = c0%a[i];
        }
        c0 = nc0;
    }

    cout << max(c0, c1+a[n-1]*s) << endl;
    return 0;
}