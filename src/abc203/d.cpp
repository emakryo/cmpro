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

    int n, k;
    cin >> n >> k;

    vector<vector<ll>> a(n, vector<ll>(n));
    cin >> a;

    vector<vector<int>> s(n+1, vector<int>(n+1));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            s[i+1][j+1] = s[i][j+1]+s[i+1][j]-s[i][j]+(a[i][j]==0?1:0);
        }
    }

    bool ok = false;
    for(int i=0; i<=n-k; i++){
        for(int j=0; j<=n-k; j++){
            if(s[i+k][j+k]-s[i+k][j]-s[i][j+k]+s[i][j]>=(k*k+1)/2){
                ok = true;
            }
        }
    }
    if(ok){
        cout << 0 << endl;
        return 0;
    }

    ll lb = 0, ub = 1e10;

    while(ub-lb>1){
        ll x = (ub+lb)/2;
        vector<vector<int>> s(n+1, vector<int>(n+1));
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                s[i+1][j+1] = s[i][j+1]+s[i+1][j]-s[i][j]+(a[i][j]<=x?1:0);
            }
        }

        bool ok = false;
        for(int i=0; i<=n-k; i++){
            for(int j=0; j<=n-k; j++){
                if(s[i+k][j+k]-s[i+k][j]-s[i][j+k]+s[i][j]>=(k*k+1)/2){
                    ok = true;
                }
            }
        }
        if(ok){
            ub = x;
        } else {
            lb = x;
        }
    }

    cout << ub << endl;

    return 0;
}