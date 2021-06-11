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

    int n, q;
    cin >> n >> q;
    vector<ll> u(n), v(n);
    for(int i=0; i<n; i++){
        ll x, y;
        cin >> x >> y;
        u[i] = x+y;
        v[i] = x-y;
    }

    ll umin = *min_element(u.begin(), u.end());
    ll umax = *max_element(u.begin(), u.end());
    ll vmin = *min_element(v.begin(), v.end());
    ll vmax = *max_element(v.begin(), v.end());

    vector<int> ans;
    for(int _i=0; _i<q; _i++){
        int k;
        cin >> k;
        k--;

        cout << max({u[k]-umin, umax-u[k], v[k]-vmin, vmax-v[k]}) << endl;
    }
    return 0;
}