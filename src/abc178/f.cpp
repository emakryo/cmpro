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
    int n;cin >> n;
    vector<int> a(n), b(n); cin >> a >> b;

    vector<int> na(n), nb(n);
    for(int i=0;i<n;i++){
        na[a[i]-1]++;
        nb[b[i]-1]++;
    }
    for(int i=0;i<n;i++){
        if(na[i]+nb[i]>n){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;

    vector<int> c(n), d(n);
    int k=0;
    for(int i=0;i<n;i++){
        while(k<a[i]&&k<n){
            c[k++] = i;
        }
    }
    while(k<n) {
        c[k] = n;
        k++;
    }
    k=0;
    for(int i=0;i<n;i++){
        while(k<b[i]&&k<n){
            d[k++] = i;
        }
    }
    while(k<n){
        d[k] = n;
        k++;
    }
    dbg(c);
    dbg(d);
    int x = 0;
    for(int i=0;i<n-1;i++){
        x = max(c[i+1]-d[i], x);
    }
    x = max(n-d[n-1], x);
    dbg(x);

    vector<int> ans(n);
    for(int i=0;i<n;i++){
        ans[(i+x)%n] = b[i];
    }
    cout << ans << endl;

    return 0;
}