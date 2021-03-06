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
    string s;
    cin >> s;
    for(int i=0; i<s.size(); i++){
        if(i%2==0){
            if(s[i]<'a'||'z'<s[i]){
                cout << "No" << endl;
                return 0;
            }
        } else {
            if(s[i]<'A'||'Z'<s[i]){
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
    return 0;
}