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
    string s; cin >> s;

    vector<int> ca(n+1), ct(n+1), cc(n+1), cg(n+1);
    for(int i=0; i<n; i++){
        ca[i+1] = ca[i];
        ct[i+1] = ct[i];
        cc[i+1] = cc[i];
        cg[i+1] = cg[i];
        if(s[i]=='A') ca[i+1]++;
        if(s[i]=='T') ct[i+1]++;
        if(s[i]=='C') cc[i+1]++;
        if(s[i]=='G') cg[i+1]++;
    }

    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<=n; j++){
            if(ca[j]-ca[i]==ct[j]-ct[i]&&cc[j]-cc[i]==cg[j]-cg[i]){
                ans++;
            }
        }
    }

    cout << ans << endl;
    return 0;
}