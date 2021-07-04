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

    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    cin >> a;
    vector<ll> k(q);
    cin >> k;
    
    for(int i=0; i<q; i++){
        ll lb=0, ub=2e18;
        while(ub-lb>1){
            ll x = (lb+ub)/2;
            int j = lower_bound(a.begin(), a.end(), x) - a.begin();
            if(x-j-1>=k[i]){
                ub = x;
            } else {
                lb = x;
            }
        }

        cout << ub-1 << endl;
    }


    return 0;
}