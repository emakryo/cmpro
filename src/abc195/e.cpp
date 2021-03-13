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
    string s, x;
    cin >> s >> x;

    int b = 1;
    vector<bool> ok(7);
    ok[0]=1;
    for(int i=n-1; i>=0; i--){
        int a = b*(s[i]-'0')%7;
        vector<bool> next(7);
        if(x[i]=='A'){
            for(int k=0; k<7; k++){
                next[k] = ok[k]&&ok[(k+7-a)%7];
            }
        } else {
            for(int k=0; k<7; k++){
                next[k] = ok[k]||ok[(k+7-a)%7];
            }
        }
        ok = next;
        b *= 10;
        b %= 7;
    }
    cout << (ok[0]?"Takahashi":"Aoki") << endl;

    return 0;
}