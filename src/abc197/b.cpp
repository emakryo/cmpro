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

    int h, w, x, y;
    cin >> h >> w >> x >> y;
    vector<string> s(h);
    cin >> s;
    x--; y--;

    int ans = 1;
    for(int i=x+1; i<h; i++){
        if(s[i][y]=='#') break;
        ans++;
    }
    for(int i=x-1; i>=0; i--){
        if(s[i][y]=='#') break;
        ans++;
    }

    for(int i=y+1; i<w; i++){
        if(s[x][i]=='#') break;
        ans++;
    }
    for(int i=y-1; i>=0; i--){
        if(s[x][i]=='#') break;
        ans++;
    }
    cout << ans << endl;

    return 0;
}