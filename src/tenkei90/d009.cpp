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
    vector<double> x(n), y(n);
    for(int i=0; i<n; i++) cin >> x[i] >> y[i];

    double ans = 0;
    for(int i=0; i<n; i++){
        vector<double> r;
        for(int j=0; j<n; j++){
            if(i==j) continue;

            ll x0 = x[j]-x[i];
            ll y0 = y[j]-y[i];
            r.push_back(arg(complex<double>(x0, y0)));
        }
        sort(r.begin(), r.end());
        for(int j=0; j<n-1; j++){
            r.push_back(r[j]+2*M_PI);
        }

        for(int j=0; j<n-1; j++){
            auto it = lower_bound(r.begin(), r.end(), r[j]+M_PI);

            double z = 0;
            if(it!=r.end()){
                z = 2*M_PI - (*it - r[j]);
            }
            if(it!=r.begin()){
                it--;
                z = max(z, *it - r[j]);
            }
            ans = max(ans, z / M_PI * 180);
        }
    }

    cout << ans << endl;
    return 0;
}