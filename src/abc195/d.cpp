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
    int n, m, q;
    cin >> n >> m >> q;

    vector<pair<int, int>> vw(n);
    for(int i=0; i<n; i++) cin >> vw[i].second >> vw[i].first;
    sort(vw.rbegin(), vw.rend());

    vector<int> x(m);
    cin >> x;
    
    vector<int> ls(q), rs(q);
    for(int i=0; i<q; i++) cin >> ls[i] >> rs[i];

    for(int p=0; p<q; p++){
        int l=ls[p], r=rs[p];

        multiset<int> y;
        for(int i=0; i<l-1; i++) y.insert(x[i]);
        for(int i=r; i<m; i++) y.insert(x[i]);
        dbg(p, y.size());

        int ans = 0;
        for(int i=0; i<n; i++){
            if(y.size()==0) break;
            auto it = y.lower_bound(vw[i].second);
            if(it==y.end()) continue;
            ans += vw[i].first;
            y.erase(it);
        }
        cout << ans << endl;
    }
    
    return 0;
}