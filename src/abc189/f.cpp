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

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(k);
    cin >> a;

    vector<double> e0(n+m+1), ex(n+m+1);
    vector<bool> c(n);

    for(int i=0; i<k; i++) c[a[i]] = true;

    double s0 = 0, sx = 0;
    for(int i=n-1; i>0; i--){
        if(c[i]){
            ex[i] = 1;
        } else {
            e0[i] = 1 + s0/m;
            ex[i] = sx/m;
        }

        s0 += e0[i] - e0[i+m];
        sx += ex[i] - ex[i+m];

        if(abs(sx-m) < 1e-8) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << (m + s0) / (m - sx) << endl;
    return 0;
}