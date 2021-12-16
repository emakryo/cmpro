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

    if(s=="a" || s==string(20, 'z')) {
        cout << "NO" << endl;
    } else if(s.size() == 1){
        cout << (char)(s[0]-1) << 'a' << endl;
    } else {
        int imin = 0;
        for(int i=0; i<s.size(); i++){
            if(s[i]<s[imin]) imin = i;
        }
        int imax = 0;
        if(imin==imax) imax++;
        for(int i=0; i<s.size(); i++){
            if(i==imin) continue;
            if(s[imax] < s[i]) imax = i;
        }
        if(s[imax]=='a'){
            s[0] = 'b';
            s.pop_back();
        } else if(s[imin]=='z'){
            s[0] = 'y';
            s.push_back('a');
        } else {
            s[imin]++;
            s[imax]--;
        }
        cout << s << endl;
    }
    return 0;
}