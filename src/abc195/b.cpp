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

    int a, b, w;
    cin >> a >> b >> w;
    w *= 1000;

    int ans_min = 1e9;
    int ans_max = 0;

    for(int k=1; k<2000000; k++){
        if(a*k<=w && w<=b*k){
            ans_min = min(ans_min, k);
            ans_max = max(ans_max, k);
        }
    }
    if(ans_max == 0) cout << "UNSATISFIABLE" << endl;
    else cout << ans_min << " " << ans_max << endl;
    return 0;
}