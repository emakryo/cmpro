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
    string x;
    cin >> x;
    ll m;
    cin >> m;

    int d = *max_element(x.begin(), x.end()) - '0';
    if(x.size()==1){
        if(d<=m){
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }

    // x = "9";
    // for(int i=0; i<59; i++) x+="0";
    // m = 1;
    dbg(x);
    dbg(m);

    ll z = 0;
    for(int i=0; i<x.size(); i++){
        if((m-(int)(x[i]-'0'))/(d+1)<z){
            cout << 0 << endl;
            return 0;
        }
        z *= d+1;
        z += x[i]-'0';
    }
    if(z>m){
        cout << 0 << endl;
        return 0;
    }

    ll lb=d+1, ub = m+1;
    while(ub-lb>1){
        ll n = (lb+ub)/2;
        ll z = 0;
        for(int i=0; i<x.size(); i++){
            if((m-(int)(x[i]-'0'))/n<z){
                ub = n;
                break;
            }
            z *= n;
            z += x[i]-'0';
        }
        dbg(z, n, ub);
        if(ub==n) continue;
        if(z>m){
            ub = n;
        } else {
            lb = n;
        }
    }

    cout << ub-(d+1) << endl;
    return 0;
}