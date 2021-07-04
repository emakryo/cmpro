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

    int n;
    cin >> n;
    vector<int> l(n), r(n);
    for(int i=0; i<n; i++) cin >> l[i] >> r[i];

    double ans = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int x = 0;
            for(int k=l[i]; k<=r[i]; k++){
                x += max(0, min(r[j], k-1) - l[j] + 1);
            }

            ans += double(x)/(r[i]-l[i]+1)/(r[j]-l[j]+1);
            dbg(i, j, l[i], r[i], l[j], r[j], x);
        }
    }
    cout << ans << endl;

    return 0;
}