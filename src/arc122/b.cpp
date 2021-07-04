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
    vector<ll> a(n);
    cin >> a;
    sort(a.begin(), a.end());

    // x <= a[0]/2
    ll sum = reduce(a.begin(), a.end());
    ll sumk = 0;
    double mean = (double)sum/n;
    double ans = mean - a[0]/2.0;
    dbg(0, ans);

    for(int i=0; i<n; i++){
        // a[i]/2 <= x <= a[i+1]/2
        int p = 2*i+2-n;
        sumk += a[i];
        double tmp;
        if(p<0) { // x = a[i+1]/2
            tmp = mean - (double)sumk/n + (double)p*a[i+1]/2/n;
        } else { // x = a[i]/2
            tmp = mean - (double)sumk/n + (double)p*a[i]/2/n;
        }
        dbg(i+1, p, tmp);
        ans = min(ans, tmp);
    }

    cout << ans << endl;

    return 0;
}