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
    int n;
    cin >> n;
    vector<ll> a(n), b(n), c(n), d(n), e(n);

    for(int i=0; i<n; i++) cin >> a[i] >> b[i] >> c[i] >> d[i] >> e[i];

    ll lb=0, ub=1e18;

    while(ub-lb>1){
        ll x = (ub+lb) / 2;

        vector<vector<vector<bool>>> dp(n+1, vector<vector<bool>>(4, vector<bool>(32)));
        dp[0][0][0] = true;

        for(int i=0; i<n; i++){
            int s = 0;
            if(a[i]>=x) s+=1;
            if(b[i]>=x) s+=2;
            if(c[i]>=x) s+=4;
            if(d[i]>=x) s+=8;
            if(e[i]>=x) s+=16;
            for(int k=0; k<4; k++){
                for(int l=0; l<32; l++){
                    if(dp[i][k][l]){
                        dp[i+1][k][l] = true;
                        if(k<3) dp[i+1][k+1][l|s] = true;
                    }
                }
            }
        }
        if(dp[n][1][31]||dp[n][2][31]||dp[n][3][31]){
            lb = x;
        } else {
            ub = x;
        }
    }

    cout << lb << endl;
    return 0;
}