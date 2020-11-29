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
    int n, k; cin >> n >> k;
    string s; cin >> s;

    for(int i=0; i<k; i++){
        if(s.size()%2){
            s = s+s;
        }
        string t;
        for(int j=0; j<s.size(); j+=2){
            if(s[j]==s[j+1]) t += s[j];
            else if(s[j]=='R' && s[j+1]=='S' || s[j]=='S' && s[j+1]=='R') t+='R';
            else if(s[j]=='P' && s[j+1]=='R' || s[j]=='R' && s[j+1]=='P') t+='P';
            else if(s[j]=='S' && s[j+1]=='P' || s[j]=='P' && s[j+1]=='S') t+='S';
        }
        s = t;
    }

    cout << s[0] << endl;
    return 0;
}