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
    int offset = 0;
    for(int i=0; i<q; i++){
        int t, x, y;
        cin >> t >> x >> y;

        if(t==1){
            swap(a[(x-1-offset+2*n)%n], a[(y-1-offset+2*n)%n]);
        } else if(t==2){
            offset = (offset+1)%n;
        } else {
            cout << a[(x-1-offset+2*n)%n] << endl;
        }
    }

    return 0;
}