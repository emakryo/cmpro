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

ll c(int n, int m){
    ll r = 1;
    for(int i=0; i<m; i++){
        r *= n-i;
        r /= i+1;
    }

    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int a, b;
    ll k;
    cin >> a >> b >> k;

    string ans;
    int n = a+b;
    for(int i=0; i<n; i++){
        dbg(a, b, k);
        if(a==0){
            ans += 'b';
            b--;
            dbg(i, 'a');
        } else if(b==0){
            ans += 'a';
            a--;
            dbg(i, 'b');
        } else if(k<=c((a-1)+b, a-1)){
            a--;
            ans += 'a';
            dbg(i, 'a');
        } else {
            k -= c((a-1)+b, a-1);
            b--;
            dbg(i, 'b');
            ans += 'b';
        }
    }

    cout << ans << endl;
    return 0;
}