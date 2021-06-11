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

vector<ll> a;

ll query(int i){
    ll x;
    cout << "? " << i+1 << endl;
    cin >> x;
    return x;
}

void rec(int i, int j){
    int k = (3-sqrt(5))/2*(j-i+1)+i;
    int l = (sqrt(5)-1)/2*(j-i+1)+i;
    dbg(i, k, l, j);
    if(a[k]<0) a[k] = query(k);
    if(a[l]<0) a[l] = query(l);
    if(j-i<2) return;

    if(a[k]>a[l]){
        rec(i, l);
    } else {
        rec(k, j);
    }
}

void solve(){
    int n;
    cin >> n;

    a.clear();
    a.assign(n, -1);
    dbg((3-sqrt(5))/2, (sqrt(5)-1)/2);

    // a[0] = query(0);
    // a[n-1] = query(n-1);
    rec(0, n-1);

    cout << "! " << *max_element(a.begin(), a.end()) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t;
    cin >> t;

    for(int i=0; i<t; i++) solve();
    return 0;
}