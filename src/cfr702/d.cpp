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

void rec(vector<int> &a, int l, int r, vector<int> &d){
    if(r<=0 || a.size()<=l || r-l<=1) return;
    int k = max_element(a.begin()+l, a.begin()+r) - a.begin();
    for(int i=l; i<r; i++){
        if(i!=k) d[i]++;
    }
    rec(a, l, k, d);
    rec(a, k+1, r, d);
}

void solve(){
    int n; cin >> n;
    vector<int> a(n); cin >> a;
    vector<int> d(n);
    rec(a, 0, n, d);

    cout << d << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int t; cin >> t;
    for(int i=0; i<t; i++) solve();
    return 0;
}