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

    int n, k;
    ll l;
    cin >> n >> l >> k;
    vector<ll> a(n);
    cin >> a;

    ll lb=0, ub=l;
    while(ub-lb>1){
        ll x = (lb+ub)/2;

        ll b = 0;
        int m = 0;
        for(int i=0; i<n; i++){
            if(a[i]-b>=x){
                b = a[i];
                m++;
            }
        }
        if(l-b>=x){
            m++;
        }

        if(m>k){
            lb = x;
        } else {
            ub = x;
        }
    }

    cout << lb << endl;


    return 0;
}