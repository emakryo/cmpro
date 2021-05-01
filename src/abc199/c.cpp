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

    int n; cin >> n;
    string s; cin >> s;
    int q; cin >> q;

    bool flip = false;
    for(int i=0; i<q; i++){
        int t; cin >> t;
        int a, b; cin >> a >> b;
        a--; b--;

        if(t==1){
            if(flip){
                a = (a+n)%(2*n);
                b = (b+n)%(2*n);
            }
            dbg(a, b);
            swap(s[a], s[b]);
        } else {
            flip = !flip;
        }
    }

    if(flip){
        cout << s.substr(n, n) + s.substr(0, n) << endl;
    } else {
        cout << s << endl;
    }
    return 0;
}