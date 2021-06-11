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
    int k, n;
    ll p;
    cin >> n >> k >> p;
    vector<ll> a(n);
    cin >> a;

    vector<vector<ll>> b(n/2+1);
    b[0].push_back(0);
    for(int i=0; i<n/2; i++){
        for(int j=n/2-1; j>=0; j--){
            for(ll x: b[j]){
                b[j+1].push_back(x+a[i]);
            }
        }
    }

    for(auto &c: b){
        sort(c.begin(), c.end());
        dbg(c);
    }

    ll ans = 0;
    for(int s=0; s<(1<<(n-n/2)); s++){
        ll x = 0;
        int m = 0;
        for(int i=0; i<n-n/2; i++){
            if(s>>i&1){
                x += a[n/2+i];
                m++;
            }
        }

        if(0<=k-m&&k-m<=n/2){
            int z = lower_bound(b[k-m].begin(), b[k-m].end(), p-x+1) - b[k-m].begin();
            dbg(s, x, m, z);
            ans += z;
        }
    }

    cout << ans << endl;
    return 0;
}