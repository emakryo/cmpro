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

    int n, m; cin >> n >> m;
    vector<int> a(m), b(m);
    for(int i=0; i<m; i++) cin >> a[i] >> b[i];

    int k; cin >> k;
    vector<int> c(k), d(k);
    for(int i=0; i<k; i++) cin >> c[i] >> d[i];

    int ans = 0;
    for(int s=0; s<(1<<k); s++){
        vector<bool> x(n+1);
        for(int i=0; i<k; i++){
            if(s>>i&1) x[c[i]]=true;
            else x[d[i]]=true;
        }

        int z = 0;
        for(int i=0; i<m; i++){
            if(x[a[i]]&&x[b[i]]){
                z++;
            }
        }

        ans = max(ans, z);
    }

    cout << ans << endl;
    return 0;
}