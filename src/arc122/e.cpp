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

ll gcd(ll x, ll y){
    if(y==0) return x;
    else return gcd(y, x%y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;

    vector<ll> ans;
    vector<bool> used(n);
    for(int i=0; i<n; i++){
        bool ok = false;
        for(int j=0; j<n; j++){
            if(used[j]) continue;
            ll b = 1;
            for(int k=0; k<n; k++){
                if(k==j) continue;
                if(used[k]) continue;
                ll g = gcd(a[j], a[k]);
                ll f = gcd(b, g);
                b *= g/f;
            }
            if(b<a[j]){
                ans.push_back(a[j]);
                used[j] = true;
                ok = true;
                break;
            }
        }
        if(!ok) {
            cout << "No" << endl;
            return 0;
        }
    }

    reverse(ans.begin(), ans.end());
    cout << "Yes" << endl;
    cout << ans << endl;

    return 0;
}