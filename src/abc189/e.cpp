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

vector<ll> mat(vector<ll> a, vector<ll> b){
    vector<ll> x(9);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            for(int k=0; k<3; k++){
                x[3*i+j] += a[3*i+k] * b[3*k+j];
            }
        }
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n; cin >> n;
    vector<ll> x(n), y(n);
    for(int i=0; i<n; i++){
        cin >> x[i] >> y[i];
    }

    int m; cin >> m;
    vector<vector<ll>> f(m+1);
    f[0] = vector<ll>{1, 0, 0, 0, 1, 0, 0, 0, 1};
    for(int i=0; i<m; i++){
        int o; cin >> o;

        vector<ll> t;
        if(o==1) {
            t = vector<ll>{0, 1, 0, -1, 0, 0, 0, 0, 1};
        } else if(o==2){
            t = vector<ll>{0, -1, 0, 1, 0, 0, 0, 0, 1};
        } else if(o==3){
            ll p; cin >> p;
            t = vector<ll>{-1, 0, 2*p, 0, 1, 0, 0, 0, 1};
        } else if(o==4){
            ll p; cin >> p;
            t = vector<ll>{1, 0, 0, 0, -1, 2*p, 0, 0, 1};
        }

        f[i+1] = mat(t, f[i]);
    }

    int q; cin >> q;
    for(int i=0; i<q; i++){
        int a, b; cin >> a >> b;
        b--;

        vector<ll> p{x[b], 0, 0, y[b], 0, 0, 1, 0, 0};
        vector<ll> z = mat(f[a], p);

        cout << z[0] << " " << z[3] << endl;
    }

    return 0;
}