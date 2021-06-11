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
    vector<ll> x(n), y(n);
    for(int i=0; i<n; i++) cin >> x[i] >> y[i];

    vector<vector<ll>> dp(1<<n, vector<ll>(k+1, 2e18));

    vector<vector<ll>> dist(n, vector<ll>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            dist[i][j] = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
        }
    }

    for(int s=1; s<(1<<n); s++){
        int m = 0;
        for(int j=0; j<n; j++){
            m += (s>>j)&1;
        }

        dp[s][1] = 0;
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                if((s>>i&1)==0||(s>>j&1)==0) continue;
                dp[s][1] = max(dp[s][1], dist[i][j]);
            }
        }

        for(int t=s&(s-1);; t=s&(t-1)){
            for(int i=2; i<=k; i++){
                dp[s][i] = min(dp[s][i], max(dp[t][i-1], dp[s^t][1]));
            }

            if(t==0) break;
        }
    }

    cout << dp[(1<<n)-1][k] << endl;
    return 0;
}

int _main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, k;
    cin >> n >> k;
    vector<ll> x(n), y(n);
    for(int i=0; i<n; i++) cin >> x[i] >> y[i];

    ll lb = 0, ub = 3e18;

    while(ub-lb>1){
        ll z = (ub+lb)/2;

        vector<int> dp(1<<n, 100);
        for(int s=1; s<(1<<n); s++){
            ll d = 0;
            for(int i=0; i<n; i++){
                for(int j=i+1; j<n; j++){
                    if((s>>i&1)==0||(s>>j&1)==0) continue;
                    d = max(d, (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                }
            }

            if(d<=z) dp[s] = 1;

            for(int t=s&(s-1);; t=s&(t-1)){
                dp[s] = min(dp[s], dp[t]+dp[s^t]);

                if(t==0) break;
            }
        }

        if(dp[(1<<n)-1]<=k){
            ub = z;
        } else {
            lb = z;
        }
    }

    cout << ub << endl;
    return 0;
}