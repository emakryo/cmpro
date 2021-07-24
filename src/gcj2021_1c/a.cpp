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

void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    cin >> p;

    set<int> ps;
    for(int i=0; i<n; i++) ps.insert(p[i]);

    p.clear();
    for(int x: ps) p.push_back(x);
    
    vector<int> d, e;
    d.push_back(p[0]-1);
    for(int i=0; i<p.size()-1; i++){
        d.push_back((p[i+1]-p[i])/2);
        e.push_back(p[i+1]-p[i]-1);
    }
    d.push_back(k-p[p.size()-1]);
    dbg(d);
    sort(d.rbegin(), d.rend());

    int x = d[0] + d[1];
    if(e.size()){
        x = max(x, *max_element(e.begin(), e.end()));
    }

    cout << double(x) / k << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t; cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}