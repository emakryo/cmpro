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

ll gcd(ll x, ll y){
    if(y==0) return x;
    else return gcd(y, x%y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;

    int ga = a[0];
    for(int i=1; i<n; i++) ga = gcd(ga, a[i]);
    for(int i=0; i<n; i++) a[i] /= ga;

    int m = *min_element(a.begin(), a.end());
    if(m==1) {
        cout << 1 << endl;
        return 0;
    }

    unordered_map<ll, ll> g;
    g[1] = 1;
    for(int i=0; i<n; i++){
        for(int p=2; p*p<=a[i]&&p<m; p++){
            if(a[i]%p>0) continue;
            if(g.count(p)==0){
                g[p] = a[i]/p;
            } else {
                g[p] = gcd(g[p], a[i]/p);
            }

            if(p*p==a[i]) continue;

            int q = a[i] / p;
            if(q < m) {
                if(g.count(q)==0){
                    g[q] = a[i]/q;
                } else {
                    g[q] = gcd(g[q] , a[i]/q);
                }
            }
        }
    }

    int ans = 1;
    for(auto p: g){
        if(p.second == 1) {
            ans+=1;
        }
    }

    cout << ans << endl;
    return 0;
}