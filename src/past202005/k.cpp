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
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n, q; cin >> n >> q;
    vector<int> above(n, -1), below(n, -1);
    vector<int> top(n);
    for(int i=0; i<n; i++){
        top[i] = i;
    }

    while(q--){
        int f, t, x;
        cin >> f >> t >> x;
        f--; t--; x--;

        int top_f = top[f];

        if(below[x]>=0) above[below[x]] = -1;
        top[f] = below[x];

        below[x] = top[t];
        if(below[x]>=0) above[below[x]] = x;
        top[t] = top_f;
    }

    vector<int> ans(n);

    for(int i=0; i<n; i++){
        int x = top[i];
        while(x>=0){
            ans[x] = i+1;
            x = below[x];
        }
    }

    for(int i=0; i<n; i++){
        cout << ans[i] << "\n";
    }

    return 0;
}