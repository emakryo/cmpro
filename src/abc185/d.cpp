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

    ll n;
    int m; 
    cin >> n >> m;
    vector<ll> a(m);
    cin >> a;
    sort(a.begin(), a.end());
    if(m==0) {
        cout << 1 << endl;
        return 0;
    }

    a.push_back(n+1);
    vector<ll> ws;
    ll last = 0;
    for(int i=0; i<m+1; i++){
        if(a[i]-last>1){
            ws.push_back(a[i]-last-1);
        }
        last = a[i];
    }
    dbg(ws);

    if(ws.size()==0){
        cout << 0 << endl;
        return 0;
    }

    ll k = *min_element(ws.begin(), ws.end());
    dbg(k);

    ll ans = 0;
    for(int w: ws){
        ans += (w+k-1)/k;
    }

    cout << ans << endl;

    return 0;
}