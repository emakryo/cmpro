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
    vector<int> s(2*n), d(2*n);
    for(int i=0; i<n; i++){
        int a, b; cin >> a >> b;
        a--; b--;
        if(a>=0&&b>=0){
            if(b<=a||s[a]!=0||s[b]!=0) {
                cout << "No" << endl;
                return 0;
            }
            s[a] = (i+1);
            s[b] = -(i+1);
            d[a] = b-a;
            d[b] = a-b;
        } else if(a>=0){
            if(s[a]!=0){
                cout << "No" << endl;
                return 0;
            }
            s[a] = i+1;
        } else if(b>=0){
            if(s[b]!=0){
                cout << "No" << endl;
                return 0;
            }
            s[b] = -(i+1);
        }
    }

    vector<bool> dp(n+1);

    dp[0] = true;

    for(int i=0; i<n; i++){
        if(!dp[i]) continue;
        for(int j=1; i+j<=n; j++){
            bool ok = true;
            for(int k=0; k<j; k++){
                int p = 2*i+k, q = 2*i+j+k;
                if(d[p]!=0&&d[p]!=j) ok = false;
                if(d[q]!=0&&d[q]!=-j) ok = false;

                if(s[p]!=0&&s[q]!=0&&s[p]+s[q]!=0) ok = false;
                if(s[p]<0 || 0<s[q]) ok = false;
            }
            dp[i+j] = dp[i+j] || ok;
        }
    }

    cout << (dp[n]?"Yes":"No") << endl;

    return 0;
}