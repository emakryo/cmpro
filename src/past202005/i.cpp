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
    int n, q; cin >> n >> q;
    vector<ll> x(n), y(n);
    bool transposed = false;
    for(int i=0; i<n; i++){
        x[i] = i;
        y[i] = i;
    }

    for(int i=0; i<q; i++){
        int p; cin >> p;
        int a, b;
        if(p==1){
            cin >> a >> b;
            a--; b--;
            if(transposed){
                swap(y[a], y[b]);
            } else {
                swap(x[a], x[b]);
            }
        } else if(p==2){
            cin >> a >> b;
            a--; b--;
            if(transposed){
                swap(x[a], x[b]);
            } else {
                swap(y[a], y[b]);
            }
        } else if(p==3){
            transposed = !transposed;
        } else {
            cin >> a >> b;
            a--; b--;
            if(transposed){
                cout << x[b] * n + y[a] << endl;
            } else {
                cout << x[a] * n + y[b] << endl;
            }
        }
    }
    return 0;
}