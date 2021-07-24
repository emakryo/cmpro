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
    ll k, p;
    cin >> n >> k >> p;
    vector<ll> a(n), b(n);
    cin >> a >> b;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll lb=-1, ub=p;
    while(ub-lb>1){
        ll x = (ub+lb)/2;
        
        ll m = 0;
        for(int i=0; i<n; i++){
            m += lower_bound(a.begin(), a.end(), x-b[i]+1) - a.begin();
            m +=  lower_bound(a.begin(), a.end(), p+x-b[i]+1) - lower_bound(a.begin(), a.end(), p-b[i]);
        }

        if(m<k) {
            lb = x;
        } else {
            ub = x;
        }
    }

    cout << ub << endl;
    return 0;
}