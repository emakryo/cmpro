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

void solve(){
    ll x; cin >> x;
    for(ll a=1; a*a*a<x; a++){
        ll lb=1, ub=1e5;
        while(ub-lb>1){
            ll m = (ub+lb)/2;
            if(m*m*m+a*a*a<=x){
                lb = m;
            } else {
                ub = m;
            }
        }
        if(lb*lb*lb+a*a*a==x) {
            cout << "Yes" << endl;
            return;
        }
    }

    cout << "No" << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int t; cin >> t;
    for(int i=0; i<t; i++) solve();
    return 0;
}