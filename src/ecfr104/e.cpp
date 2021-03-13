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
    
    int n[4];
    for(int i=0; i<4; i++) cin >> n[i];
    vector<ll> a(n[0]), b(n[1]), c(n[2]), d(n[3]);
    cin >> a >> b >> c >> d;

    int m[3];
    vector<vector<int>> x, y;
    for(int i=0; i<3; i++){
        cin >> m[i];
        vector<int> xi(m[i]), yi(m[i]);
        for(int j=0; j<m[i]; j++){
            cin >> xi[j] >> yi[j];
            xi[j]--; yi[j]--;
        }
        x.push_back(xi);
        y.push_back(yi);
    }

    vector<pair<ll, int>> ai(n[0]);
    for(int i=0; i<n[0]; i++) ai[i] = {a[i], i};
    sort(ai.begin(), ai.end());

    vector<set<int>> bm(n[1]);
    for(int i=0; i<m[0]; i++){
        bm[y[0][i]].insert(x[0][i]);
    }

    for(int i=0; i<n[1]; i++){
        ll k = 0;
        while(k<n[0]&&bm[i].count(ai[k].second)==1) k++;
        if(k==n[0]){
            b[i] += 1e9;
        } else {
            b[i] += ai[k].first;
        }
    }

    dbg(b);

    vector<pair<ll, int>> di(n[3]);
    for(int i=0; i<n[3]; i++) di[i] = {d[i], i};
    sort(di.begin(), di.end());

    vector<set<int>> cm(n[2]);
    for(int i=0; i<m[2]; i++){
        cm[x[2][i]].insert(y[2][i]);
    }

    for(int i=0; i<n[2]; i++){
        ll k = 0;
        while(k<n[3]&&cm[i].count(di[k].second)==1) k++;
        if(k==n[3]){
            c[i] += 1e9;
        } else {
            c[i] += di[k].first;
        }
    }

    dbg(c);

    vector<pair<ll, int>> ci(n[2]);
    for(int i=0; i<n[2]; i++) ci[i] = {c[i], i};
    sort(ci.begin(), ci.end());

    for(int i=0; i<n[1]; i++){
        bm[i].clear();
    }
    for(int i=0; i<m[1]; i++){
        bm[x[1][i]].insert(y[1][i]);
    }

    ll ans = 1e18;
    for(int i=0; i<n[1]; i++){
        ll k = 0;
        while(k<n[2]&&bm[i].count(ci[k].second)==1) k++;
        if(k==n[2]){
            b[i] += 1e9;
        } else {
            b[i] += ci[k].first;
        }
        ans = min(ans, b[i]);
    }

    if(ans >= 1e9){
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}