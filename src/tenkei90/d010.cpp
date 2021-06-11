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
    vector<int> c(n), p(n);
    for(int i=0; i<n; i++) cin >> c[i] >> p[i];

    vector<int> x1(n+1), x2(n+1);
    for(int i=0; i<n; i++){
        if(c[i]==1){
            x1[i+1] = p[i];
        } else {
            x2[i+1] = p[i];
        }
    }

    for(int i=1; i<=n; i++){
        x1[i] += x1[i-1];
        x2[i] += x2[i-1];
    }


    int q; cin >> q;
    for(int _i=0; _i<q; _i++){
        int l, r;
        cin >> l >> r;
        cout << x1[r]-x1[l-1] << " " << x2[r]-x2[l-1] << endl;
    }

    return 0;
}