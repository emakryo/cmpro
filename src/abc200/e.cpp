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

    ll n;
    ll k;
    cin >> n >> k;

    ll t = 0;
    for(ll s=3; s<=3*n; s++){
        ll nt;
        if(s<=n){
            nt = (s-1)*(s-2)/2;
        } else if(s<=2*n){
            nt = (s-1)*(s-2)/2 - 3*(s-n-1)*(s-n-2)/2;
        } else {
            nt = (3*n-s+1)*(3*n-s+2)/2;
        }

        if(t<k&&k<=t+nt){
            dbg(s, k-t);
            for(ll i=max(1ll, s-2*n); i<=s-2; i++){
                nt = min((ll)n, s-i-1) - max(1ll, s-i-n) + 1;
                if(t<k&&k<=t+nt){
                    dbg(i, k-t);
                    ll j = max(1ll, s-i-n) + k-t - 1;
                    cout << i << " " << j << " " << s-i-j << endl;
                    return 0;
                }
                t += nt;
            }
        }
        t += nt;
    }

    dbg(t);
    dbg((ll)n*n*n);
    return 0;
}