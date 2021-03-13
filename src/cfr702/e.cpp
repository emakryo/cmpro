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
    vector<ll> a(n); cin >> a;
    vector<pair<ll, int>> ai(n);
    for(int i=0; i<n; i++){
        ai[i] = {a[i], i};
    }
    sort(ai.begin(), ai.end());
    vector<bool> ok(n, true);
    ll cum = 0;
    for(int i=0; i<n-1; i++){
        cum += ai[i].first;
        ok[i] = cum>=ai[i+1].first;
    }

    for(int i=n-1; i>0; i--){
        ok[i-1] = ok[i-1] && ok[i];
    }

    vector<int> ans;
    for(int i=0; i<n; i++){
        if(ok[i]) ans.push_back(ai[i].second+1);
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    cout << ans << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t; cin >> t;
    for(int i=0; i<t; i++) solve();
    return 0;
}