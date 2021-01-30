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

    int n; cin >> n;
    vector<int> x(n), y(n);
    for(int i=0; i<n; i++) cin >> x[i] >> y[i];

    vector<vector<double>> a(n+2, vector<double>(n+2));
    for(int i=0; i<n; i++){
        a[i][n] = a[n][i] = (y[i]+100)*(y[i]+100);
        a[i][n+1] = a[n+1][i] = (100-y[i])*(100-y[i]);

        for(int j=i+1; j<n; j++){
            a[i][j] = a[j][i] = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
        }
    }
    a[n][n+1] = a[n+1][n] = 200*200;

    for(int i=0; i<n+2; i++) dbg(a[i]);

    double ub = 200, lb = 0;
    for(int lo=0; lo<100; lo++){
        double z = (ub+lb)/2;

        vector<bool> visit(n+2);
        queue<int> que;
        que.push(n);
        while(que.size()){
            int u = que.front();
            que.pop();
            if(visit[u]) continue;
            visit[u] = true;
            for(int v=0; v<n+2; v++){
                if(u==v||a[u][v]>=z*z) continue;
                if(visit[v]) continue;
                que.push(v);
            }
        }

        if(visit[n+1]) {
            ub = z;
        } else {
            lb = z;
        }
    }

    cout << lb/2 << endl;
    return 0;
}