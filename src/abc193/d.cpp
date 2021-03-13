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

    ll k; cin >> k;
    string s, t;
    cin >> s >> t;

    vector<int> x(9), y(9);
    for(int i=0; i<4; i++){
        x[s[i]-'1']++;
        y[t[i]-'1']++;
    }

    ll n = 0;
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            ll s = 0;
            x[i]++;
            y[j]++;
            for(int l=0; l<9; l++){
                int p=1;
                for(int m=0; m<x[l]; m++) p*=10;
                int q=1;
                for(int m=0; m<y[l]; m++) q*=10;
                s += (l+1)*(p-q);
            }
            dbg(i, j, s);
            dbg(x);
            dbg(y);
            x[i]--;
            y[j]--;
            if(s>0){
                if(i==j){
                    ll z = k-x[i]-y[i];
                    if(z>1) n += z*(z-1);
                } else {
                    if(k>x[i]+y[i]&&k>x[j]+y[j]) n += (k-x[i]-y[i])*(k-x[j]-y[j]);
                }
            }
        }
    }

    ll z = 9*k-8;
    cout << (double)n/z/(z-1) << endl;

    return 0;
}