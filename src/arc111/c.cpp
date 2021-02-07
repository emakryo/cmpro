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
    vector<ll> a(n), b(n);
    cin >> a >> b;
    vector<int> p(n);
    cin >> p;
    for(int i=0; i<n; i++) p[i]--;

    vector<pair<ll, int>> ai(n);
    for(int i=0; i<n; i++) ai[i] = {a[i], i};
    sort(ai.begin(), ai.end());

    vector<int> q(n);
    for(int i=0; i<n; i++) q[p[i]] = i;

    vector<pair<int, int>> ans;
    for(int i=0; i<n-1; i++){
        int j = ai[i].second;
        int k = q[j];
        if(j==k) continue;
        if(a[j] <= b[p[j]] || a[k] <= b[p[k]]){
            cout << -1 << endl;
            return 0;
        }
        ans.push_back({j+1, k+1});
        p[k] = p[j];
        p[j] = j;
        q[p[j]] = j;
        q[p[k]] = k;
        dbg(j);
        dbg(p);
    }

    cout << ans.size() << endl;
    for(int i=0; i<ans.size(); i++) cout << ans[i].first << " " << ans[i].second << "\n";

    return 0;
}