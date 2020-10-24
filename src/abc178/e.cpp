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

    int n;cin>>n;
    vector<ll> x(n),y(n);
    for(int i=0;i<n;i++)cin>>x[i]>>y[i];

    vector<ll> w(n),z(n);
    for(int i=0;i<n;i++){
        w[i]=x[i]+y[i];
        z[i]=x[i]-y[i];
    }

    sort(w.begin(), w.end());
    sort(z.begin(), z.end());
    cout<<max(w[n-1]-w[0], z[n-1]-z[0])<<endl;
    return 0;
}