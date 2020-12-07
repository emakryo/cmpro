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
    string t; cin >> t;

    ll s = 10000000000ll;
    // ll s = 5;
    if(n==1){
        if(t[0]=='0') cout << s << endl;
        else cout << 2*s << endl;
        return 0;
    } else if(n==2){
        if(t=="00") cout << 0 << endl;
        else if(t=="01") cout << s-1 << endl;
        else cout << s << endl; 
        return 0;
    }

    for(int i=3; i<n; i++){
        if(t[i]!=t[i%3]){
            cout << 0 << endl;
            return 0;
        }
    }

    if(t.substr(0, 3) == "110"){
        cout << s - (n-1)/3 << endl;
    } else if(t.substr(0, 3) == "101"){
        cout << s - n/3 << endl;
    } else if(t.substr(0, 3) == "011") {
        cout << s - (n+1)/3  << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}