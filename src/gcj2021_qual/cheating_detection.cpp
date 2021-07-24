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

double inv_sigmoid(double y) {
    if(y == 0.0){
        return -3.0;
    } else if (y == 1.0) {
        return 3.0;
    }
    return min(3.0, max(-3.0, log(y / (1-y))));
}

void solve(){
    int n = 100, m = 10000;
    vector<string> a(n);
    cin >> a;

    vector<int> cp(n), cq(m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j]=='1'){
                cp[i]++;
                cq[j]++;
            }
        }
    }


    vector<double> likelihood(n, 1e10);

    for(int i=0; i<n; i++){
        if(cp[i]<4000) continue;
        double st = inv_sigmoid(cp[i] / 10000.0);
        double sc = inv_sigmoid((cp[i]-5000) / 5000.0);

        double la = 0, lb = 0;
        for(int j=0; j<m; j++){
            double q = inv_sigmoid((cq[j] - (a[i][j]-'0')) / 99.0);
            double pa = 1 / (1 + exp(-st+q));
            double pb = 0.5 * (1 + 1 / (1 + exp(-sc+q)));
            if(a[i][j]=='1'){
                la += -log(pa);
                lb += -log(pb);
            } else {
                la += -log(1-pa);
                lb += -log(1-pb);
            }
        }
        likelihood[i] = la - lb;

        dbg(i, st, sc, la, lb, likelihood[i]);
    }

    dbg(*min_element(likelihood.begin(), likelihood.end()));
    int ans = min_element(likelihood.begin(), likelihood.end()) - likelihood.begin() + 1;
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t, p;
    cin >> t >> p;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}