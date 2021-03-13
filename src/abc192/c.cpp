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
    ll n; cin >> n;
    int k; cin >> k;

    ll x = n;
    for(int i=0; i<k; i++){
        vector<int> d;
        if(x==0){
            continue;
        }
        while(x>0){
            d.push_back(x%10);
            x /= 10;
        }
        sort(d.begin(), d.end());
        ll m = 1;
        x = 0;
        for(int j=0; j<d.size(); j++){
            x += m*(d[j]-d[d.size()-1-j]);
            m *= 10;
        }
        dbg(d);
        dbg(x);
    }
    cout << x << endl;
    return 0;
}