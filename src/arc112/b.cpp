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

    ll b, c;
    cin >> b >> c;
    ll d = b-c/2;
    ll e = -b-(c-1)/2;
    dbg(d, e);
    if(b==0){
        cout << c << endl;
    }
    else if((b>0&&d>0)||(b<0&&e>0)){
        if(c==1){
            cout << 2 << endl;
        } else {
            cout << 2*c-1 << endl;
        }
    } else {
        if(b>0){
            cout << c+2*b-1 << endl;
        } else {
            cout << c-2*b << endl;
        }

    }
    return 0;
}