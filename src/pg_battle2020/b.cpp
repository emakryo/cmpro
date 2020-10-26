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

void dfs(int m, int k, int s, vector<int> &a) {
    if(s<1) return;
    if(s<m) return;
    if(k==a.size()-1){
        a[k] = s;
        cout << a << endl;
        return;
    }
    for(int i=m;i<s;i++){
        a[k]=i;
        dfs(i, k+1, s-i, a);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n, s; cin >> n >> s;
    vector<int> ans(n);

    dfs(1, 0, s, ans);
    return 0;
}