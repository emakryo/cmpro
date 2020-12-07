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
    if(n==1){
        if(m==0) cout << 1 << " " << 2 << endl;
        else cout << -1 << endl;
        return 0;
    }

    if(m<0||n-2<m){
        cout << -1 << endl;
        return 0;
    }

    vector<pair<int, int>> ans;
    ans.push_back({1, 2*m+4});
    for(int i=0; i<m+1; i++){
        ans.push_back({2*i+2, 2*i+3});
    }
    for(int i=0; i<n-m-2; i++){
        ans.push_back({2*m+5+2*i, 2*m+6+2*i});
    }

    for(int i=0; i<n; i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    return 0;
}