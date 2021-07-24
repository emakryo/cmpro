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
    vector<int> cost(m);
    vector<vector<int>> p(m, vector<int>(n));

    for(int i=0; i<m; i++){
        int c;
        cin >> c >> cost[i];
        for(int j=0; j<c; j++){
            int x;
            cin >> x;
            x--;
            cin >> p[i][x];
        }
    }

    vector<double> dp(1<<n);
    for(int i=(1<<n)-2; i>=0; i--){
        vector<double> exp(m);
        for(int j=0; j<m; j++){
            int pj = 0;
            for(int k=0; k<n; k++){
                if((i>>k&1)==0) pj += p[j][k];
            }
            if(pj==0){
                exp[j] = 1e18;
                continue;
            }

            exp[j] = cost[j] * 100.0 / pj;
            for(int k=0; k<n; k++){
                if(i>>k&1) continue;
                exp[j] += dp[i|(1<<k)] * p[j][k] / pj;
            }
        }

        dp[i] = *min_element(exp.begin(), exp.end());
        dbg(i, exp, dp[i]);
    }

    cout << dp[0] << endl;

    return 0;
}