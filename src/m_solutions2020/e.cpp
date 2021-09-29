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
    vector<int> x(n), y(n), p(n);

    for(int i=0; i<n; i++) cin >> x[i] >> y[i] >> p[i];

    vector<vector<ll>> dx(1<<n, vector<ll>(n, 1e9));
    vector<vector<ll>> dy(1<<n, vector<ll>(n, 1e9));

    for(int u=0; u<(1<<n); u++){
        for(int i=0; i<n; i++){
            dx[u][i] = abs(x[i]);
            dy[u][i] = abs(y[i]);
            for(int j=0; j<n; j++){
                if(u>>j&1) dx[u][i] = min(dx[u][i], (ll)abs(x[i]-x[j]));
                if(u>>j&1) dy[u][i] = min(dy[u][i], (ll)abs(y[i]-y[j]));
            }
        }
    }

    vector<ll> ans(n+1, 1e18);
    for(int u=0; u<(1<<n); u++){
        int k = 0;
        for(int i=0; i<n; i++){
            if(u>>i&1) k++;
        }
        for(int v=u;; v=(v-1)&u){
            ll c = 0;
            for(int i=0; i<n; i++){
                ll d = min(dx[v][i], dy[u^v][i]);
                c += p[i] * d;
            }
            ans[k] = min(ans[k], c);
            if(v==0) break;
        }
        if(ans[k]==0) {
            for(int j=k+1; j<=n; j++) ans[j] = 0;
            break;
        }
    }

    for(int k=0; k<=n; k++){
        cout << ans[k] << endl;
    }
    return 0;
}