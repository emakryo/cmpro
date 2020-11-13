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
    vector<string> a(n); cin >> a;

    string ans;

    for(int i=0; i<n/2; i++){
        vector<bool> x(26), y(26);
        for(int j=0; j<n; j++){
            x[a[i][j]-'a']=true;
        }
        for(int j=0; j<n; j++){
            y[a[n-i-1][j]-'a']=true;
        }
        bool ok = false;
        for(int j=0; j<26; j++){
            if(x[j]&&y[j]){
                ans += j+'a';
                ok = true;
                break;
            }
        }

        if(!ok){
            cout << -1 << endl;
            return 0;
        }
    }

    if(n%2){
        cout << ans + a[n/2][0];
        reverse(ans.begin(), ans.end());
        cout << ans << endl;
    } else {
        cout << ans;
        reverse(ans.begin(), ans.end());
        cout << ans << endl;
    }

    return 0;
}