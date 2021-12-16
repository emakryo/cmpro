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
    int n; cin >> n;
    vector<int> p(n);
    cin >> p;

    vector<pair<int, int>> pi(n);
    for(int i=0; i<n; i++) pi[i] = {p[i], i};
    sort(pi.rbegin(), pi.rend());

    vector<int> ans;
    int e = n;
    for(int i=0; i<n; i++){
        int j = pi[i].second;
        if(j>=e) continue;
        for(int k=j; k<e; k++) ans.push_back(p[k]);
        e = j;
    }

    cout << ans << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int t; cin >> t;
    for(int i=0; i<t; i++) solve();
    return 0;
}