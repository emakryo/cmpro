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
    int n, m; cin >> n >> m;
    vector<ll> a(m); cin >> a;

    vector<int> x(n);

    for(int i=0; i<m; i++){
        int p = x.rend() - lower_bound(x.rbegin(), x.rend(), a[i]);
        if(p==n){
            cout << -1 << "\n";
        } else {
            cout << p+1 << "\n";
            x[p] = a[i];
        }
    }
    return 0;
}